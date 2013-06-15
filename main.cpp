/**
 * This file is Copyright 2012
 *     Kristian Beres <admin@katropine.net>
 *
 * Other copyrights also apply to some parts of this work.  Please
 * see the individual file headers for details.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.  See the file
 * COPYING included with this distribution for more information.
 */
#include <QApplication>
#include "mainwindow.h"

extern const QString  VERSION = "1.3.1";

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
