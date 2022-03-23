#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sys/types.h>
#include <QSqlQuery>
#include <QMap>
#include <QSqlRecord>
#include <QComboBox>
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_employe->setModel(emp.afficher());
    ui->email->setPlaceholderText("email");
    ui->password->setPlaceholderText("password");
    ui->recherche_employe->setPlaceholderText("Vous pouvez rechercher par le cin, le nom, le prenom ou la fonction");

    ui->confirm_email->setPlaceholderText("Saisir votre email");
    ui->confirm_email->setFocus();
    ui->old_password->setPlaceholderText("Saisir ancien mot de passe");
    ui->new_password->setPlaceholderText("Saisir nouveau mot de passe");
    ui->new_password_2->setPlaceholderText("Confirmer nouveau mot de passe");

    QSqlQuery query,query2;
    query.prepare("select CIN from Employe");
    query.exec();
    ui->cin_employe_2->addItem("");
    while(query.next())
        ui->cin_employe_2->addItem(query.value(0).toString());

    //recherche avancée
    QStringList CompletionList;
    query2.prepare("select * from Employe");
    query2.exec();
    while(query2.next())
        CompletionList <<query2.value("CIN").toString() <<query2.value("NOM").toString()<<query2.value("AGE").toString()<<query2.value("SALAIRE").toString();
    StringCompleter=new QCompleter(CompletionList, this);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->recherche_employe->setCompleter(StringCompleter);
}
MainWindow::~MainWindow()
{
    delete ui;
}

QString random()
{
    QString a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString r;
    srand(time(NULL));
    for(int i = 0; i < 5; i++) r.push_back(a.at(size_t(rand() % 62)));
    return r;
}

void MainWindow::on_forgot_password_clicked()
{
    QString email=ui->email->text();
    QSqlQuery query;
    QString password=random();
    if (email=="")
        QMessageBox::critical(this,"error","this field can't be empty");
    else if (!emp.chercher_employe(email))
        QMessageBox::critical(this,"error","Email inexistant");
    else
    {
        Smtp *smtp = new Smtp("waterproof.application@gmail.com" , "waterproofwaterproof", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("perspectives.agence@gmail.com",email,"New password",password);
        query.prepare("UPDATE EMPLOYE SET PASSWORD=:password WHERE EMAIL=:EMAIL");
        query.bindValue(":EMAIL",email);
        query.bindValue(":password",password);
        query.exec();
    }
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
            ui->stackedWidget->setCurrentIndex(2);
        else if (fn=="Magasinier")
        {
            ui->stackedWidget->setCurrentIndex(3);
        }
        else if (fn=="Caissier")
        {
            ui->stackedWidget->setCurrentIndex(4);
        }
        else if (fn=="Rh")
            ui->stackedWidget->setCurrentIndex(5);
        //else if (fn=="Comptable")
            //ui->stackedWidget->setCurrentIndex(6);
    }
}

