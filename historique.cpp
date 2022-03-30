#include "historique.h"
#include <QDateTime>
Historique::Historique()
{

}
void Historique::save(QString id,QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("C:/Users/ramya/OneDrive/Bureau/dry cleaning/finance/Historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << "id:"+id+" Date:"+dates+" Action:"+action << "\n";
}
QString Historique::load()
{   tmp="";
    QFile file("C:/Users/ramya/OneDrive/Bureau/dry cleaning/finance/Historique.txt");
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
