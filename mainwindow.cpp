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
 livraisons L(id,date_lv,nom_lv);
     bool test=L.ajouter_livraisons();
     QMessageBox msgbox;
     if(test)
     {msgbox.setText("Ajout avec succes.");
         ui->tableView->setModel(L.afficher_livraisons());
        // ui->lineEdit_8->setText("");
        // ui->lineEdit_9->setText("");
        // ui->lineEdit_10->setText("");
 //        ui->lineEdit_11->setText("");
       //  ui->lineEdit_12->setText("");

     }
     else
         msgbox.setText("Echec d'ajout");
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

    bool test=C.modifier_livraison(C.get_id());
    if(test)
    {
        msg.setText("modification avec succès");
       ui->tableView->setModel(C.afficher_livraisons());


    }
    else
        msg.setText("echec de modification");

    msg.exec();
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{


    if(arg1=="date decroissante")
        ui->tableView->setModel(C.afficherTrierDescDate());
        else if(arg1=="date croissante")
        ui->tableView->setModel(C.afficherTrierAscDate());


}
