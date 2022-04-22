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

    void save_f(QString,QString);
    QString load_f();

    void save_e(QString,QString,QString);
    QString load_e();
	
	void save_door(QString,QString,QString);
    QString load_door();

};

#endif // HISTORIQUE_H
