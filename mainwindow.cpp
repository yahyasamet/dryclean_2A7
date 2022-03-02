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

    QString MATRICULE_F=ui->lineEdit_MATRICULE_F->text();
    QString NOMSOCIETE=ui->lineEdit_NOMSOCIETE->text();
    int NUMERO_TEL=ui->lineEdit_NUMERO_TEL->text().toInt();
    QString ADRESSE_SOCIETE=ui->lineEdit_ADRESSE_SOCIETE->text();
    QString EMAIL_F=ui->lineEdit_EMAIL_F->text();

    if (ui->radioButton_TYPE_ACHATF_Machine->isChecked())
    typeachats="machine";

    else if (ui->radioButton_TYPE_ACHATF_Produit->isChecked())
    typeachats="produit";


    int QUANTITE_F=ui->spinBox_QUANTITE_F->text().toInt();
    int PRIX_F=ui->lineEdit_PRIX_F->text().toInt();
    Fournisseurs f( MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, typeachats, QUANTITE_F, PRIX_F);

    bool test=f.ajouter();

    if(test)
  {  ui->tableView->setModel(f.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("Ajout Effectué\n"
                                   "click cancel to exit"), QMessageBox::Cancel);

    }

    else
       {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("Ajout non Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);
    }
}


void MainWindow::on_supprimer_clicked()
{


    QString MATRICULE_F=ui->lineEdit_MATRICULE_F->text();


    bool test=f.supprimer( MATRICULE_F);

    if(test)
  {  ui->tableView->setModel(f.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("Suppression Effectué\n"
                                   "click cancel to exit"), QMessageBox::Cancel);

    }

    else
       {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("Suppression non Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);
    }
}

