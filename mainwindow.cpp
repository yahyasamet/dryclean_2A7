#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include <QPixmap>
#include <QMessageBox>
#include <QIntValidator>
#include "QWidget"
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QTabWidget>
#include<QDebug>
#include<QFileDialog>
#include<QFile>
#include<QStringList>
#include <iostream>
#include<QTextDocument>
#include<QUrl>
#include <QRect>
#include <QPdfWriter>
#include <QPixmap>
#include <QValidator>
#include <QSqlRelationalDelegate>
#include <QSystemTrayIcon>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <iostream>
#include <QDir>
#include <regex>
#include <string>
#include <QRegularExpression>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/MSI/Desktop/Projet_C++_2A7/untitled/logo_c++_1.png");
    ui->label_36->setPixmap(pix);
    ui->le_ref->setValidator(new QIntValidator(0,99999,this));
    ui->supprimer_ref->setValidator(new QIntValidator(0,99999,this));
    ui->modifier_ref->setValidator(new QIntValidator(0,99999,this));
     ui->le_cin->setValidator(new QIntValidator(0,99999999,this));
      ui->modifier_cin->setValidator(new QIntValidator(0,99999999,this));
      ui->modifier_cin_emp->setValidator(new QIntValidator(0,99999999,this));
     ui->cin_empl->setValidator(new QIntValidator(0,99999999,this));
      ui->la_qtt->setValidator(new QIntValidator(0,999,this));
      ui->Modifier_qtt->setValidator(new QIntValidator(0,999,this));
      ui->modifier_montant->setValidator(new QIntValidator(0,9999,this));
       ui->le_mt->setValidator(new QIntValidator(0,999,this));
ui->date->setDate(QDate::currentDate());
ui->modifier_date->setDate(QDate::currentDate());
       ui->le_nbpt->setValidator(new QIntValidator(0,9999,this));
ui->modifier_nbr_pts->setValidator(new QIntValidator(0,9999,this));

      //Metier:Notification

      mSystemTrayIcon= new QSystemTrayIcon(this);
      mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
mSystemTrayIcon->setVisible(true);

     ui->tab_v->setModel(Etmp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    int ref_cmd=ui->le_ref->text().toInt();
    int cin_cl =ui->le_cin->text().toInt();
    int qtt_vet =ui->la_qtt->text().toInt();
    int montant_cmd =ui->le_mt->text().toInt();
    int etat=ui->etat_cmb->currentIndex();
    int nb_pts=ui->le_nbpt->text().toInt();
    int type_v=ui->type_cmb->currentIndex();
    int livraison=ui->type_livr_cmb->currentIndex();
    int cin=ui->cin_empl->text().toInt();
    QString Nom_cl=ui->le_nom->text();
    QString adr_cl=ui->la_adr->text();
    QDate Date_cmd=ui->date->date();
    QMessageBox msgbox;

    //pdf
QString ref=ui->le_ref->text();
QString cin_clS=ui->le_cin->text();
QString qtt_vetS =ui->la_qtt->text();
QString montant_cmdS =ui->le_mt->text();
QString nb_ptsS=ui->le_nbpt->text();
QString type_vS=ui->type_cmb->currentText();
QString livraisonS=ui->type_livr_cmb->currentText();
QString cinS=ui->cin_empl->text();
QString Date_cmdS=ui->date->date().toString();

    Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);

    int erreur=0;

    QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
    bool hasMatch= re.exactMatch(Nom_cl);

    QRegExp rex("^[a-zA-Z0-9_ ]*$");
    bool match=rex.exactMatch(adr_cl);

    if (!hasMatch)
        erreur=1;
    if(C.entierValide(cin_cl)!=8)
        erreur=2;
        if(C.entierValide(qtt_vet)>5)
            erreur=3;
        if(C.entierValide(montant_cmd)>5)
            erreur=4;
        if(!C.DateValide(Date_cmd))
            erreur=5;
        if(!match)
            erreur=7;
        if(!C.entierValide(nb_pts))
            erreur=8;
        if(!C.entierValide(cin))
            erreur=11;

if (erreur==0)
  {  bool test =C.ajouter();
    if (test)
       {



        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
        bool test1=C.genererFacture(ref,cin_clS,qtt_vetS,Date_cmdS,montant_cmdS,type_vS,livraisonS,cinS,Nom_cl);
        if(!test1)
           { QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                                       QObject::tr("Facture non générer\n"
                                                   "click cancel to exit"),QMessageBox::Cancel);  }
        else
        {QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("Facture générer avec succés\n"
                                              "Click cancel to exit."),QMessageBox::Cancel);}
    ui->tab_v->setModel(Etmp.afficher());
    ui->le_ref->clear();
    ui->le_cin->clear();
    ui->le_mt->clear();
    ui->la_adr->clear();
    ui->la_qtt->clear();
    ui->le_nom->clear();
    ui->cin_empl->clear();
     ui->le_nbpt->clear();


    }
    else
    {QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                           QObject::tr("Ajout non effectué.\n"
                                       "click cancel to exit"),QMessageBox::Ok);}

}else  if (erreur==1)
{ QMessageBox::critical(nullptr,QObject::tr("Nom non valide"),
                         QObject::tr("Ajout nn effectue\n"
                                     "click cancel to exit"),QMessageBox::Cancel);  }
