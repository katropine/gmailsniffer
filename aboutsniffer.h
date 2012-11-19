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
#ifndef ABOUTSNIFFER_H
#define ABOUTSNIFFER_H

#include <QDialog>

namespace Ui {
class AboutSniffer;
}

class AboutSniffer : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutSniffer(QWidget *parent = 0);
    ~AboutSniffer();
    
private:
    Ui::AboutSniffer *ui;
};

#endif // ABOUTSNIFFER_H
