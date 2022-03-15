#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smtp.h"
#include <QMessageBox>
#include <sys/types.h>
#include <QSqlQuery>
#include <QMap>
#include <QSqlRecord>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_employe->setModel(emp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString random(int len)
{
    QString a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString r;
    srand(time(NULL));
    for(int i = 0; i < len; i++) r.push_back(a.at(size_t(rand() % 62)));
    return r;
}

void MainWindow::on_forgot_password_clicked()
{
    /*MailMessage msg;
    msg.addRecipient (MailRecipient (MailRecipient::PRIMARY_RECIPIENT,
                                           "bob@example.com", "Bob"));
    msg.setSender ("Me <me@example.com>");
    msg.setSubject ("Subject");
    msg.setContent ("Content");

    SMTPClientSession smtp ("mail.example.com");
    smtp.login ();
    smtp.sendMessage (msg);
    smtp.close ();*/
    QString pass=random(5);
    QMessageBox::information(nullptr, QObject::tr("Your new password is :"), pass, QMessageBox::Cancel);

    //smtp *newMail  = new smtp("mirabm48@gmail.com","amira.benmbarek@esprit.tn","mot de passe oublié",pass);
    //delete newMail;
}

QMap<QString,QString> check_login(QString email,QString password)
{
    QSqlQuery query;
    query.prepare("select NOM, PRENOM, FONCTION from employe where email=:email and password=:password");
    query.bindValue(":email",email);
    query.bindValue(":password",password);
    QMap<QString,QString> map;

    if (!query.exec()) {
        qDebug() << "Query failed!";
    } else {
        if (query.first()) { // get the first record in the result
            //QSqlRecord rec = query.record();
            //int nameCol = rec.indexOf("NOM"); // index of the field "name"
            //query.next();
            QString ch= query.value("NOM").toString();
            QString ch2= query.value("PRENOM").toString();
            QString ch3= query.value("FONCTION").toString();
            map.insert("nom",ch);
            map.insert("prenom",ch2);
            map.insert("fonction",ch3);
        } else {
            qDebug () << "Data not found";
        }
    }

    return map;
}
void MainWindow::on_login_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();
    QMap<QString,QString> map;
    map=check_login(email,password);
    QString fn=map["fonction"];
    if (map.empty())
        QMessageBox::critical(nullptr, QObject::tr("sorry"),QObject::tr("wrong login info\n"),QMessageBox::Cancel);
    else
    {
        QString msg="Bienvenue "+map["nom"]+" "+map["prenom"];
        QMessageBox::information(nullptr, QObject::tr("success"),msg,QMessageBox::Cancel);
        if (fn=="Gerant")
            ui->stackedWidget->setCurrentIndex(1);
        else if (fn=="Magasinier")
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
        else if (fn=="Caissier")
        {
            ui->stackedWidget->setCurrentIndex(3);
        }
        else if (fn=="Rh")
            ui->stackedWidget->setCurrentIndex(4);
        else if (fn=="Comptable")
            ui->stackedWidget->setCurrentIndex(5);
    }
}

void MainWindow::on_ajouter_employe_clicked()
{
    QMessageBox msgBox;

        bool test=true;

        QString cin=ui->cin_employe->text();
        QString nom=ui->nom_employe->text();
        QString prenom=ui->prenom_employe->text();
        int age=ui->age_employe->text().toInt();
        QString email=ui->email_employe->text();
        QString num_tel=ui->num_tel_employe->text();
        QString password=ui->password_employe->text();
        QString fonction=ui->fonction_employe->currentText();
        int salaire=ui->salaire_employe->text().toInt();
        QRegExp regex("([A-Z][a-z]*)");
        QRegExp regex2("[a-zA-Z0-9]*");
        QRegExp regex3("a-z");
        QString email_ending=email.right(9);
        QString email_start=email.left(email.length()-9);
        employe emp;

        if(cin=="" || nom=="" || prenom=="" || email=="" || num_tel=="" || password=="" || ui->fonction_employe->currentIndex()==0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
            test=false;
        }

        else if(cin.length()!=8)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("CIN doit être composé de 8 chiffres!"), QMessageBox::Cancel);
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

        else if(age<=20 || age>=60)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
            test=false;
        }

        else if(!email.contains("@") || !email.contains("."))
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Email invalide!"), QMessageBox::Cancel);
            test=false;
        }

        else if(num_tel.length()!=8)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
            test=false;
        }

        else if (!(regex2.exactMatch(password)) || password.length()<=4)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Le mot de passe ne doit pas contenir des symboles et au moins 4 caractères"), QMessageBox::Cancel);
            test=false;
        }

        else if(salaire<=0 || salaire>=5000)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
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
            ui->tab_employe->setModel(emp.afficher());
            ui->cin_employe->clear();
            ui->nom_employe->clear();
            ui->prenom_employe->clear();
            ui->age_employe->clear();
            ui->email_employe->clear();
            ui->num_tel_employe->clear();
            ui->password_employe->clear();
            ui->fonction_employe->setCurrentIndex(0);
            ui->salaire_employe->clear();
            ui->cin_employe->setFocus();
        }
}

