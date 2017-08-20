
#include <cstdio>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QLabel>
#include <QPushButton>
#include <qlogging.h>
#include "../include/Definitions.h"

DataParser MainWindow::m_DataParser1;
DataParser MainWindow::m_DataParser2;

const char* MainWindow::IP_ADDRESS_1 = "192.168.1.173";

const char* MainWindow::IP_ADDRESS_2 = "192.168.1.174";

const uint8_t DATA_SIZE_BYTES = 2U;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_3->setText(IP_ADDRESS_1);
    ui->label_4->setText(QString::number(PORT));
    ui->label_9->setText(QString::number(PORT));

    m_Light1Buttons[0] = ui->pushButton_2;
    m_Light1Buttons[1] = ui->pushButton_3;
    m_Light1Buttons[2] = ui->pushButton_4;

    m_conf1Buttons[0][0] = ui->pushButton_1_1;
    m_conf1Buttons[0][1] = ui->pushButton_1_2;
    m_conf1Buttons[0][2] = ui->pushButton_1_3;
    m_conf1Buttons[0][3] = ui->pushButton_1_4;
    m_conf1Buttons[1][0] = ui->pushButton_2_1;
    m_conf1Buttons[1][1] = ui->pushButton_2_2;
    m_conf1Buttons[1][2] = ui->pushButton_2_3;
    m_conf1Buttons[1][3] = ui->pushButton_2_4;
    m_conf1Buttons[2][0] = ui->pushButton_3_1;
    m_conf1Buttons[2][1] = ui->pushButton_3_2;
    m_conf1Buttons[2][2] = ui->pushButton_3_3;
    m_conf1Buttons[2][3] = ui->pushButton_3_4;
    m_conf1Buttons[3][0] = ui->pushButton_4_1;
    m_conf1Buttons[3][1] = ui->pushButton_4_2;
    m_conf1Buttons[3][2] = ui->pushButton_4_3;
    m_conf1Buttons[3][3] = ui->pushButton_4_4;
    m_conf1Buttons[4][0] = ui->pushButton_5_1;
    m_conf1Buttons[4][1] = ui->pushButton_5_2;
    m_conf1Buttons[4][2] = ui->pushButton_5_3;
    m_conf1Buttons[4][3] = ui->pushButton_5_4;


    m_PIREnable1 = ui->pushButton;

    m_LightsOn1 = ui->pushButton_8;

    m_TcpSocket1 =  new (std::nothrow) QTcpSocket(this);
    if (m_TcpSocket1 == NULL )
    {
        qFatal("New QTcpSocket failed");
    }
    connect(m_TcpSocket1, SIGNAL(readyRead()), SLOT(readTcp1Data()));

    m_TcpSocket1->connectToHost(IP_ADDRESS_1, PORT);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readTcp1Data(void)
{
    m_Data1 = m_TcpSocket1->readAll();
    // Data parser input possible
    if (m_Data1.size() == DATA_SIZE_BYTES)
    {
        m_DataParser1.SetData(*(uint16_t*)m_Data1.data());
        this->SetUiData();
        std::printf("Read socket1 passed\n");
    }
    else{
        std::printf("Read socket1 failed, invalid data size, %i\n", m_Data1.size());

    }
    ui->label_5->setText(QString(m_Data1.data()));
}

// Set Data1 button
void MainWindow::on_commandLinkButton_clicked()
{
    this->GetUiData();
    m_DataParser1.SetLightFlag(true);
    const uint16_t data = m_DataParser1.GetData();
    m_TcpSocket1->write((const char*)&data, DATA_SIZE_BYTES);
}

// Get data button
void MainWindow::on_commandLinkButton_2_clicked()
{
    m_DataParser1.SetLightFlag(false);
    uint16_t data = m_DataParser1.GetData();
    m_TcpSocket1->write((const char*)&data, DATA_SIZE_BYTES);
}

void MainWindow::GetUiData(void) const
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_DataParser1.SetLight(i, uint16_t(m_Light1Buttons[i]->isChecked()));
    }
    m_DataParser1.SetPIREnable(uint16_t(m_PIREnable1->isChecked()));

    m_DataParser1.SetLightOn((uint16_t)(m_LightsOn1->isChecked()));
    GetConfigurationUi();
}

void MainWindow::SetUiData(void)
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_Light1Buttons[i]->setChecked(m_DataParser1.GetLight(i) != 0);
    }
    std::printf("PirEnable1 %i\n", m_DataParser1.GetPIREnable());

    m_PIREnable1->setChecked(m_DataParser1.GetPIREnable() != 0);

    m_LightsOn1->setChecked(m_DataParser1.GetLightOn() != 0);
}


void MainWindow::GetConfigurationUi(void) const
{
    uint32_t configuration = 0U;
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        for (int j = 0; j < DataParser::NUM_CONFIGURATIONS; ++j) {
            if (m_conf1Buttons[i][j]->isChecked())
            {
                configuration |= ((1 << DataParser::NUM_CONFIGURATIONS * j) <<i);
            }
        }
    }
    m_DataParser1.SetConfiguration(configuration);
}
