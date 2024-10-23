#include "mainwindow.h"
#include "authwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    AuthWindow w;

    w.show();
    return a.exec();
}
