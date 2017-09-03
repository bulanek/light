
#include <cstdio>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QLabel>
#include <QPushButton>
#include <qlogging.h>
#include "../include/Definitions.h"

DataParser MainWindow::m_DataParser;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_TcpSocket(this)
{
    ui->setupUi(this);
    for (int i = 0; i < NUM_ADDRESSES; ++i) {
        ui->comboBox->addItem(QString(ADDRESS_NAMES[i]));
    }


    m_LightButtons[0] = ui->pushButton_2;
    m_LightButtons[1] = ui->pushButton_3;
    m_LightButtons[2] = ui->pushButton_4;

    m_confButtons[0][0] = ui->pushButton_1_1;
    m_confButtons[0][1] = ui->pushButton_1_2;
    m_confButtons[0][2] = ui->pushButton_1_3;
    m_confButtons[0][3] = ui->pushButton_1_4;
    m_confButtons[1][0] = ui->pushButton_2_1;
    m_confButtons[1][1] = ui->pushButton_2_2;
    m_confButtons[1][2] = ui->pushButton_2_3;
    m_confButtons[1][3] = ui->pushButton_2_4;
    m_confButtons[2][0] = ui->pushButton_3_1;
    m_confButtons[2][1] = ui->pushButton_3_2;
    m_confButtons[2][2] = ui->pushButton_3_3;
    m_confButtons[2][3] = ui->pushButton_3_4;
    m_confButtons[3][0] = ui->pushButton_4_1;
    m_confButtons[3][1] = ui->pushButton_4_2;
    m_confButtons[3][2] = ui->pushButton_4_3;
    m_confButtons[3][3] = ui->pushButton_4_4;
    m_confButtons[4][0] = ui->pushButton_5_1;
    m_confButtons[4][1] = ui->pushButton_5_2;
    m_confButtons[4][2] = ui->pushButton_5_3;
    m_confButtons[4][3] = ui->pushButton_5_4;


    m_PIREnable = ui->pushButton;

    m_LightsOn = ui->pushButton_8;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readTcpData(void)
{
    m_Data = m_TcpSocket.readAll();
    // Data parser input possible
    if (m_Data.size() == CONFIGURATION_DATA_SIZE)
    {
        m_DataParser.SetData(*(uint16_t*)m_Data.data());
        this->SetUiData();
        std::printf("Read socket1 passed\n");
    }
    else{
        std::printf("Read socket1 failed, invalid data size, %i\n", m_Data.size());

    }
    ui->label_5->setText(QString(m_Data.data()));
}

// Set Data1 button
void MainWindow::on_commandLinkButton_clicked()
{
    this->GetUiData();
    m_DataParser.SetLightFlag(true);
    const uint16_t data = m_DataParser.GetData();
    m_TcpSocket.write((const char*)&data, CONFIGURATION_DATA_SIZE);
}

// Get data button
void MainWindow::on_commandLinkButton_2_clicked()
{
    m_DataParser.SetLightFlag(false);
    uint16_t data = m_DataParser.GetData();
    m_TcpSocket.write((const char*)&data, CONFIGURATION_DATA_SIZE);
}

void MainWindow::GetUiData(void) const
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_DataParser.SetLight(i, uint16_t(m_LightButtons[i]->isChecked()));
    }
    m_DataParser.SetPIREnable(uint16_t(m_PIREnable->isChecked()));

    m_DataParser.SetLightOn((uint16_t)(m_LightsOn->isChecked()));
    GetConfigurationUi();
}

void MainWindow::SetUiData(void)
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_LightButtons[i]->setChecked(m_DataParser.GetLight(i) != 0);
    }
    std::printf("PirEnable %i\n", m_DataParser.GetPIREnable());

    m_PIREnable->setChecked(m_DataParser.GetPIREnable() != 0);

    m_LightsOn->setChecked(m_DataParser.GetLightOn() != 0);
}


void MainWindow::GetConfigurationUi(void) const
{
    uint32_t configuration = 0U;
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        for (int j = 0; j < DataParser::NUM_CONFIGURATIONS; ++j) {
            if (m_confButtons[i][j]->isChecked())
            {
                configuration |= ((1 << DataParser::NUM_CONFIGURATIONS * j) <<i);
            }
        }
    }
    m_DataParser.SetConfiguration(configuration);
}

void MainWindow::on_commandLinkButton_3_clicked()
{
    int currentIndex = ui->comboBox->currentIndex();
    Q_ASSERT(currentIndex <= NUM_ADDRESSES);
    connect(&m_TcpSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
    m_TcpSocket.connectToHost(IP_ADDRESSES[currentIndex], PORT);
}
