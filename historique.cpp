#include "historique.h"
#include <QDateTime>
Historique::Historique()
{

}
void Historique::save(QString cin,QString ref,QString mt,QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/MSI/Desktop/untitled_cb/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << " cin employe: "+cin+" Référence commande: "+ref+" montant: "+mt+" Date de l'action: "+dates+" Action: "+action << "\n";
}

QString Historique::load()
{   tmp="";
    QFile file("C:/Users/MSI/Desktop/untitled_cb/Historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
