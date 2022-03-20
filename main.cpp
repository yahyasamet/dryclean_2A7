#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QStringList langues;
        QTranslator t;
        langues<<"Anglais"<<"Français";
        QString choix=QInputDialog::getItem(NULL,"CHOISIR","Langue",langues);
        if(choix=="Anglais")
        {
            t.load(":/english.qm");
        }
        if(choix!="Français")
        {
            a.installTranslator(&t);
        }*/

    Connection c;
    c.connect();

    MainWindow w;
    w.show();
    return a.exec();
}