void MainWindow::on_supprimer_employe_clicked()
{
    employe emp;
    QString cin2=ui->cin_employe_3->text();

        bool test=emp.supprimer(cin2);
        QMessageBox msgBox;
        if(test)
      {
            msgBox.setText("supprimé avec succée");
            ui->tab_employe->setModel(emp.afficher());
            ui->cin_employe_3->clear();
            ui->cin_employe_3->setFocus();
        }
        else
            msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_modifier_employe_clicked()
{
    QMessageBox msg;
    bool test=true;
    bool x=true;
    bool y=true;
    employe emp;

    QRegExp regex("([A-Z][a-z]*)");
    QRegExp regex2("[a-zA-Z0-9]*");

    emp.setCIN(ui->cin_employe_2->text());
    emp.setNom(ui->nom_employe_2->text());
    emp.setPrenom(ui->prenom_employe_2->text());
    emp.setAge(ui->age_employe_2->text().toInt());
    emp.setEmail(ui->email_employe_2->text());
    emp.setNum(ui->num_tel_employe_2->text());
    emp.setPassword(ui->password_employe_2->text());
    emp.setFonction(ui->fonction_employe_2->currentText());
    emp.setSalaire(ui->salaire_employe_2->text().toInt());

    if(ui->cin_employe_2->text()=="" || ui->nom_employe_2->text()=="" || ui->prenom_employe_2->text()=="" || ui->email_employe_2->text()=="" || ui->num_tel_employe_2->text()=="" || ui->password_employe_2->text()=="" || ui->fonction_employe_2->currentIndex()==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->cin_employe_2->text().length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("CIN doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->nom_employe_2->text())))
    {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le nom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->prenom_employe_2->text())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le prenom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->age_employe_2->text().toInt()<=20 || ui->age_employe_2->text().toInt()>=60)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
        test=false;
    }

    else if(!ui->email_employe_2->text().contains("@") || !ui->email_employe_2->text().contains("."))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Email invalide!"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->num_tel_employe_2->text().length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex2.exactMatch(ui->password_employe_2->text())) || ui->password_employe_2->text().length()<=4)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Le mot de passe ne doit pas contenir des symboles"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->fonction_employe_2->currentText())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("La fonction des employés doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->salaire_employe_2->text().toInt()<=0 || ui->salaire_employe_2->text().toInt()>=5000)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
        test=false;
    }

    for (int i=0;i!=8;i++)
    {
        if ((ui->cin_employe_2->text()[i] >= 'A' && ui->cin_employe_2->text()[i]<='Z') || (ui->cin_employe_2->text()[i] >= 'a' && ui->cin_employe_2->text()[i]<='z'))
        {
            //QMessageBox::critical(nullptr, QObject::tr("Echec"),
                //QObject::tr("Le CIN doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
            test=false;
            x=false;
        }
        else if ((ui->num_tel_employe_2->text()[i] >= 'A' && ui->num_tel_employe_2->text()[i]<='Z') || (ui->num_tel_employe_2->text()[i] >= 'a' && ui->num_tel_employe_2->text()[i]<='z'))
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

        ui->tab_employe->setModel(emp.afficher());
        ui->cin_employe_2->clear();
        ui->nom_employe_2->clear();
        ui->prenom_employe_2->clear();
        ui->age_employe_2->clear();
        ui->email_employe_2->clear();
        ui->num_tel_employe_2->clear();
        ui->password_employe_2->clear();
        ui->fonction_employe_2->setCurrentIndex(0);
        ui->salaire_employe_2->clear();
        ui->cin_employe_2->setFocus();
    }
}

void MainWindow::on_gestion_employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
