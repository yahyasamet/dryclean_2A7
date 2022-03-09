#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QWidget"
#include <QMessageBox>
#include<QDebug>
#include "fournisseurs.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(f.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
  QString typeachats;
 QMessageBox msgBox;

    QString MATRICULE_F=ui->lineEdit_MATRICULE_F->text();
    QString NOMSOCIETE=ui->lineEdit_NOMSOCIETE->text();
    int NUMERO_TEL=ui->lineEdit_NUMERO_TEL->text().toInt();
     QString ADRESSE_SOCIETE=ui->lineEdit_ADRESSE_SOCIETE->text();
       QString EMAIL_F=ui->lineEdit_EMAIL_F->text();
       int QUANTITE_F=ui->spinBox_QUANTITE_F->text().toInt();
       int PRIX_F=ui->lineEdit_PRIX_F->text().toInt();

       int testid=0;
       for (int i=0;i==5;i++)
       {
                  if ((MATRICULE_F[i] >= 'A' && MATRICULE_F[i]<='Z') || (MATRICULE_F[i] >= 'a' && MATRICULE_F[i]<='z'))
                      testid=1;
       }

       int testid2=0;
       for (int i=8;i==10;i++)
       {
                  if ((MATRICULE_F[i] >= 'A' && MATRICULE_F[i]<='Z') || (MATRICULE_F[i] >= 'a' && MATRICULE_F[i]<='z'))
                      testid2=1;
       }



      if  (MATRICULE_F=="" || NOMSOCIETE=="" || NUMERO_TEL==0 || ADRESSE_SOCIETE=="" || EMAIL_F=="" )
            {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Ce champ ne peut pas rester vide!"), QMessageBox::Cancel);}


    else if(!ui->lineEdit_EMAIL_F->text().contains("@") || !ui->lineEdit_EMAIL_F->text().contains("."))
        {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                            QObject::tr("Adresse mail invalide!"), QMessageBox::Cancel);}

    else if (!((testid!=1) && (MATRICULE_F[6] >= 'A' && MATRICULE_F[6]<='Z') && (MATRICULE_F[7]=="/")&&(testid2!=1)))
          QMessageBox::critical(nullptr, QObject::tr("Echec"),
                      QObject::tr("Matricule fiscale doit etre de la forme 000000A/000!"), QMessageBox::Cancel);
      else

     {
            if (ui->radioButton_TYPE_ACHATF_Machine->isChecked())
            typeachats="machine";

            else if (ui->radioButton_TYPE_ACHATF_Produit->isChecked())
            typeachats="produit";


            Fournisseurs f( MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, typeachats, QUANTITE_F, PRIX_F);

      bool test=f.ajouter();

      if(test)
      {  ui->tableView->setModel(f.afficher());
      QMessageBox::information(nullptr, QObject::tr("success"),
                         QObject::tr("Ajout Effectué\n"
                                     "click cancel to exit"), QMessageBox::Cancel);

      }

      else
         {
          QMessageBox::critical(nullptr, QObject::tr("error"),
                             QObject::tr("Ajout non Effectué\n"
                                         "click cancel to exit"), QMessageBox::Cancel);
      }
      ui->tableView->setModel(f.afficher());
                     ui->lineEdit_MATRICULE_F->clear();
                     ui->lineEdit_NOMSOCIETE->clear();
                     ui->lineEdit_NUMERO_TEL->clear();
                     ui->lineEdit_ADRESSE_SOCIETE->clear();
                     ui->lineEdit_EMAIL_F->clear();
                     ui->spinBox_QUANTITE_F->clear();
                     ui->lineEdit_PRIX_F->clear();
                    ui->lineEdit_MATRICULE_F->setFocus();
      }






}


void MainWindow::on_supprimer_clicked()
{


    QString MATRICULE_F=ui->lineEdit_MATRICULE_F->text();


    bool test=f.supprimer( MATRICULE_F);

    if(test)
  {  ui->tableView->setModel(f.afficher());
    QMessageBox::information(nullptr, QObject::tr("success"),
                       QObject::tr("Suppression Effectué\n"
                                   "click cancel to exit"), QMessageBox::Cancel);

    }

    else
       {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                           QObject::tr("Suppression non Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);
    }
}


void MainWindow::on_modifier_clicked()
{

  QString typeachats1;
    QString MATRICULE_F=ui->matf->text();
    QString NOMSOCIETE=ui->nom->text();
   int NUMERO_TEL=ui->num->text().toInt();
    QString ADRESSE_SOCIETE=ui->adresse->text();
    QString EMAIL_F=ui->email->text();
    int QUANTITE_F=ui->quantite->text().toInt();
    int PRIX_F=ui->prix->text().toInt();


   if  (MATRICULE_F=="" || NOMSOCIETE=="" || NUMERO_TEL==0 || ADRESSE_SOCIETE=="" || EMAIL_F=="" )
         {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                     QObject::tr("Ce champ ne peut pas rester vide!"), QMessageBox::Cancel);}


 else if(!ui->email->text().contains("@") || !ui->email->text().contains("."))
     {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                         QObject::tr("Adresse mail invalide!"), QMessageBox::Cancel);}


else {
    if (ui->machine->isChecked())
    typeachats1="machine";

    else if (ui->produit->isChecked())
    typeachats1="produit";

 Fournisseurs f(MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, typeachats1, QUANTITE_F, PRIX_F);

        bool test=f.modifier(f.getMATRICULE_F());



        if(test)
      {  ui->tableView->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("success"),
                           QObject::tr("Modification Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);

        }

        else
           {
            QMessageBox::critical(nullptr, QObject::tr("error"),
                               QObject::tr("Modification non Effectué\n"
                                           "click cancel to exit"), QMessageBox::Cancel);
        }
        ui->tableView->setModel(f.afficher());
                       ui->matf->clear();
                       ui->nom->clear();
                       ui->num->clear();
                       ui->adresse->clear();
                       ui->email->clear();
                       ui->quantite->clear();
                       ui->prix->clear();
                      ui->matf->setFocus();
   }
}
