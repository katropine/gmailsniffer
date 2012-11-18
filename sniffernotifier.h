#ifndef SNIFFERNOTIFIER_H
#define SNIFFERNOTIFIER_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QRect>
#include "settings.h"

namespace Ui {
class SnifferNotifier;
}

class SnifferNotifier : public QWidget
{
    Q_OBJECT
    
public:
    explicit SnifferNotifier(QWidget *parent = 0);
    explicit SnifferNotifier(QWidget *parent, int x, int y, int width, int height);
    ~SnifferNotifier();
    void sendMessage(QString data);
    void sendMessage(QString data, int duration);

public slots:
    void showWidget();
    void hideWidget();
    
private:
    Ui::SnifferNotifier *ui;

    QTimer *timer;
    QDesktopWidget *desktop;
    QSize windowSize;
    int getTopPanel();
    Settings *pSettings;

    int x;
    int y;
    int screenWidth, width, originalWidth;
    int screenHeight, height, originalHeight;
};

#endif // SNIFFERNOTIFIER_H
