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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>

class Settings
{
public:
    Settings();
    ~Settings();
    static const int salt = 254568546;

    void save();
    QString fetchBrowserCommand(const int browserID);

    void setUserName(QString userName);
    void setPassword(QString password);
    void setBrowser(int browser);
    void setBrowserCmd(QString browserCmd);
    void setPositoinX(int x);
    void setPositoinY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setDuration(int duration);
    void setSnifferPosition(QRect rect);
    void setRefreshTime(int seconds);
    void setSystemNotifier(bool sysNotify);

    QString getUserName();
    QString getPassword();
    int getBrowser();
    QString getBrowserCmd();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    int getDuration();
    int getRefreshTime();
    QRect getSnifferPosition();
    bool getSystemNotifier();

protected:
    QString userName;
    QString password;
    int browser;
    QString browserCmd;
    int positionX;
    int positionY;
    int width;
    int height;
    int duration;
    int seconds;
    QRect snifferPosition;
    bool sysNotify;

private:
    QSettings *pSettings;
};

#endif // SETTINGS_H