else if(erreur==2)
{QMessageBox::critical(nullptr,QObject::tr("le cin du client est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==3)
{QMessageBox::critical(nullptr,QObject::tr("la quantité est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==4)
{QMessageBox::critical(nullptr,QObject::tr("le montant est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==5)
{QMessageBox::critical(nullptr,QObject::tr("la date est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==7)
{QMessageBox::critical(nullptr,QObject::tr("l'adresse est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                  "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==8)
{QMessageBox::critical(nullptr,QObject::tr("le nombre de points est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==11)
{QMessageBox::critical(nullptr,QObject::tr("le cin de l'employe est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}

}
void MainWindow::on_pb_supprimer_clicked()
{
    Commande c;
   int ref_cmd=ui->supprimer_ref->text().toInt();
    c.setRef(ui->supprimer_ref->text().toInt());

if(c.recherche_id(ref_cmd)==true)
{ bool test=c.supprimer(c.getRef());
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuee\n"
                                                                       "Click cancel to exit."), QMessageBox::Cancel);
ui->tab_v->setModel(Etmp.afficher());
ui->supprimer_ref->clear();
    }
    else
    {QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                           QObject::tr("Suppression non effectué.\n"
                                       "click cancel to exit"),QMessageBox::Cancel);}
}else {QMessageBox::critical(nullptr,QObject::tr("Reference introuvable"),
                             QObject::tr("Suppression non effectué.\n"
                                         "click cancel to exit"),QMessageBox::Cancel);}

}


void MainWindow::on_pb_modifier_clicked()
{
    int ref_cmd=ui->modifier_ref->text().toInt();
       QString adr_cl=ui->modifier_adr->text();
       QString Nom_cl=ui->modifier_nom->text();
       int cin_cl =ui->modifier_cin->text().toInt();
       int cin =ui->modifier_cin_emp->text().toInt();
       int qtt_vet =ui->Modifier_qtt->text().toInt();
       int montant_cmd =ui->modifier_montant->text().toInt();
       int etat=ui->modifier_etat->currentIndex();
       int nb_pts=ui->modifier_nbr_pts->text().toInt();
       int type_v=ui->modifier_type->currentIndex();
       int livraison=ui->modifier_livraison->currentIndex();
         QDate Date_cmd=ui->modifier_date->date();

       Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);
       //C.set_ref_equipement(ui->lineEdit_13->text().toInt());
      int erreur=0;
       QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
       bool hasMatch= re.exactMatch(Nom_cl);

       QRegExp rex("^[a-zA-Z0-9_ ]*$");
       bool match=rex.exactMatch(adr_cl);

       if (!hasMatch)
           erreur=1;
       if(C.entierValide(cin_cl)!=8)
           erreur=2;
           if(C.entierValide(qtt_vet)>5)
               erreur=3;
           if(C.entierValide(montant_cmd)>5)
               erreur=4;
           if(!C.DateValide(Date_cmd))
               erreur=5;
           if(!match)
               erreur=7;
           if(!C.entierValide(nb_pts))
               erreur=8;
           if(!C.entierValide(cin))
               erreur=11;


           if (erreur==0)
             {if(C.recherche_id(ref_cmd)==true)
      { bool test=C.modifier(C.getRef()) ;

           QMessageBox msgBox;
           if(test)
           {QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Modification effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);
               if(etat==1)
               {mSystemTrayIcon ->showMessage(tr("Notification"),tr("La commande n° %1 est prete.Veuillez Consulter la base de donnee").arg(ref_cmd));}
               ui->tab_v->setModel(C.afficher());
           }
           else
         {  QMessageBox::information(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification Non effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);}

               }

else {QMessageBox::critical(nullptr,QObject::tr("OK"),
                               QObject::tr("Modification non effectué\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);}

           }
           else  if (erreur==1)
           { QMessageBox::critical(nullptr,QObject::tr("Nom non valide"),
                                    QObject::tr("Modification nn effectue\n"
                                                "click cancel to exit"),QMessageBox::Cancel);  }
           else if(erreur==2)
           {QMessageBox::critical(nullptr,QObject::tr("le cin du client est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==3)
           {QMessageBox::critical(nullptr,QObject::tr("la quantité est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==4)
           {QMessageBox::critical(nullptr,QObject::tr("le montant est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==5)
           {QMessageBox::critical(nullptr,QObject::tr("la date est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==7)
           {QMessageBox::critical(nullptr,QObject::tr("l'adresse est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                             "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==8)
           {QMessageBox::critical(nullptr,QObject::tr("le nombre de points est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==11)
           {QMessageBox::critical(nullptr,QObject::tr("le cin de l'employe est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}

}

void MainWindow::on_comboBox_2_activated(int index)
{
    if(index==0)
    {
          ui->tab_v->setModel(Etmp.afficherTrierDescDate());
    }
    else if(index==1)
    {
        ui->tab_v->setModel(Etmp.afficherTrierAscDate());
    }
    else if(index==2)
    {
      ui->tab_v->setModel(Etmp.afficherTrierDescMontant());
    }
    else if(index==3)
    {
      ui->tab_v->setModel(Etmp.afficherTrierAscMontant());
    }
    else if(index==4)
    {
      ui->tab_v->setModel(Etmp.afficherTrierDescLivr());
    }
}


