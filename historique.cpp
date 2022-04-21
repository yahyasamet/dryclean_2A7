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
void Historique::saveA(QString name,QString cin,QString nb,QString g)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/MSI/Desktop/untitled_cb/HistoriqueA.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << " cin employe: "+g+ " cin client: "+cin+ " Nom client: "+name+ "Nombre de points:" +nb+ " Date du scan: "+dates << "\n";



}
QString Historique::loadA()
{
    tmp="";
      QFile file("C:/Users/MSI/Desktop/untitled_cb/HistoriqueA.txt");
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
