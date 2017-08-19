#include "mainwindow.h"
#include <QApplication>
#include <QTcpSocket>
#include "../include/DataParser.hpp"
#include "../include/Definitions.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
