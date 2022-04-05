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
#include "barcode.h"
#include <QBoxLayout>
#include "historique.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/MSI/Desktop/untitled_cb/logo_c++_1.png");
    QPixmap pix1("C:/Users/MSI/Desktop/untitled_cb/search.png");
    ui->label_36->setPixmap(pix);
    ui->label_14->setPixmap(pix1);
    ui->modifier_cin_emp_cmb->addItem("");
    ui->modifier_combo->addItem("");
   // ui->modifier_etat->addItem("");
   // ui->modifier_livraison->addItem("");
    //ui->modifier_type->addItem("");


    label = new QLabel("Code：",this);
  lineEdit = new QLineEdit(this);
 // cin= new QComboBox(this);
  produceCode128Button = new QPushButton("code128",this);
   // produceEAN13Button = new QPushButton("EAN13",this);
    savePictureButton = new QPushButton("save",this);
    barCodeBox = new BarCodeBox("Code",this);

   // QHBoxLayout *hBoxLayout = new QHBoxLayout();
    ui->hBoxLayout->addWidget(label);
   ui-> hBoxLayout->addWidget(lineEdit);
   ui->hBoxLayout->addWidget(produceCode128Button);
 // ui-> hBoxLayout->addWidget(produceEAN13Button);
  ui-> hBoxLayout->addWidget(savePictureButton);

  // QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    //vBoxLayout->addLayout(hBoxLayout);
   ui-> vBoxLayout->addWidget(barCodeBox);

   /*QSqlQuery qry1;
   qry1.prepare("select cin_cl from commandes");
   qry1.exec();

         while(qry1.next()){

         //ui->cin->addItem(qry1.value(0).toString());
          }*/



    connect(produceCode128Button,SIGNAL(clicked()),this,SLOT(produceBarCode128Slot()));
    //connect(produceEAN13Button,SIGNAL(clicked()),this,SLOT(produceBarCodeEAN13Slot()));
  connect(savePictureButton,SIGNAL(clicked()),this,SLOT(savePictureSlot()));

    //this->resize(1400,1300);
    ui->le_ref->setValidator(new QIntValidator(0,99999,this));
    //ui->supprimer_ref->setValidator(new QIntValidator(0,99999,this));
   // ui->modifier_ref->setValidator(new QIntValidator(0,99999,this));
     ui->le_cin->setValidator(new QIntValidator(0,99999999,this));
      ui->modifier_cin->setValidator(new QIntValidator(0,99999999,this));
      //ui->modifier_cin_emp->setValidator(new QIntValidator(0,99999999,this));
     //ui->cin_empl->setValidator(new QIntValidator(0,99999999,this));
      ui->la_qtt->setValidator(new QIntValidator(0,999,this));
      ui->Modifier_qtt->setValidator(new QIntValidator(0,999,this));
      ui->modifier_montant->setValidator(new QIntValidator(0,9999,this));
       ui->le_mt->setValidator(new QIntValidator(0,999,this));
ui->date->setDate(QDate::currentDate());
ui->modifier_date->setDate(QDate::currentDate());
       ui->le_nbpt->setValidator(new QIntValidator(0,9999,this));
ui->modifier_nbr_pts->setValidator(new QIntValidator(0,9999,this));
//ui->modifier_etat->addItem("");
       // ui->modifier_type->addItem("");
        //ui->modifier_livraison->addItem("");

QSqlQuery qry,qry2,qry1;
       qry.prepare("select ref_cmd from commandes");
       qry.exec();
       qry2.prepare("select cin from employes");
       qry2.exec();
       //ui->combo_cin_2->addItem("");
      while(qry.next()){

     // ui->supprimer_combo->addItem(qry.value(0).toString());
      ui->modifier_combo->addItem(qry.value(0).toString());
       }
      // ui->combo_ref->addItem("");
       while(qry2.next()){
       ui->cin_empl_cmb->addItem(qry2.value(0).toString());
       ui->modifier_cin_emp_cmb->addItem(qry2.value(0).toString());}
qry1.prepare("select * from commandes");
qry1.exec();
QStringList completionlist;
while(qry1.next()){
              completionlist <<qry1.value("ref_cmd").toString() <<qry1.value("Nom_cl").toString();
          }
