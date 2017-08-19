
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
    ui->label_7->setText(IP_ADDRESS_2);
    ui->label_4->setText(QString::number(PORT));
    ui->label_9->setText(QString::number(PORT));

    m_Light1Buttons[0] = ui->pushButton_2;
    m_Light1Buttons[1] = ui->pushButton_3;
    m_Light1Buttons[2] = ui->pushButton_4;
    m_Light2Buttons[0] = ui->pushButton_5;
    m_Light2Buttons[1] = ui->pushButton_6;
    m_Light2Buttons[2] = ui->pushButton_7;

    m_PIREnable1 = ui->pushButton;
    m_PIREnable2 = ui->pushButton_9;

    m_LightsOn1 = ui->pushButton_8;
    m_LightsOn2 = ui->pushButton_10;

    m_TcpSocket1 =  new (std::nothrow) QTcpSocket(this);
    m_TcpSocket2 =  new (std::nothrow) QTcpSocket(this);
    if ((m_TcpSocket1 == NULL) || (m_TcpSocket2 == NULL))
    {
        qFatal("New QTcpSocket failed");
    }
    connect(m_TcpSocket1, SIGNAL(readyRead()), SLOT(readTcp1Data()));
    connect(m_TcpSocket2, SIGNAL(readyRead()), SLOT(readTcp2Data()));

    m_TcpSocket1->connectToHost(IP_ADDRESS_1, PORT);
    m_TcpSocket2->connectToHost(IP_ADDRESS_2, PORT);
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

void MainWindow::readTcp2Data(void)
{
    m_Data2 = m_TcpSocket2->readAll();
    // Data parser input possible
    if (m_Data2.size() == DATA_SIZE_BYTES)
    {
        m_DataParser2.SetData(*(uint16_t*)m_Data2.data());
        this->SetUiData();
        std::printf("Read socket2 passed\n");
    }
    else{
        std::printf("Read socket2 failed, invalid size: %i\n",m_Data2.size());
    }
    ui->label_5->setText(QString(m_Data2.data()));
}


// Set Data1 button
void MainWindow::on_commandLinkButton_clicked()
{
    this->GetUiData();
    m_DataParser1.SetLightFlag(true);
    const uint16_t data = m_DataParser1.GetData();
    m_TcpSocket1->write((const char*)&data, DATA_SIZE_BYTES);
}
// Set Data2 button
void MainWindow::on_commandLinkButton_3_clicked()
{
    this->GetUiData();
    m_DataParser2.SetLightFlag(true);
    const uint16_t data = m_DataParser2.GetData();
    m_TcpSocket2->write((const char*)&data, DATA_SIZE_BYTES);
}

// Get data button
void MainWindow::on_commandLinkButton_2_clicked()
{
    m_DataParser1.SetLightFlag(false);
    uint16_t data = m_DataParser1.GetData();
    m_TcpSocket1->write((const char*)&data, DATA_SIZE_BYTES);

    m_DataParser2.SetLightFlag(false);
    data = m_DataParser2.GetData();
    m_TcpSocket2->write((const char*)&data, DATA_SIZE_BYTES);
}

void MainWindow::GetUiData(void) const
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_DataParser1.SetLight(i, uint16_t(m_Light1Buttons[i]->isChecked()));
        m_DataParser2.SetLight(i, uint16_t(m_Light2Buttons[i]->isChecked()));
    }
    m_DataParser1.SetPIREnable(uint16_t(m_PIREnable1->isChecked()));
    m_DataParser2.SetPIREnable(uint16_t(m_PIREnable2->isChecked()));

    m_DataParser1.SetLightOn((uint16_t)(m_LightsOn1->isChecked()));
    m_DataParser2.SetLightOn((uint16_t)(m_LightsOn2->isChecked()));
}

void MainWindow::SetUiData(void)
{
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        m_Light1Buttons[i]->setChecked(m_DataParser1.GetLight(i) != 0);
        m_Light2Buttons[i]->setChecked(m_DataParser2.GetLight(i) != 0);
    }
    std::printf("PirEnable1 %i\n", m_DataParser1.GetPIREnable());
    std::printf("PirEnable2 %i\n", m_DataParser2.GetPIREnable());

    m_PIREnable1->setChecked(m_DataParser1.GetPIREnable() != 0);
    m_PIREnable2->setChecked(m_DataParser2.GetPIREnable() != 0);

    m_LightsOn1->setChecked(m_DataParser1.GetLightOn() != 0);
    m_LightsOn2->setChecked(m_DataParser2.GetLightOn() != 0);
}
