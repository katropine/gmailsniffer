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
#include "gmailatom.h"
#include <QDebug>
#include <QNetworkReply>
#include <QDomDocument>
#include "email.h"

/***
<entry>
    <title>email title</title>
    <summary>email summary</summary>
    <link rel="alternate" href="link_to_the_email" type="text/html"/>
    <modified>2012-09-25T14:16:49Z</modified>
    <issued>2012-09-25T14:16:49Z</issued>
    <id>tag:gmail.google.com,2004:1414091358027121800</id>
    <author>
        <name>Kristian</name>
        <email>kristian@katropine.com</email>
    </author>
 </entry>
*/

GmailAtom::GmailAtom(QNetworkReply *reply)
{

    if(!document.setContent(reply)){
        qDebug() << "Failed to load document";
    }
    //qDebug() << document.toString();

}
QMap<int, Email> GmailAtom::fetch(){
    //qDebug() << document.toString();
    QDomNodeList items = document.elementsByTagName("entry");
    int cnt = items.count();
    QMap<int, Email> Emails;
    if(cnt > 0){
        qDebug() << items.count();
        //QDomElement rootOfEntry = document.firstChildElement();
        for(int i=0; i < cnt; i++){
           QDomElement rootOfEntry = items.at(i).toElement();

           Email email;
           email.setTitle(rootOfEntry.elementsByTagName("title").at(0).toElement().text().trimmed());
           email.setSummary(rootOfEntry.elementsByTagName("summary").at(0).toElement().text().trimmed());
           email.setAuthorName(rootOfEntry.elementsByTagName("name").at(0).toElement().text().trimmed());
           email.setLink(rootOfEntry.elementsByTagName("link").at(0).toElement().attribute("href").trimmed());
           email.setIssued(rootOfEntry.elementsByTagName("issued").at(0).toElement().text().trimmed());
           Emails.insert(i, email);
       }
        document.clear();
    }else{
        qDebug() << "XML empty";
    }

    return Emails;
}


GmailAtom::~GmailAtom(){

}
