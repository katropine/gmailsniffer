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
