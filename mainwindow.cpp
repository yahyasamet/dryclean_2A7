#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraisons.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QUrl>
#include <QPdfWriter>
#include <QPainter>
#include <QPointF>
#include <QPicture>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tableView->setModel(C.afficher_livraisons());
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_2_clicked()
{

 int id=ui->le_id->text().toInt();
 QString nom_lv=ui->le_nom->text();
 QDate date_lv=ui->la_date->date();
// QString date_lv2=date_lv.toString("yyyy,dd,MM");
 int ref_cmd=ui->le_ref_cmd->text().toInt();

 livraisons L(id,date_lv,nom_lv,ref_cmd);
     QMessageBox msgbox;
     int erreur=0;
         if(!L.NOM_Valid(nom_lv) || nom_lv=="")
         erreur=1;
         if(!L.DateValide(date_lv))
         erreur=2;

         switch(erreur)
         {
         case 1:
         msgbox.setText("Le nom doit être composé seulement par des lettres !");
         break;
         case 2:
         msgbox.setText("La date doit être suppérieur à la date actuel !");
         break;

         }
 if(erreur==0)
   {
             bool test=L.ajouter_livraisons();

     if(test)
     {msgbox.setText("Ajout avec succes.");
         ui->tableView->setModel(L.afficher_livraisons());
         ui->le_id->clear();
         ui->le_nom->clear();
         ui->le_ref_cmd->clear();



     }
     else
         msgbox.setText("Echec d'ajout");

   }
msgbox.exec();

}
void MainWindow::on_supprimer_clicked()
{

    int id=ui->le_id_3->text().toInt();

    bool test=C.supprimer_livraison(id);
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("supprimer avec succée");
    ui->tableView->setModel(C.afficher_livraisons());

    // Put the focus back into the input box so they can type again:
   ui->le_id_3->setFocus();
    }

    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
    livraisons C;
    QMessageBox msg;
    C.set_id(ui->le_id_2->text().toInt());
    C.set_nom_lv(ui->le_nom_2->text());
    C.set_date_lv(ui->la_date_2->date());
    C.set_ref_cmd(ui->le_ref_cmd_2->text().toInt());
    int erreur=0;
        if(!C.NOM_Valid(C.get_nom_lv()) || C.get_nom_lv()=="")
        erreur=1;
        if(!C.DateValide( C.get_date_lv()))
        erreur=2;

        switch(erreur)
        {
        case 1:
        msg.setText("Le nom doit être composé seulement par des lettres !");
        break;
        case 2:
        msg.setText("La date doit être suppérieur à la date actuel !");
        break;

        }
if(erreur==0)
  {
    bool test=C.modifier_livraison(C.get_id());
    if(test)
    {
        msg.setText("modification avec succès");
       ui->tableView->setModel(C.afficher_livraisons());
       ui->le_id_2->clear();
       ui->le_nom_2->clear();
       ui->le_ref_cmd_2->clear();


    }
    else
        msg.setText("echec de modification");

  }




    msg.exec();
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{


    if(arg1=="date decroissante")
    ui->tableView->setModel(C.afficherTrierDescDate());
    else if(arg1=="date croissante")
    ui->tableView->setModel(C.afficherTrierAscDate());
    else if(arg1=="ID decroissant")
    ui->tableView->setModel(C.afficherTrierAscId());
    else if(arg1=="ID croissant")
    ui->tableView->setModel(C.afficherTrierDescId());


}

void MainWindow::on_pushButton_5_clicked()
{
    QPdfWriter pdf("C:\\Users\\MSI\\OneDrive\\Bureau\\PDF_livraisons.pdf");

       QPainter painter(&pdf);
       int i = 4000;
             QImage image("C:\\Users\\MSI\\OneDrive\\Bureau\\yahyav2\\images\\logo_c++-1.png");
             painter.drawImage(-20,-30,image);

              painter.setPen(Qt::red);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Bon de Livraison");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,100,9400,2500); // dimension ta3 rectangle eli fih liste des  livraisons
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(400,3300,"ID");
              painter.drawText(1350,3300,"Nom livreure");
              painter.drawText(2900,3300,"Date livraisons");
              painter.drawText(4500,3300,"Reference Commande");
              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              int id=ui->le_id_4->text().toInt(); //on supprime si tout livraisins
              query.prepare("select * from livraisons where ID_LIVR=:ID_LIVR");   //on supprime  where ID_LIVR=:ID_LIVR si tout livraisins
              query.bindValue(":ID_LIVR", id);   //on supprime si tout livraisins
              query.exec();
            //  while (query.next()) on utilise selemnt pour affichier tou les livraisons
             // {
              query.next(); //on supprime si tout livraisins
                  painter.drawText(400,i,query.value(0).toString());
                  painter.drawText(1350,i,query.value(1).toString());
                  painter.drawText(2900,i,query.value(2).toString());
                  painter.drawText(4500,i,query.value(3).toString());


               //  i = i + 350;
             // }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}
