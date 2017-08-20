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

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_commandLinkButton_clicked();
    void readTcp1Data(void);

    void on_commandLinkButton_2_clicked();


private:

    void GetUiData(void) const;

    void SetUiData(void);

    void GetConfigurationUi(void) const;


    Ui::MainWindow *ui;
    QTcpSocket* m_TcpSocket1;
    QByteArray m_Data1;
    static DataParser m_DataParser1;
    QPushButton* m_Light1Buttons[DataParser::NUM_LIGHT];
    QPushButton* m_PIREnable1;
    QPushButton* m_LightsOn1;

    /// 4 configurations for 5 lights.
    QPushButton* m_conf1Buttons[DataParser::NUM_LIGHT][DataParser::NUM_CONFIGURATIONS];
};

#endif // MAINWINDOW_H
