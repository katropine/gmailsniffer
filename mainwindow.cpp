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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gmailatom.h"
#include "sniffernotifier.h"

#include <QtCore>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QHttp>
#include <QtNetwork>
#include <QWebPage>
#include <QDomDocument>
#include <QtGui>
#include "gmailatom.h"
#include "dialogsettings.h"
#include "aboutsniffer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/gmailredsmall.png"));
    this->setCentralWidget(ui->scrollArea);
    this->createTrayIcon();

    /**
     * Setting Button
     */
    QFont font;
    font.setPixelSize(9);

    pSettingsBtn= new  QPushButton("Settings");
    pSettingsBtn->setMaximumHeight(20);
    pSettingsBtn->setMaximumWidth(50);
    pSettingsBtn->setFont(font);
    ui->statusbar->addPermanentWidget(pSettingsBtn);
    connect(pSettingsBtn, SIGNAL(clicked()), this, SLOT(onSettingsClicked()));


    /**
     * Load Gmail
     */
    Settings settings;
    this->load();
    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(load()));
    int refreshEvery = settings.getRefreshTime() * 1000;
    pTimer->start(refreshEvery);
    qDebug() << refreshEvery;
}

void MainWindow::load(){
    qDebug() << "Timer fired";

    pNetworkManager = new QNetworkAccessManager(this);

    connect(pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(result(QNetworkReply*)));

    /**
     * load settings
     */
    Settings settings;

    QUrl url("https://mail.google.com/mail/feed/atom");
    url.setUserName(settings.getUserName());
    url.setPassword(settings.getPassword());

    pNetworkManager->get(QNetworkRequest(url));
}

void MainWindow::result(QNetworkReply *reply){
    qDebug() << "reply: ";

    if(reply->error() > 0){
        pTimer->stop();
        QMessageBox::information(this, "Oooopsss!","Could not connect to gmail.com. Possible wrong username or password.\n\n Try entering Your data again.");
        qDebug() << reply->errorString();

    }else{
        GmailAtom gmailAtom = GmailAtom(reply);
        QMap<int, Email> map = gmailAtom.fetch();

        pSignalMapper = new QSignalMapper(this);


        // check if layout filled
        if(ui->verticalLayout->count() > 0){
            QLayoutItem *item = NULL;
            while ((item = ui->verticalLayout->takeAt(0)) != 0) {
                delete item->widget();
            }
        }
        QFont font;

        font.setPixelSize(11);

        foreach(int i, map.keys()){
            font.setBold(false);
            QCommandLinkButton* buttonEmail = new QCommandLinkButton(this);
            Email em = map[i];

            buttonEmail->setObjectName(em.getLink());
            buttonEmail->setText(em.__toString());
            if(i == 0){
                font.setBold(true);
                buttonEmail->setIcon(QIcon(":/images/gmailred.png"));
            }else{
                buttonEmail->setIcon(QIcon(":/images/gmailblue.png"));
            }
            buttonEmail->setToolTip("Requires that you are logged in Gmail");
            buttonEmail->setMinimumHeight(61);
            buttonEmail->setMaximumWidth(270);
            buttonEmail->setFont(font);
            connect(buttonEmail, SIGNAL(clicked()), pSignalMapper, SLOT(map()));


            pSignalMapper->setMapping(buttonEmail, buttonEmail);

            ui->verticalLayout->addWidget(buttonEmail);
        }

        if(this->emailCount < map.count() && map.count() > 0){
            //allert
            Email newEm = map[0];
            Settings settings;
            if(settings.getSystemNotifier()){
                QString message;
                message.append("notify-send \"");
                message.append(newEm.getAuthorName());
                message.append("\" \"<br>");
                message.append(newEm.getTitle());
                message.append("\" -i /usr/share/icons/gmailsniffer.png");
                system(message.toUtf8());
            }else{
                pNotifier = new SnifferNotifier(this);
                pNotifier->sendMessage(newEm.__toString());
            }
            this->trayAlert();
        }
        if(map.count() == 0 && this->emailCount == 0){
            this->trayNormal();
            QCommandLinkButton* buttonNoEmail = new QCommandLinkButton(this);
            buttonNoEmail->setText("You have 0 unread emails, go to inbox?");
            buttonNoEmail->setFont(font);
            buttonNoEmail->setObjectName("https://mail.google.com/mail/#inbox");
            ui->verticalLayout->addWidget(buttonNoEmail);

            connect(buttonNoEmail, SIGNAL(clicked()), pSignalMapper, SLOT(map()));
            pSignalMapper->setMapping(buttonNoEmail, buttonNoEmail);
        }

        // connect mapped QCommandLinkButton SIGNAL to onButtonEmailClicked SLOT
        connect(pSignalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(onButtonEmailClicked(QWidget*)));

        this->emailCount = map.count();
        this->reloadTrayTooltip();

        QString msg = QString::number(map.count());
        msg.append(" unread emails.");

        ui->statusbar->showMessage(msg);

        /**
         * !important
         */
        reply->deleteLater();
        reply->close();
        pNetworkManager->deleteLater();
        map.clear();

        qDebug() << "Request successful!";
    }

}


