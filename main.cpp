#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "webaxwidget.h"

/*
#include <QtQml>
#include "C:\Qt\Qt5.9.9\Examples\Qt-5.9.9\quickcontrols\controls\shared\qtquickcontrolsapplication.h"
#include "C:\Users\MSI\OneDrive\Bureau\yahyav2\calendrier\calendar\src\sqleventmodel.h"

if(w.on_Calendrier_clicked()==1)
{
    QtQuickControlsApplication app(argc, argv);
    qmlRegisterType<SqlEventModel>("org.qtproject.examples.calendar", 1, 0, "SqlEventModel");
    QQmlApplicationEngine engine(QUrl("qrc:/calendrier/calendar/qml/main.qml"));
   if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();

}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;

bool test=c.createconnect();
MainWindow w;

if(test)
{w.show();
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("connection successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("connection failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);





return a.exec();
}

