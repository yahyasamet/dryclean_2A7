#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>

Historique::Historique()
{

}


void Historique::save_door(QString fn,QString nom,QString prenom,bool test)
{
    QDateTime date = QDateTime::currentDateTime();
    QString time=date.toString();
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/untitled2/Historique_door.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     if(test)
           out << "La carte est utilisée par: "+fn+"   Nom:"+nom+"   Prénom:"+prenom+"   Date: "+time << "\n";
          else out << "utilisateur n'est pas identifie / Pas d'acces\n";
}

QString Historique::load_door()
{   tmp="";
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/untitled2/Historique_door.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          tmp="";

        QTextStream in(&file);
    while (!in.atEnd()) {
             QString myString = in.readLine();
             tmp+=myString+"\n";
    }

       return tmp;
}
