#ifndef GMAILATOM_H
#define GMAILATOM_H
#include <QDebug>
#include <QNetworkReply>
#include <QDomDocument>
#include "email.h"

class GmailAtom
{
public:
    GmailAtom(QNetworkReply *reply);
    ~GmailAtom();
    QMap<int, Email> fetch();

private:
    QDomDocument document;
};

#endif // GMAILATOM_H
