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
#include <QtGui>

#include <QVariant>
#include <QAbstractEventDispatcher>
#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  setFixedSize(1300,750);


   this->showAddrWeb();
  connect(ui->goPushButton,SIGNAL(clicked(bool)),this,SLOT(showAddrWeb()));


    ui->le_id->setValidator(new QIntValidator(0,99999999,this));

     ui->tableView->setModel(C.afficher_livraisons());
     ui->tableView->horizontalHeader()->setStretchLastSection(true);

     QDate date = QDate::currentDate();
        ui->la_date->setDate(date);
        ui->la_date_2->setDate(date);

        //combox
     QSqlQuery qry,qry1,qry2;
         qry.prepare("select REF_CMD from COMMANDES WHERE OPT_LIVRAISON=1 ");
             qry.exec();
             while(qry.next()){
             ui->le_ref_cmd->addItem(qry.value(0).toString());
             ui->le_ref_cmd_2->addItem(qry.value(0).toString());
         }
         qry1.prepare("select ID_LIVR from livraisons");
             qry1.exec();
             while(qry1.next()){
              ui->le_id_2->addItem(qry1.value(0).toString());
              ui->le_id_3->addItem(qry1.value(0).toString());
              ui->le_id_4->addItem(qry1.value(0).toString());
             }

         qry2.prepare("SELECT ID_LIVR,NOM_LIVREUR,DATE_LIVRAISON,REF_CMD,NOM_CL,ADR_CL FROM livraisons NATURAL JOIN COMMANDES");
             qry2.exec();
             QStringList completionlist;
             while(qry2.next()){
                 completionlist <<qry2.value("NOM_LIVREUR").toString()<<qry2.value("ID_LIVR").toString()<<qry2.value("DATE_LIVRAISON").toString()<<qry2.value("REF_CMD").toString()<<qry2.value("NOM_CL").toString()<<qry2.value("ADR_CL").toString();
             }

             stringcompleter=new QCompleter(completionlist,this);
             stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
             ui->Rechercher_livraisons->setCompleter(stringcompleter);







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
 int ref_cmd=ui->le_ref_cmd->currentText().toInt();



 livraisons L(id,date_lv,nom_lv,ref_cmd);
     QMessageBox msgbox;
     int erreur=0;
         if(!L.NOM_Valid(nom_lv) || nom_lv=="")
         erreur=1;
         if(L.DateValide(date_lv))
         erreur=2;
         if(L.chercher_ref(ref_cmd)>=1)
          erreur=3;
         if(L.chercher_id(id)>=1)
          erreur=4;

         switch(erreur)
         {
         case 1:
         msgbox.setText("Le nom doit être composé seulement par des lettres !");
         break;
         case 2:
         msgbox.setText("La date doit être suppérieur à la date actuel !");
         break;
         case 3:
         msgbox.setText("reference deja existe !");
         break;
         case 4:
         msgbox.setText("ID deja existe !");
         break;

         }
 if(erreur==0)
   {
             bool test=L.ajouter_livraisons();

     if(test)
     {msgbox.setText("Ajout avec succes.");
         ui->tableView->setModel(L.afficher_livraisons());
         ui->le_id->clear();
         //mise a jour des id
          ui->le_id_2->clear();
          ui->le_id_3->clear();
          ui->le_id_4->clear();
         QSqlQuery qry1;
         qry1.prepare("select ID_LIVR from livraisons");
             qry1.exec();
             while(qry1.next()){
              ui->le_id_2->addItem(qry1.value(0).toString());
              ui->le_id_3->addItem(qry1.value(0).toString());
              ui->le_id_4->addItem(qry1.value(0).toString());
             }

         ui->le_nom->clear();
         QDate date = QDate::currentDate();
            ui->la_date->setDate(date);



     }
     else
         msgbox.setText("Echec d'ajout");

   }
