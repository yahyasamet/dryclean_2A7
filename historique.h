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
	
    void save_door(QString,QString,QString,bool);
    QString load_door();
};

#endif // HISTORIQUE_H
