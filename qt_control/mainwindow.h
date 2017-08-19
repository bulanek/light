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

    static const char*  IP_ADDRESS_1;
    static const char*  IP_ADDRESS_2;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_commandLinkButton_clicked();
    void readTcp1Data(void);
    void readTcp2Data(void);

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

private:

    void GetUiData(void) const;

    void SetUiData(void);


    Ui::MainWindow *ui;
    QTcpSocket* m_TcpSocket1,* m_TcpSocket2;
    QByteArray m_Data1, m_Data2;
    static DataParser m_DataParser1;
    static DataParser m_DataParser2;
    QPushButton* m_Light1Buttons[DataParser::NUM_LIGHT];
    QPushButton* m_Light2Buttons[DataParser::NUM_LIGHT];
    QPushButton* m_PIREnable1;
    QPushButton* m_PIREnable2;
    QPushButton* m_LightsOn1;
    QPushButton* m_LightsOn2;
};

#endif // MAINWINDOW_H