msgbox.exec();

}
void MainWindow::on_supprimer_clicked()
{


    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
           int id = index.data(Qt::DisplayRole).toInt();

         QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {

               bool test=C.supprimer_livraison(id);
               if(test)
               {
         ui->tableView->setModel(C.afficher_livraisons());
         QMessageBox::information(nullptr,"Suppression","case supprimé");
         //mise a jour des id
          ui->le_id_2->clear();
          ui->le_id_3->clear();
          ui->le_id_4->clear();
         QSqlQuery qry1;
         qry1.prepare("select ID_LIVR from livraisons");
             qry1.exec();
             while(qry1.next()){
              ui->le_id_2->addItem(qry1.value(0).toString());
              ui->le_id_3->addItem(qry1.value(0).toString());
              ui->le_id_4->addItem(qry1.value(0).toString());
             }

               }
               else
                   QMessageBox::information(nullptr,"Suppression","echc de supprimé");
           }
}


void MainWindow::on_modifier_clicked()
{
    livraisons C;
    QMessageBox msg;






    C.set_id(ui->le_id_2->currentText().toInt());
    C.set_nom_lv(ui->le_nom_2->text());
    C.set_date_lv(ui->la_date_2->date());
    C.set_ref_cmd(ui->le_ref_cmd_2->currentText().toInt());
    int erreur=0;
        if(!C.NOM_Valid(C.get_nom_lv()) || C.get_nom_lv()=="")
        erreur=1;
        if(C.DateValide( C.get_date_lv()))
        erreur=2;
        if(C.chercher_ref(C.get_ref_cmd())>=1)
         erreur=3;
        if(C.chercher_id(C.get_id())>=1)
         erreur=4;

        switch(erreur)
        {
        case 1:
        msg.setText("Le nom doit être composé seulement par des lettres !");
        break;
        case 2:
        msg.setText("La date doit être suppérieur à la date actuel !");
        break;
        case 3:
        msg.setText("reference deja existe !");
        break;
        case 4:
        msg.setText("ID deja existe !");
        break;

        }
if(erreur==0)
  {
    bool test=C.modifier_livraison(C.get_id());
    if(test)
    {
        msg.setText("modification avec succès");
       ui->tableView->setModel(C.afficher_livraisons());
       ui->le_nom_2->clear();
       QDate date = QDate::currentDate();
          ui->la_date_2->setDate(date);


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
              int id=ui->le_id_4->currentText().toInt(); //on supprime si tout livraisins
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



void MainWindow::on_le_id_2_activated()
{



        QSqlQuery query;
        QString ID_LIVR=ui->le_id_2->currentText() ;
       query.prepare("Select * from livraisons where ID_LIVR=:ID_LIVR" );
               query.bindValue(":ID_LIVR",ID_LIVR) ;
               query.exec();
        query.next() ;

        ui->le_nom_2->setText(query.value(1).toString());
        ui->la_date_2->setDate(query.value(2).toDate());
        ui->le_ref_cmd_2->setCurrentText(query.value(3).toString());

}



void MainWindow::on_Rechercher_livraisons_textEdited(const QString &arg1)
{
   ui->tableView->setModel(C.Recherche_Avancee(arg1));
}





void MainWindow::on_Rechercher_livraisons_textChanged(const QString &arg1)
{
  ui->tableView->setModel(C.Recherche_Avancee(arg1));
}
void MainWindow::webShow(const QString &url)
{
    ui->webBrowser->dynamicCall("Navigate(const QString&)", url);
}

void MainWindow::showAddrWeb()
{
    QString addr="https://www.google.com/maps/place/"+on_le_id_3_activated();
    webShow(addr);

}



QString MainWindow::on_le_id_3_activated()
{


    QSqlQuery query;
    QString ID_LIVR=ui->le_id_3->currentText() ;
   query.prepare("SELECT ID_LIVR,NOM_LIVREUR,DATE_LIVRAISON,REF_CMD,NOM_CL,ADR_CL FROM livraisons NATURAL JOIN COMMANDES where ID_LIVR=:ID_LIVR" );
           query.bindValue(":ID_LIVR",ID_LIVR) ;
           query.exec();
    query.next() ;

     QString ADR_CL=query.value(5).toString();

    return  ADR_CL;
}
