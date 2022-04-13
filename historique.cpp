#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>
#include "widget.h"
Historique::Historique()
{

}
void Historique::save(QString cin,QString ref,QString action)
{
    QSqlQuery query;
    QString prenom;
   query.prepare("Select * from employe where cin=2" );
           query.bindValue(":cin",2) ;
           query.exec();
    query.next() ;
    prenom=query.value("prenom").toString();
    widget w;
    int day = QDateTime::currentDateTime().date().day();
    int month = QDateTime::currentDateTime().date().month();
    int year = QDateTime::currentDateTime().date().year();

    QString time=w.get_temps();
    QString dates=QString::number(day)+"/"+QString::number(month)+"/"+QString::number(year);
    QFile file ("C:/Users/ASUS/Documents/interface/interface/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "cin:"+cin+"  Référence:"+ref+"  Date:"+dates+"  Temps:"+time+"  Action:"+action+" by: "+prenom << ".\n";
}
QString Historique::load()
{   tmp="";
    QFile file("C:/Users/ASUS/Documents/interface/interface/Historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);
    int i=0;
    QString color="#09B9FF";

   while (!in.atEnd()) {
       switch (i) {
       case 0:
       color="#09B9FF";
       break;
       case 1:
           color="#0A8DFF";
       break;
       case 2:
           color="#0070D1";
       break;
       case 3:
           color="#024A7D";
           break;
       }

         QString myString = in.readLine();
         tmp+="<font color="+color+">"+myString+"\n<br><br> <font>";
         i++;
         if(i==4)
             i=0;

   }
   return tmp;
}