StringCompleter=new QCompleter(completionlist,this);
           StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
           ui->recherche->setCompleter(StringCompleter);


       Historique h;
                 ui->historique->setText(h.load());




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
    QString ref_cmd=ui->le_ref->text();
    QString cin_cl =ui->le_cin->text();
    int qtt_vet =ui->la_qtt->text().toInt();
    int montant_cmd =ui->le_mt->text().toInt();
    int etat=ui->etat_cmb->currentIndex();
    int nb_pts=ui->le_nbpt->text().toInt();
    int type_v=ui->type_cmb->currentIndex();
    int livraison=ui->type_livr_cmb->currentIndex();
   QString cin=ui->cin_empl_cmb->currentText();
    QString Nom_cl=ui->le_nom->text();
    QString adr_cl=ui->la_adr->text();
    QDate Date_cmd=ui->date->date();
    QMessageBox msgbox;

    //pdf


QString qtt_vetS =ui->la_qtt->text();
QString montant_cmdS =ui->le_mt->text();
QString nb_ptsS=ui->le_nbpt->text();
QString type_vS=ui->type_cmb->currentText();
QString livraisonS=ui->type_livr_cmb->currentText();

QString Date_cmdS=ui->date->date().toString();

    Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);

    int erreur=0;

    QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
    bool hasMatch= re.exactMatch(Nom_cl);

    QRegExp rex("^[a-zA-Z0-9_ ]*$");
    bool match=rex.exactMatch(adr_cl);

    if (!hasMatch)
        erreur=1;
    if(cin_cl.length()!=8)
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
        //if(cin.length()!=8)
           // erreur=11;

