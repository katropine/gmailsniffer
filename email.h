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
