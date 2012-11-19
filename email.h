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
#ifndef EMAIL_H
#define EMAIL_H
#include <QString>

class Email {
    public:
        Email();
        void setTitle(QString title);
        void setSummary(QString summary);
        void setAuthorName(QString autorMame);
        void setLink(QString link);
        void setIssued(QString issued);
        QString getTitle();
        QString getSummary();
        QString getAuthorName();
        QString getLink();
        QString getIssued();
        QString __toString();

    private:
        QString title;
        QString summary;
        QString autorMame;
        QString link;
        QString issued;
};

#endif // EMAIL_H
