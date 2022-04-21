#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

class Historique
{
    QString tmp;
public:
    Historique();
    void save(QString,QString,QString,QString);
    QString load();
    void saveA(QString,QString,QString,QString);
    QString loadA();

};

#endif // HISTORIQUE_H
