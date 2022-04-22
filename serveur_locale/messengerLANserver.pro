QT       += core

QT       -= gui
QT       += network

TARGET = messengerLANserver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    MessengerServer.cpp \
    MessengerSocket.cpp

QMAKE_CXXFLAGS += -std=gnu++11


#HEADERS += \
#    mainwindow.h

#FORMS += \
#    mainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MessengerServer.h \
    MessengerSocket.h