void MainWindow::on_ajouter_employe_clicked()
{
    QMessageBox msgBox;
        bool test=true,x=true,y=true;

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

        if(cin=="" || nom=="" || prenom=="" || email=="" || num_tel=="" || password=="" || ui->fonction_employe->currentIndex()==0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
            test=false;
        }

        else if(cin.length()!=8)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("CIN doit être composé de 8 chiffres!"), QMessageBox::Cancel);
            test=false;
        }

        else if (!(regex.exactMatch(nom)))
        {
                QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le nom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
            test=false;
        }

        else if (!(regex.exactMatch(prenom)))
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le prenom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
            test=false;
        }

        else if(age<=20 || age>=60)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
            test=false;
        }

        else if(!email.contains(QRegExp("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$")))
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Email invalide!"), QMessageBox::Cancel);
            test=false;
        }
        else if (emp.chercher_employe(email))
        {
                    QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Email existe déja!"), QMessageBox::Cancel);
            test=false;
        }

        else if(num_tel.length()!=8)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
            test=false;
        }

        else if (!(regex2.exactMatch(password)) || password.length()<4)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le mot de passe ne doit pas contenir des symboles et au moins 4 caractères"), QMessageBox::Cancel);
            test=false;
        }

        else if(salaire<=0 || salaire>=5000)
        {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
            test=false;
        }

        for (int i=0;i!=8;i++)
        {
            if ((cin[i] >= 'A' && cin[i]<='Z') || (cin[i] >= 'a' && cin[i]<='z'))
            {
                test=false;
                x=false;
            }
            else if ((num_tel[i] >= 'A' && num_tel[i]<='Z') || (num_tel[i] >= 'a' && num_tel[i]<='z'))
            {
               test=false;
               y=false;
            }
        }

        if (!x)
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le CIN doit être composé par des chiffres seulement!"), QMessageBox::Cancel);
        else if (!y)
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le numero de telephone doit être composé par des chiffres seulement!"), QMessageBox::Cancel);


        if (test)
        {
            employe e( cin, nom, prenom, age, email, num_tel, password, fonction, salaire);

            e.ajouter();
            ui->tab_employe->setModel(emp.afficher());
            ui->cin_employe->clear();
            ui->cin_employe_2->clear();
            ui->nom_employe->clear();
            ui->prenom_employe->clear();
            ui->age_employe->clear();
            ui->email_employe->clear();
            ui->num_tel_employe->clear();
            ui->password_employe->clear();
            ui->fonction_employe->setCurrentIndex(0);
            ui->salaire_employe->clear();
            ui->cin_employe->setFocus();

            QSqlQuery query;
            query.prepare("select CIN from Employe");
            query.exec();
            ui->cin_employe_2->addItem("");
            while(query.next())
                ui->cin_employe_2->addItem(query.value(0).toString());
        }
}

void MainWindow::on_supprimer_employe_clicked()
{
    QString cin2 = ui->tab_employe->selectionModel()->currentIndex().data(Qt::DisplayRole).toString();
    emp.supprimer(cin2);
    ui->tab_employe->setModel(emp.afficher());
    ui->cin_employe_2->clear();
    QSqlQuery query;
    query.prepare("select CIN from Employe");
    query.exec();
    ui->cin_employe_2->addItem("");
    while(query.next())
        ui->cin_employe_2->addItem(query.value(0).toString());
}

