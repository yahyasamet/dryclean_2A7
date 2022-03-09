#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QRegExp>
#include <QLineEdit>

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
    QMessageBox msgBox;

    bool test=true;

    QString cin=ui->cin->text();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int age=ui->age->text().toInt();
    QString email=ui->email->text();
    QString num_tel=ui->num_tel->text();
    QString password=ui->password->text();
    QString fonction=ui->fonction->text();
    int salaire=ui->salaire->text().toInt();
    QRegExp regex("([A-Z][a-z]*)");
    QRegExp regex2("[a-zA-Z0-9]*");
    QRegExp regex3("a-z");
    QString email_ending=email.right(9);
    QString email_start=email.left(email.length()-9);
    employe emp;

    if(cin=="" || nom=="" || prenom=="" || email=="" || num_tel=="" || password=="" || fonction=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
        test=false;
    }

    else if(age<=20 || age>=60)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
        test=false;
    }

    else if(salaire<=0 || salaire>=5000)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
        test=false;
    }

    else if(cin.length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("CIN doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }
    else if(num_tel.length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(nom)))
    {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le nom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(prenom)))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le prenom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(fonction)))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("La fonction des employés doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex2.exactMatch(password)))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le mot de passe ne doit pas contenir des symboles"), QMessageBox::Cancel);
        test=false;
    }

    else if(!email.contains("@") || !email.contains("."))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Email invalide!"), QMessageBox::Cancel);
        test=false;
    }

    for (int i=0;i!=8;i++)
    {
        if ((cin[i] >= 'A' && cin[i]<='Z') || (cin[i] >= 'a' && cin[i]<='z'))
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                QObject::tr("Le CIN doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
            test=false;
        }
        else if ((num_tel[i] >= 'A' && num_tel[i]<='Z') || (num_tel[i] >= 'a' && num_tel[i]<='z'))
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                QObject::tr("Le numero de telephone doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
           test=false;
        }
    }

    if (test)
    {
        employe e( cin, nom, prenom, age, email, num_tel, password, fonction, salaire);

        e.ajouter();
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
        ui->cin->setFocus();
    }
}

void MainWindow::on_supprimer_clicked()
{
    employe emp;
    QString cin2=ui->cin2->text();

        bool test=emp.supprimer(cin2);
        QMessageBox msgBox;
        if(test)
      {
            msgBox.setText("supprimé avec succée");
            ui->tab_emp->setModel(emp.afficher());
            ui->cin2->clear();
            ui->cin2->setFocus();
        }
        else
            msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
    QMessageBox msg;
    bool test=true;
    bool x=true;
    bool y=true;
    employe emp;

    QRegExp regex("([A-Z][a-z]*)");
    QRegExp regex2("[a-zA-Z0-9]*");

    emp.setCIN(ui->cin_2->text());
    emp.setNom(ui->nom_2->text());
    emp.setPrenom(ui->prenom_2->text());
    emp.setAge(ui->age_2->text().toInt());
    emp.setEmail(ui->email_2->text());
    emp.setNum(ui->num_tel_2->text());
    emp.setPassword(ui->password_2->text());
    emp.setFonction(ui->fonction_2->text());
    emp.setSalaire(ui->salaire_2->text().toInt());

    if(ui->cin_2->text()=="" || ui->nom_2->text()=="" || ui->prenom_2->text()=="" || ui->email_2->text()=="" || ui->num_tel_2->text()=="" || ui->password_2->text()=="" || ui->fonction_2->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->age_2->text().toInt()<=20 || ui->age_2->text().toInt()>=60)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->salaire_2->text().toInt()<=0 || ui->salaire_2->text().toInt()>=5000)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->cin_2->text().length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("CIN doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }
    else if(ui->num_tel_2->text().length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->nom_2->text())))
    {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le nom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->prenom_2->text())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le prenom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->fonction_2->text())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("La fonction des employés doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex2.exactMatch(ui->password_2->text())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le mot de passe ne doit pas contenir des symboles"), QMessageBox::Cancel);
        test=false;
    }

    else if(!ui->email_2->text().contains("@") || !ui->email_2->text().contains("."))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Email invalide!"), QMessageBox::Cancel);
        test=false;
    }

    for (int i=0;i!=8;i++)
    {
        if ((ui->cin_2->text()[i] >= 'A' && ui->cin_2->text()[i]<='Z') || (ui->cin_2->text()[i] >= 'a' && ui->cin_2->text()[i]<='z'))
        {
            //QMessageBox::critical(nullptr, QObject::tr("Echec"),
                //QObject::tr("Le CIN doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
            test=false;
            x=false;
        }
        else if ((ui->num_tel_2->text()[i] >= 'A' && ui->num_tel_2->text()[i]<='Z') || (ui->num_tel_2->text()[i] >= 'a' && ui->num_tel_2->text()[i]<='z'))
        {
            //QMessageBox::critical(nullptr, QObject::tr("Echec"),
                //QObject::tr("Le numero de telephone doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
           test=false;
           y=false;
        }
    }
    if (!x)
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
            QObject::tr("Le CIN doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
    else if (!y)
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
            QObject::tr("Le numero de telephone doit être composé par des chiffres seulement!"), QMessageBox::Cancel);

    if (test)
    {
        emp.modifier(emp.getCIN()) ;

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
        ui->cin->setFocus();
    }
}
