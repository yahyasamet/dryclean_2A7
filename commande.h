#ifndef COMMANDE_H
#define COMMANDE_H
#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSharedDataPointer>
#include <QPrintDialog>
#include <QPrinter>

class Commande
{
public:
    Commande();
     Commande(QString ref_cmd,QString cin_cl, QString Nom_cl,int qtt_vet,int montant_cmd,QDate Date_cmd,int etat_cmd,QString adr_cl,int nb_pts, int type_vet, int opt_livr, QString cin_emp);
    QString getRef();
     QString getNomcl();
     QString getAdrcl();
     QString getCincl();
     int getQttvet();
     int getMtcmd();
     int getEtatCmd();
     int getNbPt();
     int getTypeVet();
     int getOptLivr();
     QString getCinCl();
     QDate getDateCmd();
     void setRef(QString);
    void setNomcl(QString);
     void setAdrcl(QString);
     void setCincl(QString);
     void setQttvet(int);
     void setMtcmd(int);
     void setEtatCmd(int);
     void setNbPt(int);
     void setTypeVet(int);
     void setOptLivr(int);
     void getDateCmd(QDate);
       void setDateCmd(QDate);
       void setCinCl(QString);

     bool ajouter();
     QSqlQueryModel * afficherTrierDescDate();
     QSqlQueryModel * afficherTrierAscDate();
     QSqlQueryModel * afficherTrierAscMontant();
     QSqlQueryModel * afficherTrierDescMontant();
     QSqlQueryModel * afficherTrierDescLivr();
     bool supprimer(QString);
     QSqlQueryModel * afficher();
     bool recherche_id(QString);
     QString recherche_cin_arduino(QString);
      QString recherche_cin_arduino_nb_pts(QString cin);
     bool modifier(QString);
     //bool genererFacture(QString ref,QString cinS,QString qtt,QString Date,QString mt,QString type,QString livr,QString cin_e,QString nom);
bool NomValide(QString chaine);
bool adresseValide(QString adresse);
int entierValide(int entier);
bool DateValide(QDate Date);
//bool PrintFacture(QString ref, QString cinS, QString qtt, QString Date, QString mt, QString type, QString livr, QString cin_e, QString nom);
QSqlQueryModel * Recherche_Avancee(QString arg1);

private:
         int qtt_vet,montant_cmd,etat_cmd,nb_pts,type_vet,opt_livr;
             QString ref_cmd,cin_cl,Nom_cl,adr_cl,cin_emp;
             QDate Date_cmd;
};

#endif // COMMANDE_H
