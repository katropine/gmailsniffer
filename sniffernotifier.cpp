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
#include "sniffernotifier.h"
#include "ui_sniffernotifier.h"
#include "settings.h"
#include <QtGui>
#include <QString>
#include <QRect>

SnifferNotifier::SnifferNotifier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SnifferNotifier)
{
    ui->setupUi(this);
    // settings
    this->pSettings = new Settings();

    // init
    desktop = QApplication::desktop();
    this->setWindowFlags(Qt::ToolTip);
    this->setWindowOpacity(0.9);
    //windowSize = size();
    qDebug() << this->pSettings->getWidth();
    width = this->pSettings->getWidth();//350;
    height = this->pSettings->getHeight();//windowSize.height();
    //QRect rec1 = desktop->screenGeometry(0);
    //QRect rec2 = desktop->availableGeometry(0);
    //height = 0, x = rec2.width() - width, y = rec2.height() + this->getTopPanel();
    x = this->pSettings->getPositionX();
    y = this->pSettings->getPositionY();
    setGeometry(x,y,width,height);
    QPixmap pixmap(":/images/gmailredsmall.png");
    ui->lblImage->setPixmap(pixmap);
}

// settings test notify position
SnifferNotifier::SnifferNotifier(QWidget *parent, int x, int y, int width, int height) :
    QWidget(parent),
    ui(new Ui::SnifferNotifier)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::ToolTip);
    this->setWindowOpacity(0.9);


    this->width = width;
    this->height = height;

    this->x = x;
    this->y = y;
    setGeometry(x,y,width,height);
    QPixmap pixmap(":/images/gmailredsmall.png");
    ui->lblImage->setPixmap(pixmap);
}

void SnifferNotifier::sendMessage(QString data, int duration){

    timer = new QTimer(this);
    this->showWidget();
    connect(timer, SIGNAL(timeout()), this, SLOT(hideWidget()));
    timer->start(duration * 1000);
    ui->lblMessage->setText(data);

}
// settings test notify position



void SnifferNotifier::sendMessage(QString data){

    timer = new QTimer(this);
    this->showWidget();
    connect(timer, SIGNAL(timeout()), this, SLOT(hideWidget()));
    timer->start(this->pSettings->getDuration() * 1000);
    ui->lblMessage->setText(data);

}

void SnifferNotifier::showWidget(){
    //y = y - 100;
    //height = height + 100;
    setGeometry(x,y,width,height);
    this->show();
}
void SnifferNotifier::hideWidget(){
    //y = y + 100;
    //height = height - 100;
    setGeometry(x,y,width,height);
    this->hide();
    timer->stop();
}
/**
 * @brief SnifferNotifier::getTopPanel KDE stuff
 * @return
 */
int SnifferNotifier::getTopPanel()
{
    int topPanel = 0;
    #ifdef Q_WS_X11
    char * pPath = getenv ("KDE_FULL_SESSION");
    if (QString(pPath) == NULL)
    {
        QProcess gconf;
        gconf.start("gconftool", QStringList() << "--get" <<  "/schemas/apps/panel/toplevels/size");

        gconf.waitForStarted();
        gconf.closeWriteChannel();
        gconf.waitForFinished();

        QByteArray result = gconf.readAll();

        QString str = QString(result);
        int j = 0;
        j = str.indexOf("Default Value:", j);

        int k = 0;
        k = str.indexOf("Owner:", k);

        topPanel = str.section("", j, k).trimmed().section("",-3,-1).toInt();
    }
    #endif
    return topPanel;
}

SnifferNotifier::~SnifferNotifier()
{
    delete pSettings;
    delete desktop;
    delete timer;
    delete ui;
}
