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
