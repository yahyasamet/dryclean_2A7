QT       += core gui sql printsupport widgets network multimedia charts serialport axcontainer qml  quickwidgets quick opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp \
    fournisseurs.cpp \
    smtp.cpp \
    barcode.cpp \
    barcodebox.cpp \
    historique.cpp \
    commande.cpp \
    finances.cpp \
    chat.cpp \
    equipements.cpp \
    widget.cpp \
    livraisons.cpp \
    secformdialog.cpp \
    sqleventmodel.cpp\
    event.cpp\
    qrcode.cpp

HEADERS += \
    arduino.h \
    connection.h \
    employe.h \
    mainwindow.h \
    fournisseurs.h \
    smtp.h \
    barcode.h \
    barcodebox.h \
    historique.h \
    commande.h \
    finances.h \
    chat.h \
    equipements.h \
    widget.h \
    livraisons.h \
secformdialog.h \
    webaxwidget.h\
    event.h\
sqleventmodel.h\
qtquickcontrolsapplication.h\
qrcode.h


FORMS += \
    mainwindow.ui \
    secformdialog.ui

OTHER_FILES += qml/main.qml

TRANSLATIONS += english.ts
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = myappico.ico

QMAKE_CXXFLAGS+=-std=gnu++14

RESOURCES += \
    english.qrc \
    res.qrc \
    Ressources.qrc \
    img.qrc \
    resources.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols/controls/calendar
INSTALLS += target
