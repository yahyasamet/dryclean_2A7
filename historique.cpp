#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>
#include "widget.h"

Historique::Historique()
{

}
void Historique::save(QString cin,QString ref,QString mt,QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_commande.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << " cin employe: "+cin+" Référence commande: "+ref+" montant: "+mt+" Date de l'action: "+dates+" Action: "+action << "\n";
}

QString Historique::load()
{   tmp="";
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_commande.txt");
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
                      color="#6f85d1";
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

void Historique::save_f(QString id,QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_finance.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "id:"+id+" Date:"+dates+" Action:"+action << "\n";
}
QString Historique::load_f()
{   tmp="";
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_finance.txt");
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

void Historique::save_e(QString cin,QString ref,QString action)
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
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_equipements.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "cin:"+cin+"  Référence:"+ref+"  Date:"+dates+"  Temps:"+time+"  Action:"+action+" by: "+prenom << ".\n";
}
QString Historique::load_e()
{   tmp="";
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_equipements.txt");
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

void Historique::save_door(QString cin,QString nom,QString prenom,QString ch)
{
    QDateTime date = QDateTime::currentDateTime();
    QString time=date.toString();
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_door.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "cin:"+cin+" Nom:"+nom+" Prénom:"+prenom+" Time:"+time+" "+ch << "\n";
}

QString Historique::load_door()
{   tmp="";
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Historique_door.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          tmp="";

        QTextStream in(&file);

             QString myString = in.readLine();
             tmp+=myString+"\n<br><br>";

       return tmp;
}
