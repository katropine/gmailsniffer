/**
 * This file is Copyright 2012
 *     Kristian Beres <admin@katropine.com>
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
#include "email.h"
#include <QString>
#include <QDateTime>
/***
<entry>
    <title>email title</title>
    <summary>email summary</summary>
    <link rel="alternate" href="link_to_the_email" type="text/html"/>
    <modified>2012-09-25T14:16:49Z</modified>
    <issued>2012-09-25T14:16:49Z</issued>
    <id>tag:gmail.google.com,2004:1414091358027121800</id>
    <author>
        <name>ivanka</name>
        <email>ivanka@test.com</email>
    </author>
 </entry>
*/

Email::Email(){
    //entity class
}

void Email::setTitle(QString title){
    this->title = title;
}

void Email::setSummary(QString summary){
    this->summary = summary;
}

void Email::setAuthorName(QString autorMame){
    this->autorMame = autorMame;
}
void Email::setLink(QString link){
    this->link = link;
}
void Email::setIssued(QString issued){
    this->issued = issued;
}

QString Email::getTitle(){
    return this->title;
}

QString Email::getSummary(){
    return this->summary;
}

QString Email::getAuthorName(){
    return  this->autorMame;
}

QString Email::getLink(){
    return  this->link;
}

QString Email::getIssued(){
    return this->issued;
}

QString Email::__toString(){
    QString buttonText;

    QString title;
    if(this->getTitle().length() > 43){
        title = this->getTitle().left(40).append("...");
    }else{
        title = this->getTitle();
    }

    buttonText.append(title);
    buttonText.append("\n");
    buttonText.append(QDateTime::fromString(this->getIssued(), "yyyy-MM-ddThh:mm:ssZ").toString("HH:mm:ss ddd MMM dd yyyy"));
    buttonText.append("\n");
    //buttonText.append(this->getSummary());
    //buttonText.append("\n");
    buttonText.append(this->getAuthorName());

    return buttonText;
}
