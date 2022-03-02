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
#include <QPixmap>
#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/MSI/Desktop/Projet_C++_2A7/untitled/logo_c++_1.png");
    ui->label_36->setPixmap(pix);

    ui->le_ref->setValidator(new QIntValidator(0,999,this));
      ui->le_cin->setValidator(new QIntValidator(0,9999999,this));
      ui->la_qtt->setValidator(new QIntValidator(0,999,this));
       ui->le_mt->setValidator(new QIntValidator(0,999,this));

       ui->le_nbpt->setValidator(new QIntValidator(0,999,this));

      ui->supprimer_ref->setValidator(new QIntValidator(0,999,this));
      ui->modifier_ref->setValidator(new QIntValidator(0,999,this));
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
    QString Nom_cl=ui->le_nom->text();
    QString adr_cl=ui->la_adr->text();
    QDate Date_cmd=ui->date->date();

    Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison);
    bool test =C.ajouter();
    if (test)
       { QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
    ui->tab_v->setModel(Etmp.afficher());}
    else
    {QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                           QObject::tr("Ajout non effectué.\n"
                                       "click cancel to exit"),QMessageBox::Cancel);}

}
void MainWindow::on_pb_supprimer_clicked()
{
    Commande c;
    c.setRef(ui->supprimer_ref->text().toInt());

    bool test=c.supprimer(c.getRef());
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
}

void MainWindow::on_pb_modifier_clicked()
{
    int ref_cmd=ui->modifier_ref->text().toInt();
       QString adr_cl=ui->modifier_adr->text();
       QString Nom_cl=ui->modifier_nom->text();
       int cin_cl =ui->modifier_cin->text().toInt();
       int qtt_vet =ui->Modifier_qtt->text().toInt();
       int montant_cmd =ui->modifier_montant->text().toInt();
       int etat=ui->modifier_etat->currentIndex();
       int nb_pts=ui->modifier_nbr_pts->text().toInt();
       int type_v=ui->modifier_type->currentIndex();
       int livraison=ui->modifier_livraison->currentIndex();
         QDate Date_cmd=ui->modifier_date->date();
       Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison);
       //C.set_ref_equipement(ui->lineEdit_13->text().toInt());
           bool test=C.modifier(C.getRef()) ;

           QMessageBox msgBox;
           if(test)
           {msgBox.setText("modification avec succes.");
               ui->tab_v->setModel(C.afficher());
           }
           else
           msgBox.setText("Echec de modification");
               msgBox.exec();

}
