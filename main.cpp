#include <QApplication>
#include "mainwindow.h"

extern const QString  VERSION = "1.2";

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("Gmail Sniffer");
    a.setApplicationVersion(VERSION.toUtf8());

    MainWindow w;
    w.setWindowTitle("Gmail Sniffer " + VERSION.toUtf8());
    w.hide();

    return a.exec();
}
