QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteApp
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
        main.cpp \
    remotewindow.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    remotewindow.h
