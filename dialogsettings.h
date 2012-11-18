#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H
#include <QtCore>
#include <QDialog>
#include <QAbstractButton>
#include "mainwindow.h"
#include "sniffernotifier.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSettings(QWidget *parent = 0);
    ~DialogSettings();
    
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_clicked();

private:
    Ui::DialogSettings *ui;
    SnifferNotifier *pNotifyTest;

};

#endif // DIALOGSETTINGS_H
