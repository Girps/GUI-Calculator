#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(316,320);
    w.setWindowTitle("Calculator");
    w.show();
    return a.exec();
}
