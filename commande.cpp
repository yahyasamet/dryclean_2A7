#include "commande.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include<QPdfWriter>
#include <QPrintDialog>

Commande::Commande()
{
    QDate date1(1995,2,2);
    ref_cmd="";cin_cl="";qtt_vet=0;montant_cmd=0;etat_cmd=0;nb_pts=0;type_vet=0;opt_livr=0;
       Nom_cl=" ",adr_cl=" ";
        Date_cmd=date1;
}
Commande::Commande(QString ref_cmd,QString cin_cl,QString Nom_cl,int qtt_vet,int montant_cmd, QDate Date_cmd,int etat_cmd,QString adr_cl,int nb_pts, int type_vet, int opt_livr,QString cin_emp)
{
    this ->ref_cmd=ref_cmd;
    this ->cin_cl=cin_cl;
    this ->qtt_vet=qtt_vet;
    this ->montant_cmd=montant_cmd;
    this ->etat_cmd=etat_cmd;
    this ->nb_pts=nb_pts;
    this ->type_vet=type_vet;
    this ->opt_livr=opt_livr;
    this ->Nom_cl=Nom_cl;
    this ->adr_cl=adr_cl;
    this ->Date_cmd=Date_cmd;
     this ->cin_emp=cin_emp;
}
QString Commande::getRef()
{return ref_cmd;}
QString Commande::getNomcl()
{return Nom_cl;}
QString Commande::getAdrcl()
{return adr_cl;}
QString Commande::getCincl()
{return cin_cl;}
int Commande::getQttvet()
{return qtt_vet;}
int Commande::getMtcmd()
{return montant_cmd;}
int Commande::getEtatCmd()
{return etat_cmd;}
int Commande::getNbPt()
{return nb_pts;}
int Commande::getTypeVet()
{return type_vet;}
int Commande::getOptLivr()
{return opt_livr;}
QDate Commande::getDateCmd()
{return  Date_cmd;}
void Commande::setRef(QString ref_cmd)
{this->ref_cmd=ref_cmd;}
void Commande::setNomcl(QString Nom_cl)
{this->Nom_cl=Nom_cl;}
void Commande::setAdrcl(QString adr_cl)
{this->adr_cl=adr_cl;}
void Commande::setCincl(QString cin_cl)
{this->cin_cl=cin_cl;}
void Commande::setQttvet(int qtt_vet)
{this ->qtt_vet=qtt_vet;}
void Commande::setMtcmd(int montant_cmd)
{this->montant_cmd=montant_cmd;}
void Commande::setEtatCmd(int etat_cmd)
{this->etat_cmd=etat_cmd;}
void Commande::setNbPt(int nb_pts)
{this->nb_pts=nb_pts;}
void Commande::setTypeVet(int type_vet)
{this->type_vet=type_vet;}
void Commande::setOptLivr(int opt_livr)
{this->opt_livr=opt_livr;}
void Commande::setDateCmd(QDate Date_cmd)
{this ->Date_cmd=Date_cmd;}
void Commande::setCinCl(QString cin_emp)
{this ->cin_emp=cin_emp;}


