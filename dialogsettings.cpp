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
#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QtCore>
#include "settings.h";
#include "mainwindow.h"

DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    this->setWindowTitle("Settings");

    ui->passwordInput->setEchoMode(QLineEdit::Password);
    Settings settings;

    QString username;
    username.append("Active account: ");
    username.append(settings.getUserName());

    ui->labelActiveUser->setText(username);
    ui->spinBoxRefresh->setValue(settings.getRefreshTime());
    ui->comboBoxBrowsers->setCurrentIndex(settings.getBrowser());

    ui->notifyPositionX->setValue(settings.getPositionX());
    ui->notifyPositionY->setValue(settings.getPositionY());
    ui->notifyWidth->setValue(settings.getWidth());
    ui->notifyHeight->setValue(settings.getHeight());
    ui->notifyDuration->setValue(settings.getDuration());
    if(settings.getSystemNotifier()){
        ui->chkSystemNotifier->setChecked(true);
        qDebug() << "is checked";
    }


    //browser



}

void DialogSettings::on_btnOk_clicked(){
    qDebug() << "OK button";
    Settings settings;
    if(!ui->userNameInput->text().isEmpty()){
        settings.setUserName(ui->userNameInput->text());
        settings.setPassword(ui->passwordInput->text());

    }

    QString browserCmd = settings.fetchBrowserCommand(ui->comboBoxBrowsers->currentIndex());
    settings.setBrowserCmd(browserCmd);
    settings.setBrowser(ui->comboBoxBrowsers->currentIndex());
    settings.setRefreshTime(ui->spinBoxRefresh->value());
    //notifier
    settings.setPositoinX(ui->notifyPositionX->value());
    settings.setPositoinY(ui->notifyPositionY->value());
    settings.setWidth(ui->notifyWidth->value());
    settings.setHeight(ui->notifyHeight->value());
    settings.setDuration(ui->notifyDuration->value());
    settings.setSystemNotifier(ui->chkSystemNotifier->isChecked());

    settings.save();

    // reload parent settings
    connect(this, SIGNAL(destroyed()), this->parentWidget(), SLOT(load()));
    this->close();
}

void DialogSettings::on_btnCancel_clicked()
{
    this->close();
}

void DialogSettings::on_pushButton_clicked()
{

    if(ui->chkSystemNotifier->isChecked()){
        QString message;
        message.append("notify-send \"");
        message.append("New Test Email");
        message.append("\" \"<br>");
        message.append("Test notify message");
        message.append("\" -i /usr/share/icons/hicolor/256x256/apps/gmailsniffer.png");
        system(message.toUtf8());
    }else{
        int x = ui->notifyPositionX->value();
        int y = ui->notifyPositionY->value();
        int width = ui->notifyWidth->value();
        int height = ui->notifyHeight->value();
        int duration = ui->notifyDuration->value();

        pNotifyTest = new SnifferNotifier(this, x, y, width, height);
        pNotifyTest->sendMessage("Test notify message<br>Test notify message", duration);
    }
}


DialogSettings::~DialogSettings()
{
    delete ui;
}