void MainWindow::onButtonEmailClicked(QWidget *buttonEmail){
    QCommandLinkButton * bt = qobject_cast<QCommandLinkButton *>( buttonEmail );
    Q_ASSERT( bt );
    qDebug() << bt->objectName(); //email->getLink();


    Settings settings;

    if(settings.getBrowser() == 0){
        QDesktopServices::openUrl(QUrl(bt->objectName(), QUrl::TolerantMode));
    }else{
        QString exeBrowserCmd;
        exeBrowserCmd.append(settings.getBrowserCmd()+" \"");
        exeBrowserCmd.append(bt->objectName());
        exeBrowserCmd.append("\" &");

        QProcess process;
        process.execute(exeBrowserCmd.toUtf8());
        process.deleteLater();
    }
    delete bt;
}

void MainWindow::onSettingsClicked(){
    DialogSettings dialogSettings(this);
    dialogSettings.setModal(true);
    dialogSettings.exec();
}

void MainWindow::showAboutSnifferDialog(){
    AboutSniffer dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::createTrayIcon(){
    trayIconMenu = new QMenu(this);


    quitAction = new QAction(tr("Exit"), this);
    quitAction->setIcon(QIcon(":/images/application-exit.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    maximizeAction = new QAction(tr("Show Sniffer"), this);
    maximizeAction->setIcon(QIcon(":/images/package-upgrade.png"));
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showSniffer()));

    minimizeAction = new QAction(tr("Hide Sniffer"), this);
    minimizeAction->setIcon(QIcon(":/images/package-downgrade.png"));
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hideSniffer()));

    aboutSniffer = new QAction(tr("About Sniffer"), this);
    aboutSniffer->setIcon(QIcon(":/images/gtk-info.png"));
    connect(aboutSniffer, SIGNAL(triggered()), this, SLOT(showAboutSnifferDialog()));

    settingsAction = new QAction(tr("Settings"), this);
    settingsAction->setIcon(QIcon(":/images/preferences-system.png"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(onSettingsClicked()));

    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutSniffer);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivation(QSystemTrayIcon::ActivationReason)));
    //sets the icon
    this->trayNormal();
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setVisible(true);

}
void MainWindow::reloadTrayTooltip(){
    trayIcon->setToolTip("Gmail Sniffer Notifier\nYou have "+QString::number(emailCount)+" unread emails");
}

void MainWindow::trayNormal(){
    trayIcon->setIcon(QIcon(":/images/gmailblue.png"));
}

void MainWindow::trayAlert(){
    trayIcon->setIcon(QIcon(":/images/gmailredsmall.png"));
}

void MainWindow::showSniffer(){
    Settings settings;
    qDebug() << settings.getSnifferPosition();
    this->setGeometry(settings.getSnifferPosition());
    this->trayNormal();
    this->show();
}
void MainWindow::hideSniffer(){
    Settings settings;
    settings.setSnifferPosition(this->geometry());
    settings.save();
    this->hide();
}

void MainWindow::trayActivation(QSystemTrayIcon::ActivationReason reason){
    if(QSystemTrayIcon::DoubleClick == reason){
        qDebug() << "Double click detected";
        this->trayNormal();
        if(this->isHidden()){
            this->showSniffer();
            this->load();
        }else{
            this->hideSniffer();
        }
    }
}

/**
 * @brief MainWindow::closeEvent override
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "closed";
    this->hideSniffer();
}

MainWindow::~MainWindow(){
    delete pNotifier;
    delete trayIcon;
    delete trayIconMenu;
    delete pSignalMapper;
    delete pNetworkManager;
    delete pTimer;
    delete ui;
}
