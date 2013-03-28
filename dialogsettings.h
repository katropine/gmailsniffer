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
#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H
#include <QtCore>
#include <QDialog>
#include <QAbstractButton>
#include "mainwindow.h"
#include "sniffernotifier.h"
#include <phonon/MediaObject>
#include <phonon/MediaSource>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSettings(QWidget *parent = 0);
    ~DialogSettings();
    
private slots:

    void on_pushButton_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogSettings *ui;
    SnifferNotifier *pNotifyTest;
    Phonon::MediaObject *alertSound;

};

#endif // DIALOGSETTINGS_H