bool Commande::ajouter()
{

    QSqlQuery query;
   /* QString ref_string=QString::number(ref_cmd);
    QString cin_string=QString::number(cin_cl);
    QString qtt_string=QString::number(qtt_vet);
    QString montant_string=QString::number(montant_cmd);
    QString etat_string=QString::number(etat_cmd);
    QString nbpts_string=QString::number(nb_pts);
    QString opt_string=QString::number(opt_livr);
    QString typevet_string=QString::number(type_vet);
    QDate date= QDate::currentDate();*/

          query.prepare("INSERT INTO commandes (ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat_cmd,adr_cl,nb_pts,type_vet,opt_livraison,cin_employe) "
                        "VALUES (:ref_cmd, :cin_cl, :Nom_cl, :qtt_vet, :montant_cmd, :Date_cmd, :etat_cmd, :adr_cl, :nb_pts, :type_vet, :opt_livraison, :cin_employe)");
          query.bindValue(0, ref_cmd);
          query.bindValue(1, cin_cl);
          query.bindValue(2, Nom_cl);
          query.bindValue(3, qtt_vet);
           query.bindValue(4, montant_cmd);
           query.bindValue(5, Date_cmd);
            query.bindValue(6,etat_cmd);
            query.bindValue(7, adr_cl);
             query.bindValue(8, nb_pts);
              query.bindValue(9, type_vet);
               query.bindValue(10, opt_livr);
                query.bindValue(11, cin_emp);

          return query.exec();
}
bool Commande::supprimer(QString ref_cmd)
{
    QSqlQuery query;

    query.prepare("Delete from commandes where ref_cmd= :ref_cmd");
    query.bindValue(":ref_cmd",ref_cmd);
    return query.exec();
}

 QSqlQueryModel * Commande::afficher()
 {
QSqlQueryModel *model= new QSqlQueryModel();
model->setQuery("select * from commandes");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
return model;
 }
 QString Commande::recherche_cin_arduino_nb_pts(QString cin)
 {
     qDebug() <<cin;
     QMessageBox msgBox;
     QSqlQuery query,q1;
     query.prepare("SELECT * From(SELECT ROWNUM , nom_cl,montant_cmd,nb_pts FROM commandes WHERE cin_cl= :cin order by ref_cmd DESC)WHERE ROWNUM=1");
     query.bindValue(":cin", cin);
     if (query.exec() && query.next())
     {

              return query.value(3).toString();


     }
     else
     {
        return "false";
     }
 }
 QString Commande::recherche_cin_arduino(QString cin)
 {
     QMessageBox msgBox;
     QSqlQuery query,q1;
     query.prepare("SELECT * From(SELECT ROWNUM , nom_cl,montant_cmd,nb_pts FROM commandes WHERE cin_cl= :cin order by ref_cmd DESC)WHERE ROWNUM=1");
     query.bindValue(":cin", cin);
     if (query.exec() && query.next())
     {
         int m=(query.value(2).toInt()) *0.1;
         q1.prepare("update commandes set nb_pts =nb_pts+:m WHERE cin_cl= :cin ");
              q1.bindValue(":cin", cin);
               q1.bindValue(":m", m);
              q1.exec();
              return query.value(1).toString();


     }
     else
     {
        return "false";
     }
 }
 QString Commande::recherche_cin_arduino_emp(QString cin)
 {
    // qDebug() <<cin;
     QMessageBox msgBox;
     QSqlQuery query,q1;
     query.prepare("SELECT * From(SELECT ROWNUM ,cin_employe FROM commandes WHERE cin_cl= :cin order by ref_cmd DESC)WHERE ROWNUM=1");
     query.bindValue(":cin", cin);
     if (query.exec() && query.next())
     {

              return query.value(1).toString();


     }
     else
     {
        return "false";
     }
 }
 bool Commande::recherche_id(QString ref_cmd)
  {
      QMessageBox msgBox;
      QSqlQuery query;
      query.prepare("SELECT * FROM commandes WHERE ref_cmd= :ref_cmd");
      query.bindValue(":ref_cmd", ref_cmd);
      if (query.exec() && query.next())
      {
              return true;
      }
      else
      {
          return false;
      }
  }

 /*int Commande::recherche_id(int ref_cmd)
 {
     QSqlQuery query;
     query.prepare("SELECT * from commandes WHERE ref_cmd= :ref_cmd");
     query.bindValue(" :ref_cmd",ref_cmd);
     int count(0);
     if(query.exec())
     {

         while(query.next())
         {
             count++;
         }
     }
     return count;

 }*/
bool Commande::modifier(QString ref_cmd)
{

    QSqlQuery query;
     query.prepare("Update commandes set cin_cl= :cin_cl, Nom_cl= :Nom_cl , qtt_vet= :qtt_vet , montant_cmd= :montant_cmd , Date_cmd= :Date_cmd , etat_cmd= :etat_cmd , adr_cl= :adr_cl , nb_pts= :nb_pts , type_vet= :type_vet , opt_livraison= :opt_livraison , cin_employe= :cin_employe where ref_cmd= :ref_cmd ");

     query.bindValue(":ref_cmd",ref_cmd);
     query.bindValue(":cin_cl", cin_cl);
     query.bindValue(":Nom_cl", Nom_cl);
     query.bindValue(":qtt_vet", qtt_vet);
     query.bindValue(":montant_cmd", montant_cmd);
      query.bindValue(":Date_cmd", Date_cmd);
       query.bindValue(":adr_cl", adr_cl);
       query.bindValue(":etat_cmd", etat_cmd);
         query.bindValue(":nb_pts", nb_pts);
         query.bindValue(":type_vet", type_vet);
         query.bindValue(":opt_livraison", opt_livr);
         query.bindValue(":cin_employe", cin_emp);

    return query.exec();
    }
QSqlQueryModel * Commande::afficherTrierDescDate()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from commandes order by Date_cmd DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
    return model;


}

QSqlQueryModel * Commande::afficherTrierAscDate()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from commandes order by Date_cmd ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
    return model;


}
QSqlQueryModel * Commande::afficherTrierAscMontant()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from commandes order by montant_cmd ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
    return model;

}
QSqlQueryModel * Commande::afficherTrierDescMontant()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from commandes order by montant_cmd DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
       model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
    return model;

}
 QSqlQueryModel * Commande::afficherTrierDescLivr()
 {
     QSqlQueryModel *model= new QSqlQueryModel();
     model->setQuery("select * from commandes order by opt_livraison DESC");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
     model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
     model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));
     return model;

 }

int Commande::entierValide(int entier)
{
    int Retour = 0;
        while(entier !=0)
        {
            Retour++;
            entier = entier / 10;
        }

        return Retour;
}
bool Commande::DateValide(QDate Date)
{
    if (Date!=QDate::currentDate())
       {return false;}
    else return true;
}
QSqlQueryModel * Commande::Recherche_Avancee(QString arg)
{
    QSqlQueryModel *model= new QSqlQueryModel();
     model->setQuery("select * from commandes WHERE ((ref_cmd ) LIKE '%"+arg+"%') or ((Nom_cl ) LIKE '%"+arg+"%') ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref_cmd"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Qtt"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Montant"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("Adresse"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("nb_pts"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("type_v"));
     model->setHeaderData(10,Qt::Horizontal,QObject::tr("Opt_livr"));
     model->setHeaderData(11,Qt::Horizontal,QObject::tr("cin_empl"));


return model;
}

