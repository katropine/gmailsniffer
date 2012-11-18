#include "settings.h"
#include "simplecrypt.h"
#include <QtCore>

Settings::Settings(){

    this->width = 350;
    this->height = 80;
    this->duration = 5;
    this->seconds = 30; // refresh time
    this->positionX = 1;
    this->positionY = 1;

    pSettings = new QSettings("Katropine", "GmailSniffer");

    pSettings->beginGroup("User");
    this->setUserName(pSettings->value("username").toString());

    SimpleCrypt crypt(Settings::salt);
    QString hash = crypt.decryptToString(pSettings->value("password").toString());
    this->setPassword(hash);

    this->setBrowser(pSettings->value("browser").toInt());
    this->setBrowserCmd(pSettings->value("browser_cmd").toString());
    int refresh = this->seconds;
    if(pSettings->value("refresh").toInt() > 0){
        refresh = pSettings->value("refresh").toInt();
    }
    this->setRefreshTime(refresh);
    pSettings->endGroup();

    pSettings->beginGroup("Notifiction");
    this->setSystemNotifier(pSettings->value("use_sys_notification").toBool());
    this->setPositoinX(pSettings->value("position_x").toInt());
    this->setPositoinY(pSettings->value("position_y").toInt());
    this->setWidth(pSettings->value("width").toInt());
    this->setHeight(pSettings->value("height").toInt());
    this->setDuration(pSettings->value("duration").toInt());
    pSettings->endGroup();

    pSettings->beginGroup("Geometry");
    this->setSnifferPosition(pSettings->value("position").toRect());
    pSettings->endGroup();

}

void Settings::setUserName(QString userName){
    this->userName = userName;
}

void Settings::setPassword(QString password){
    this->password = password;
}

void Settings::setBrowserCmd(QString browserCmd){
    this->browserCmd = browserCmd;
}

void Settings::setBrowser(int browser){
    this->browser = browser;
}
void Settings::setRefreshTime(int seconds){
    this->seconds = seconds;
}

// notification
void Settings::setPositoinX(int x){
    this->positionX = x;
}

void Settings::setPositoinY(int y){
    this->positionY = y;
}

void Settings::setWidth(int width){
    this->width = width;
}

void Settings::setHeight(int height){
    this->height = height;
}

void Settings::setDuration(int duration){
    this->duration = duration;
}
void Settings::setSnifferPosition(QRect rect){
    this->snifferPosition = rect;
}
void Settings::setSystemNotifier(bool sysNotify){
    this->sysNotify = sysNotify;
}

QString Settings::getUserName(){
    return this->userName;
}

QString Settings::getPassword(){
    return this->password;
}

QString Settings::getBrowserCmd(){
    return this->browserCmd;
}

int Settings::getBrowser(){
    return this->browser;
}

int Settings::getPositionX(){
    return this->positionX;
}

int Settings::getPositionY(){
    return this->positionY;
}
int Settings::getWidth(){
    return this->width;
}

int Settings::getHeight(){
    return this->height;
}

int Settings::getDuration(){
    return this->duration;
}
int Settings::getRefreshTime(){
    return this->seconds;
}

QRect Settings::getSnifferPosition(){
    return this->snifferPosition;
}
bool Settings::getSystemNotifier(){
    return this->sysNotify;
}

void Settings::save(){
    pSettings->beginGroup("User");
    if(!this->userName.isEmpty()){
        pSettings->setValue("username", this->userName);
    }
    if(!this->password.isEmpty()){
        SimpleCrypt crypt(Settings::salt);
        QString hash = crypt.encryptToString(this->password);
        pSettings->setValue("password", hash);
    }
    if(!this->browserCmd.isEmpty()){
        pSettings->setValue("browser", this->browser);
        pSettings->setValue("browser_cmd", this->browserCmd);
    }
    pSettings->setValue("refresh", this->seconds);
    pSettings->endGroup();

    pSettings->beginGroup("Notifiction");
    pSettings->setValue("use_sys_notification", this->sysNotify);
    pSettings->setValue("position_x", this->positionX);
    pSettings->setValue("position_y", this->positionY);
    pSettings->setValue("width",this->width);
    pSettings->setValue("height", this->height);
    pSettings->setValue("duration", this->duration);
    pSettings->endGroup();

    pSettings->beginGroup("Geometry");
    pSettings->setValue("position", this->snifferPosition);
    pSettings->endGroup();

}

QString Settings::fetchBrowserCommand(const int browserID){
    QMap<int, QString> browser;
    browser.insert(0, "default");
    browser.insert(1, "firefox");
    browser.insert(2, "chromium");
    browser.insert(3, "opera");
    browser.insert(4, "iceweasel");
    browser.insert(5, "konqueror");
    return browser[browserID];
}

Settings::~Settings(){
    delete pSettings;
}
