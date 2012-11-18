#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QHttp>
#include <QtNetwork>
#include <QWebPage>
#include <QDomDocument>
#include <QtGui>
#include "gmailatom.h"
#include "ui_mainwindow.h"
#include "dialogsettings.h"
#include "sniffernotifier.h"
#include "aboutsniffer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
     void closeEvent(QCloseEvent *event);
    
private:
    Ui::MainWindow *ui;
    QTimer *pTimer;
    QNetworkAccessManager *pNetworkManager;
    QSignalMapper *pSignalMapper;
    QPushButton *pSettingsBtn;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void createTrayIcon();
    void reloadTrayTooltip();
    void trayNormal();
    void trayAlert();

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *aboutSniffer;
    QAction *quitAction;
    QAction *settingsAction;

    SnifferNotifier *pNotifier;

    int emailCount;

public slots:
    void load();
    void result(QNetworkReply *reply);

private slots:
    void onButtonEmailClicked(QWidget* buttonEmail);
    void onSettingsClicked();
    void showAboutSnifferDialog();
    void showSniffer();
    void hideSniffer();
    void trayActivation(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
