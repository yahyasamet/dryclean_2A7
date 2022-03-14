#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>
Historique::Historique()
{

}
void Historique::save(QString cin,QString ref,QString action)
{
    QSqlQuery query;
    QString prenom;
   query.prepare("Select * from employes where cin=2" );
           query.bindValue(":cin",2) ;
           query.exec();
    query.next() ;
    prenom=query.value("prenom").toString();
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/ASUS/Documents/interface/interface/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "cin:"+cin+" Référence:"+ref+" Date:"+dates+" Action:"+action+" by: "+prenom << "\n";
}
QString Historique::load()
{   tmp="";
    QFile file("C:/Users/ASUS/Documents/interface/interface/Historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