if (erreur==0)
  {  bool test =C.ajouter();
    if (test)
       {



        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
        bool test1=C.genererFacture(ref_cmd,cin_cl,qtt_vetS,Date_cmdS,montant_cmdS,type_vS,livraisonS,cin,Nom_cl);
        Historique h;
            h.save(cin,ref_cmd,montant_cmdS,"Ajout");
            ui->historique->setText(h.load());
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
     ui->le_nbpt->clear();
     //ui->supprimer_combo->clear();
     ui->modifier_combo->clear();
     QSqlQuery qry;
     qry.prepare("select ref_cmd from commandes");
     qry.exec();
     while(qry.next()){

    // ui->supprimer_combo->addItem(qry.value(0).toString());
     ui->modifier_combo->addItem(qry.value(0).toString());
      }

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
    QString ref_cmd = ui->tab_v->selectionModel()->currentIndex().data(Qt::DisplayRole).toString();
 QString cin,mt;
 QSqlQuery query;

            query.prepare("Select * from commandes where ref_cmd=:ref_cmd" );
                    query.bindValue(":ref_cmd",ref_cmd) ;

                    query.exec();

                    query.next() ;
                   cin=query.value(11).toString();
                    mt=query.value(4).toString();




 Etmp.supprimer(ref_cmd);
        ui->tab_v->setModel(Etmp.afficher());



        Historique h;
                        h.save(cin,ref_cmd,mt,"Supprimer");
                        ui->historique->setText(h.load());

}


void MainWindow::on_pb_modifier_clicked()
{
    QString ref_cmd=ui->modifier_combo->currentText();
       QString adr_cl=ui->modifier_adr->text();
       QString Nom_cl=ui->modifier_nom->text();
       QString cin_cl =ui->modifier_cin->text();
       QString cin =ui->modifier_cin_emp_cmb->currentText();
       int qtt_vet =ui->Modifier_qtt->text().toInt();
       int montant_cmd =ui->modifier_montant->text().toInt();
       int etat=ui->modifier_etat->currentIndex();
       int nb_pts=ui->modifier_nbr_pts->text().toInt();
       int type_v=ui->modifier_type->currentIndex();
       int livraison=ui->modifier_livraison->currentIndex();
         QDate Date_cmd=ui->modifier_date->date();
         QString cin_clS=ui->modifier_cin_emp_cmb->currentText();
 QString montant_cmds =ui->modifier_montant->text();
 QString ref=ui->modifier_combo->currentText();


       Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);
       //C.set_ref_equipement(ui->lineEdit_13->text().toInt());
      int erreur=0;
       QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
       bool hasMatch= re.exactMatch(Nom_cl);

       QRegExp rex("^[a-zA-Z0-9_ ]*$");
       bool match=rex.exactMatch(adr_cl);

       if (!hasMatch)
           erreur=1;
           if(C.entierValide(qtt_vet)>5)
               erreur=3;
           if(C.entierValide(montant_cmd)>5)
               erreur=4;
           if(!match)
               erreur=7;
           if(!C.entierValide(nb_pts))
               erreur=8;
         //  if(cin.length()!=8)
               //erreur=11;


           if (erreur==0)
             {if(C.recherche_id(ref_cmd)==true)
      { bool test=C.modifier(C.getRef()) ;

           QMessageBox msgBox;
           if(test)
           {QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Modification effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);
               Historique h;
                              h.save(cin_clS,ref,montant_cmds,"Modification");
                              ui->historique->setText(h.load());
               if(etat==1)
               {mSystemTrayIcon ->showMessage(tr("Notification"),tr("La commande n° %1 est prete.").arg(ref_cmd));}
               ui->tab_v->setModel(C.afficher());
           }
           else
         {  QMessageBox::information(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification Non effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);}

               }

else {QMessageBox::critical(nullptr,QObject::tr("Reference introuvable"),
                               QObject::tr("Modification non effectué\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);}

           }
           else  if (erreur==1)
           { QMessageBox::critical(nullptr,QObject::tr("Nom non valide"),
                                    QObject::tr("Modification nn effectue\n"
                                                "click cancel to exit"),QMessageBox::Cancel);  }

           else if(erreur==3)
           {QMessageBox::critical(nullptr,QObject::tr("la quantité est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==4)
           {QMessageBox::critical(nullptr,QObject::tr("le montant est non valide"),
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



/*void MainWindow::on_recuperer_clicked()
{
    QSqlQuery query;
        QString ref=ui->modifier_combo->currentText();
       query.prepare("Select * from commandes where ref_cmd=:ref_cmd" );
               query.bindValue(":ref_cmd",ref) ;
               query.exec();
        query.next() ;
       // E.recuperer_equipement(ref_cmd);
        ui->modifier_cin->setText(query.value(1).toString());
        ui->modifier_nom->setText(query.value(2).toString());
        ui->Modifier_qtt->setText(query.value(3).toString());
       ui->modifier_montant->setText(query.value(4).toString());
       ui->modifier_date->setDate(query.value(5).toDate());
       ui->modifier_adr->setText(query.value(6).toString());
       ui->modifier_etat->setCurrentText(query.value(7).toString());
       ui->modifier_nbr_pts->setText(query.value(8).toString());
       ui->modifier_type->setCurrentText(query.value(9).toString());
       ui->modifier_livraison->setCurrentText(query.value(10).toString());
       ui->modifier_cin_emp_cmb->setCurrentText(query.value(11).toString());


}*/

void MainWindow::on_modifier_combo_activated(int index)
{
    QSqlQuery query;
        QString ref_cmd=ui->modifier_combo->currentText() ;
       query.prepare("Select * from commandes where ref_cmd=:ref_cmd" );
               query.bindValue(":ref_cmd",ref_cmd) ;
               query.exec();
        query.next() ;

        ui->modifier_cin->setText(query.value(1).toString());
        ui->modifier_nom->setText(query.value(2).toString());
        ui->Modifier_qtt->setText(query.value(3).toString());
       ui->modifier_montant->setText(query.value(4).toString());
       ui->modifier_date->setDate(query.value(5).toDate());
       ui->modifier_etat->setCurrentIndex(query.value(6).toInt());
        ui->modifier_adr->setText(query.value(7).toString());
       ui->modifier_nbr_pts->setText(query.value(8).toString());
       ui->modifier_type->setCurrentIndex(query.value(9).toInt());
       ui->modifier_livraison->setCurrentIndex(query.value(10).toInt());
       ui->modifier_cin_emp_cmb->setCurrentText(query.value(11).toString());
}

void MainWindow::on_supprimer_combo_activated(int index)
{

}

void MainWindow::produceBarCode128Slot()
{
    QString code=lineEdit->text();
    BarCode code128;//Définit l'objet qui encode le numéro de code-barres
    QString barCodes;//Enregistrez la chaîne bs, indiquant b : ligne noire s : ligne blanche
    if((barCodes=code128.process128BCode(code))!=NULL)
    {
        barCodeBox->setBarCodes(barCodes);//Définir les valeurs des variables utilisées dans les fonctions de dessin
        barCodeBox->update();
    }
}

void MainWindow::produceBarCodeEAN13Slot()
{
    QString code=lineEdit->text();//Obtenir le numéro saisi

    BarCode codeEAN13;//Définit l'objet qui encode le numéro de code-barres
    QString barCodes;//Enregistrez 01 chaînes, indiquant 1 : ligne noire 0 : ligne blanche
    if((barCodes=codeEAN13.processEAN13Code(code))!=NULL)
    {
        barCodeBox->setBarCodes(barCodes);//Définir les valeurs des variables utilisées dans les fonctions de dessin
        barCodeBox->update();//repeindre
    }
}

void MainWindow::savePictureSlot()
{
    barCodeBox->savePicture();
}

void MainWindow::on_recherche_textChanged(const QString &arg)
{
ui->tab_v->setModel(Etmp.Recherche_Avancee(arg));
}
