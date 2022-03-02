#include "commande.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
Commande::Commande()
{
    QDate date1(1995,2,2);
    ref_cmd=0;cin_cl=0;qtt_vet=0;montant_cmd=0;etat_cmd=0;nb_pts=0;type_vet=0;opt_livr=0;
       Nom_cl=" ",adr_cl=" ";
        Date_cmd=date1;
}
Commande::Commande(int ref_cmd,int cin_cl,QString Nom_cl,int qtt_vet,int montant_cmd, QDate Date_cmd,int etat_cmd,QString adr_cl,int nb_pts, int type_vet, int opt_livr)
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
}
int Commande::getRef()
{return ref_cmd;}
QString Commande::getNomcl()
{return Nom_cl;}
QString Commande::getAdrcl()
{return adr_cl;}
int Commande::getCincl()
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
void Commande::setRef(int ref_cmd)
{this->ref_cmd=ref_cmd;}
void Commande::setNomcl(QString Nom_cl)
{this->Nom_cl=Nom_cl;}
void Commande::setAdrcl(QString adr_cl)
{this->adr_cl=adr_cl;}
void Commande::setCincl(int cin_cl)
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
void Commande::getDateCmd(QDate Date_cmd)
{this ->Date_cmd=Date_cmd;}
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

          query.prepare("INSERT INTO commandes (ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat_cmd,adr_cl,nb_pts,type_vet,opt_livraison) "
                        "VALUES (:ref_cmd, :cin_cl, :Nom_cl, :qtt_vet, :montant_cmd, :Date_cmd, :etat_cmd, :adr_cl, :nb_pts, :type_vet, :opt_livraison)");
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

          return query.exec();
}
bool Commande::supprimer(int ref_cmd)
{
    QSqlQuery query;
    QString res=QString::number(ref_cmd);
    query.prepare("Delete from commandes where ref_cmd= :ref_cmd");
    query.bindValue(":ref_cmd",res);
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
return model;

 }
 bool Commande::recherche_id(int ref_cmd)
 {
     QMessageBox msgBox;
            QSqlQuery query;
             QString id_string=QString::number(ref_cmd);
            query.prepare("SELECT * FROM PRODUIT WHERE ref_cmd= :ref_cmd");
            query.bindValue(":ref_cmd", id_string);
            if (query.exec() && query.next())
            {
                    return true;
            }
            else
            {
                msgBox.setText("commande n existe pas");
                msgBox.exec();
                return false;
            }

 }
bool Commande::modifier(int ref_cmd)
{

    QSqlQuery query;
     query.prepare("Update commandes set cin_cl= :cin_cl, Nom_cl= :Nom_cl , qtt_vet= :qtt_vet , montant_cmd= :montant_cmd , Date_cmd= :Date_cmd , etat_cmd= :etat_cmd , adr_cl= :adr_cl , nb_pts= :nb_pts , type_vet= :type_vet , opt_livraison= :opt_livraison  where ref_cmd= :ref_cmd ");

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
    // query.bindValue(":CIN", CIN);

    return query.exec();
    }
