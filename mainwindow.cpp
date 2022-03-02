#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_emp->setModel(emp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int age=ui->age->text().toInt();
    QString email=ui->email->text();
    int num_tel=ui->num_tel->text().toInt();
    QString password=ui->password->text();
    QString fonction=ui->fonction->text();
    int salaire=ui->salaire->text().toInt();

    employe e( cin, nom, prenom, age, email, num_tel, password, fonction, salaire);

    bool test=e.ajouter();
    //QMessageBox msgBox;
    if(test)
  {
    //msgBox.setText("ajout avec succée");
    ui->tab_emp->setModel(emp.afficher());
    ui->cin->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->age->clear();
    ui->email->clear();
    ui->num_tel->clear();
    ui->password->clear();
    ui->fonction->clear();
    ui->salaire->clear();
    // Put the focus back into the input box so they can type again:
   ui->cin->setFocus();
    }

    /*else
        msgbox.setText("Echec d'ajout");
    msgbox.exec();*/
}



void MainWindow::on_supprimer_clicked()
{
    int cin2=ui->cin2->text().toInt();


        bool test=emp.supprimer(cin2);
        QMessageBox msgBox;
        if(test)
      {
        msgBox.setText("supprimer avec succée");
        ui->tab_emp->setModel(emp.afficher());
        ui->cin2->clear();

        // Put the focus back into the input box so they can type again:
       ui->cin2->setFocus();
        }

        else
            msgBox.setText("Echec de suppression");
        msgBox.exec();
}
