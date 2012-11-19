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
#ifndef SNIFFERNOTIFIER_H
#define SNIFFERNOTIFIER_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QRect>
#include "settings.h"

namespace Ui {
class SnifferNotifier;
}

class SnifferNotifier : public QWidget
{
    Q_OBJECT
    
public:
    explicit SnifferNotifier(QWidget *parent = 0);
    explicit SnifferNotifier(QWidget *parent, int x, int y, int width, int height);
    ~SnifferNotifier();
    void sendMessage(QString data);
    void sendMessage(QString data, int duration);

public slots:
    void showWidget();
    void hideWidget();
    
private:
    Ui::SnifferNotifier *ui;

    QTimer *timer;
    QDesktopWidget *desktop;
    QSize windowSize;
    int getTopPanel();
    Settings *pSettings;

    int x;
    int y;
    int screenWidth, width, originalWidth;
    int screenHeight, height, originalHeight;
};

#endif // SNIFFERNOTIFIER_H
