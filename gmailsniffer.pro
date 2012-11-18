#-------------------------------------------------
#
# Project created by QtCreator 2012-10-27T12:20:41
#
#-------------------------------------------------

QT       += core gui network webkit xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gmail
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gmailatom.cpp \
    email.cpp \
    dialogsettings.cpp \
    settings.cpp \
    sniffernotifier.cpp \
    aboutsniffer.cpp \
    simplecrypt.cpp

HEADERS  += mainwindow.h \
    gmailatom.h \
    email.h \
    dialogsettings.h \
    settings.h \
    sniffernotifier.h \
    aboutsniffer.h \
    simplecrypt.h

FORMS    += \
    mainwindow.ui \
    dialogsettings.ui \
    sniffernotifier.ui \
    aboutsniffer.ui

RESOURCES += \
    systrey.qrc