void MainWindow::on_modifier_employe_clicked()
{
    QMessageBox msg;
    bool test=true,y=true;
    employe emp;

    QRegExp regex("([A-Z][a-z]*)");
    QRegExp regex2("[a-zA-Z0-9]*");

    emp.setCIN(ui->cin_employe_2->currentText());
    emp.setNom(ui->nom_employe_2->text());
    emp.setPrenom(ui->prenom_employe_2->text());
    emp.setAge(ui->age_employe_2->text().toInt());
    emp.setEmail(ui->email_employe_2->text());
    emp.setNum(ui->num_tel_employe_2->text());
    emp.setPassword(ui->password_employe_2->text());
    emp.setFonction(ui->fonction_employe_2->currentText());
    emp.setSalaire(ui->salaire_employe_2->text().toInt());

    if(ui->nom_employe_2->text()=="" || ui->prenom_employe_2->text()=="" || ui->email_employe_2->text()=="" || ui->num_tel_employe_2->text()=="" || ui->password_employe_2->text()=="" || ui->fonction_employe_2->currentIndex()==0 || ui->cin_employe_2->currentIndex()==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Tous les champs doivent être remplis!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->nom_employe_2->text())))
    {
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le nom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex.exactMatch(ui->prenom_employe_2->text())))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le prenom doit être composé par des lettres seulement et commençant par une lettre majuscule"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->age_employe_2->text().toInt()<=20 || ui->age_employe_2->text().toInt()>=60)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Age doit être entre 20 et 60 ans!"), QMessageBox::Cancel);
        test=false;
    }

    else if(!ui->email_employe_2->text().contains(QRegExp("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$")))
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Email invalide!"), QMessageBox::Cancel);
        test=false;
    }
    else if(ui->num_tel_employe_2->text().length()!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le numero de telephone doit être composé de 8 chiffres!"), QMessageBox::Cancel);
        test=false;
    }

    else if (!(regex2.exactMatch(ui->password_employe_2->text())) || ui->password_employe_2->text().length()<4)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"), QObject::tr("Le mot de passe ne doit pas contenir des symboles"), QMessageBox::Cancel);
        test=false;
    }

    else if(ui->salaire_employe_2->text().toInt()<=0 || ui->salaire_employe_2->text().toInt()>=5000)
    {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Salaire doit être positive!"), QMessageBox::Cancel);
        test=false;
    }

    for (int i=0;i!=8;i++)
    {
        if ((ui->num_tel_employe_2->text()[i] >= 'A' && ui->num_tel_employe_2->text()[i]<='Z') || (ui->num_tel_employe_2->text()[i] >= 'a' && ui->num_tel_employe_2->text()[i]<='z'))
        {
           test=false;
           y=false;
        }
    }
    if (!y)
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Le numero de telephone doit être composé par des chiffres seulement!"), QMessageBox::Cancel);

    if (test)
    {
            emp.modifier(emp.getCIN()) ;

            ui->tab_employe->setModel(emp.afficher());
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

void MainWindow::on_tri_emp_activated(int index)
{
    if(index==1)
        ui->tab_employe->setModel(emp.tri_cin_asc());
    else if(index==2)
        ui->tab_employe->setModel(emp.tri_cin_desc());
    else if(index==3)
        ui->tab_employe->setModel(emp.tri_nom_asc());
    else if(index==4)
        ui->tab_employe->setModel(emp.tri_nom_desc());
    else if(index==5)
        ui->tab_employe->setModel(emp.tri_age_asc());
    else if(index==6)
        ui->tab_employe->setModel(emp.tri_age_desc());
    else if(index==7)
        ui->tab_employe->setModel(emp.tri_salaire_asc());
    else if(index==8)
        ui->tab_employe->setModel(emp.tri_salaire_desc());
}

void MainWindow::on_recherche_employe_textChanged(const QString &arg1)
{
    ui->tab_employe->setModel(emp.recherche_avancee_employe(arg1));
}

void MainWindow::on_cin_employe_2_activated(const QString &arg1)
{
       QSqlQuery query;
       query.prepare("Select * from EMPLOYE where CIN=:CIN" );
       query.bindValue(":CIN",arg1);
       query.exec();
       query.next();

        ui->nom_employe_2->setText(query.value(1).toString());
        ui->prenom_employe_2->setText(query.value(2).toString());
        ui->age_employe_2->setText(query.value(3).toString());
        ui->email_employe_2->setText(query.value(4).toString());
        ui->num_tel_employe_2->setText(query.value(5).toString());
        ui->password_employe_2->setText(query.value(6).toString());
        ui->fonction_employe_2->setCurrentIndex(0);
        ui->salaire_employe_2->setText(query.value(8).toString());
}

void MainWindow::on_confirm_password_clicked()
{
    QString email=ui->confirm_email->text();
    QString old=ui->old_password->text();
    QString new_pass=ui->new_password->text();
    QString new_pass2=ui->new_password_2->text();
    QSqlQuery query,query2;

    if(emp.chercher_employe(email))
    {
        if (new_pass==old || old==new_pass2)
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("nouveau mot de passe doit etre different"), QMessageBox::Cancel);
        else if ((new_pass==new_pass2))
        {
            query.prepare("UPDATE EMPLOYE SET PASSWORD=:password2 where EMAIL=:EMAIL AND PASSWORD=:PASSWORD" );
            query.bindValue(":EMAIL",email);
            query.bindValue(":PASSWORD",old);
            query.bindValue(":password2",new_pass);
            bool test=query.exec();
            if (test)
            {
                QMessageBox::information(nullptr, QObject::tr("success"),QObject::tr("nouveau mot de passe effectué"), QMessageBox::Cancel);
                ui->stackedWidget->setCurrentIndex(1);
            }
            else QMessageBox::critical(nullptr,"error","wronginfo");
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("new passwords don't match"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Echec"),QObject::tr("Email inexistant"), QMessageBox::Cancel);

}

void MainWindow::on_change_password_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_annuler_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
