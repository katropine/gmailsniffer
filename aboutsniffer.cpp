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
#include "aboutsniffer.h"
#include "ui_aboutsniffer.h"

AboutSniffer::AboutSniffer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutSniffer)
{
    ui->setupUi(this);
    this->setWindowTitle("About Gmail Sniffer");
    this->setWindowIcon(QIcon(":/images/gmailredsmall.png"));

}

AboutSniffer::~AboutSniffer()
{
    delete ui;
}
