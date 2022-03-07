#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cin->setValidator(new QIntValidator(0,9999999,this));
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


void MainWindow::on_modifier_clicked()
{
    QMessageBox msg;

    employe emp;

    emp.setCIN(ui->cin_2->text().toInt());
    emp.setNom(ui->nom_2->text());
    emp.setPrenom(ui->prenom_2->text());
    emp.setAge(ui->age_2->text().toInt());
    emp.setEmail(ui->email_2->text());
    emp.setNum(ui->num_tel_2->text().toInt());
    emp.setPassword(ui->password_2->text());
    emp.setFonction(ui->fonction_2->text());
    emp.setSalaire(ui->salaire_2->text().toInt());

    bool test=emp.modifier(emp.getCIN()) ;

    if(test)
        {         
            QMessageBox::information(nullptr, QObject::tr("success"),
                        QObject::tr("modification avec succès"), QMessageBox::Cancel);
            ui->tab_emp->setModel(emp.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("warning"),
                        QObject::tr("echec de modification"), QMessageBox::Cancel);
            ui->tab_emp->setModel(emp.afficher());
}
