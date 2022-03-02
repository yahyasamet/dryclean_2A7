#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QWidget"
#include <QMessageBox>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QTabWidget>
#include<QDebug>
#include<QFileDialog>
#include<QPdfWriter>
#include<QFile>
#include<QStringList>
#include <iostream>
#include<QTextDocument>
#include<QUrl>
#include <QPixmap>
#include <QValidator>
#include <QIntValidator>
#include "finances.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    ui->radioButton->setChecked(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ajouter_clicked()
{

    int ID_FINANCES=ui->id->text().toInt();
    int MONTANT_FINANCE=ui->montant->text().toInt();
    int TYPE_TRANSACTION1;
    if (ui->radioButton->isChecked())
    TYPE_TRANSACTION1=0;
    else
    TYPE_TRANSACTION1=1;
    QString PROVENANCE=ui->provenance->text();
    QDate DATE_FINANCES=ui->date->date();
    finances C( DATE_FINANCES, TYPE_TRANSACTION1, PROVENANCE, MONTANT_FINANCE, ID_FINANCES);

    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    ui->id->clear();
    ui->montant->clear();
    ui->provenance->clear();
    ui->date->clear();
    // Put the focus back into the input box so they can type again:
   ui->id->setFocus();
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}
void MainWindow::on_supprimer_clicked()
{

    int id=ui->id_3->text().toInt();


    bool test=C.supprimer(id);
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("supprimer avec succée");
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    ui->id->clear();

    // Put the focus back into the input box so they can type again:
   ui->id_3->setFocus();
    }

    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{

    QMessageBox msg;

    finances C;
    C.setID_FINANCES(ui->id_2->text().toInt());
    C.setDATE_FINANCES(ui->date_2->date());
    C.setPROVENANCE(ui->provenance_2->text());
    C.setMONTANT_FINANCE(ui->montant_2->text().toInt());
    if (ui->radioButton->isChecked())
     C.setTYPE_TRANSACTION(0);
    else
     C.setTYPE_TRANSACTION(1);


    bool test=C.modifier(C.getID_FINANCES());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tabledepence->setModel(C.afficher());
        ui->tablerevenue->setModel(C.afficher2());


    }
    else
        msg.setText("echec de modification");

    msg.exec();
}
