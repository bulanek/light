#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTcpSocket>
#include <QByteArray>
#include "../include/DataParser.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    // CONSTANTS


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_commandLinkButton_clicked();
    void readTcpData(void);

    void on_commandLinkButton_2_clicked();


    void on_commandLinkButton_3_clicked();

private:

    void GetUiData(void) const;

    void SetUiData(void);

    void GetConfigurationUi(void) const;


    Ui::MainWindow *ui;
    QTcpSocket* m_TcpSocket;
    QByteArray m_Data;
    static DataParser m_DataParser;
    QPushButton* m_LightButtons[DataParser::NUM_LIGHT];
    QPushButton* m_PIREnable;
    QPushButton* m_LightsOn;

    /// 4 configurations for 5 lights.
    QPushButton* m_confButtons[DataParser::NUM_LIGHT][DataParser::NUM_CONFIGURATIONS];
    static const uint8_t NUM_ADDRESSES = 5U;
    const char* IP_ADDRESSES[NUM_ADDRESSES] = {"192.168.1.173" ,"192.168.1.174" ,"192.168.1.175", "192.168.1.176","192.168.1.177"};
    const char* ADDRESS_NAMES[NUM_ADDRESSES] = {"chodba-dvere","chodba-satna","spalna","obyvak","kuchyna"};
    Q_STATIC_ASSERT(sizeof(IP_ADDRESSES)/sizeof(const char*) == NUM_ADDRESSES);
    Q_STATIC_ASSERT(sizeof(ADDRESS_NAMES)/sizeof(const char*) == NUM_ADDRESSES);
};

#endif // MAINWINDOW_H
