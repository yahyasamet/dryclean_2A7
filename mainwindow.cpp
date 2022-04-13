#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QUrl>
#include<QDate>
#include"widget.h"
#include"historique.h"
#include <QTimer>
#include <QDesktopServices>
#include <QMovie>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableView->setModel(E.afficher_equipements());
    ui->radioButton->setChecked("");
    QSqlQuery qry,qry2,qry1;
           qry.prepare("select cin from employe");
           qry.exec();
           qry2.prepare("select REFERENCE_EQUIPEMENT from equipements");
           qry2.exec();
           ui->combo_cin_2->addItem("");
           while(qry.next()){
           ui->combo_cin->addItem(qry.value(0).toString());
           ui->combo_cin_2->addItem(qry.value(0).toString());
           }
           ui->combo_ref->addItem("");
           while(qry2.next()){
           ui->combo_ref->addItem(qry2.value(0).toString());
           ui->combo_ref_2->addItem(qry2.value(0).toString());
            }
           qry1.prepare("select * from equipements");
           qry1.exec();
           QStringList completionlist;
           while(qry1.next()){
               completionlist <<qry1.value("MARQUE_EQUIPEMENT").toString()<<qry1.value("REFERENCE_EQUIPEMENT").toString() <<qry1.value("NOM_EQUIPEMENT").toString();
           }
           stringcompleter=new QCompleter(completionlist,this);
           stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
           ui->Rechercher_equipement->setCompleter(stringcompleter);
           Historique h;
           ui->historique->setText(h.load());
           son=new QSound(":/son/son_QT/Simple_Beep2.wav");
           error=new QSound(":/son/son_QT/Error.wav");
           success=new QSound(":/son/son_QT/success.wav");
           monTimer=new QTimer();
           monTimer2=new QTimer();

                QObject::connect(monTimer, SIGNAL(timeout()), this,SLOT(finTempo()));
                QObject::connect(monTimer2, SIGNAL(timeout()), this,SLOT(finTempo2()));
                int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }
                 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
                 //le slot update_label suite à la reception du signal readyRead (reception des données).
                 QMovie *movie = new QMovie(":/images/images/giphy.gif");
                 ui->bubbles->setMovie(movie);
                 movie->start();
                 QMovie *movie2= new QMovie(":/images/images/machinef.gif");
                 monTimer2->setSingleShot(true); //active le mode singleShot
                 monTimer2->start(3000); //démarre une tempo de 3 secondes
                 ui->label_28->setMovie(movie2);
                 movie2->start();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->Demarrer_arduino->setText("Démarrer"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->Eteindre_arduino->setText("Eteindre");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}
void MainWindow::on_Ajouter_equipement_clicked()
{
    son->play();
    int ref=ui->lineEdit_8->text().toInt();
    QString refs=ui->lineEdit_8->text();
    QString marque_EQUIPEMENT=ui->lineEdit_9->text();
    QString nom_EQUIPEMENT=ui->lineEdit_10->text();
    int annee_EQUIPEMENT=ui->lineEdit_11->text().toInt();
    //QString nom_produit=ui->lineEdit_12->text();
    QString etat1=ui->radioButton->text();
    QString etat2=ui->radioButton_2->text();//Jointure statique
    if(ui->radioButton->isChecked() && ui->radioButton_2->isEnabled())
        etat1="En marche";
    else if(ui->radioButton_2->isChecked() && ui->radioButton->isEnabled())
        etat1="En panne";
    QString cin=ui->combo_cin->currentText();
    equipements E(ref,marque_EQUIPEMENT,nom_EQUIPEMENT,annee_EQUIPEMENT,etat1,cin);
    QMessageBox msgbox;

int erreur=0;
    if(!E.Chaine_Valid(nom_EQUIPEMENT))
    erreur=1;
    if(!E.Chaine_Valid(marque_EQUIPEMENT))
    erreur=2;
    if((E.Longueur_entier(annee_EQUIPEMENT))!=4)
    erreur=3;
    if( ref==0 ||marque_EQUIPEMENT=="" || nom_EQUIPEMENT=="" || cin=="")
    {
        erreur=4;
    }
    if(annee_EQUIPEMENT<2000)
        erreur=5;
    if(annee_EQUIPEMENT>QDate::currentDate().year())
        erreur=6;
    switch(erreur)
    {
    case 1:
    error->play();
    msgbox.setText("Le nom doit être composé seulement par des lettres !");
    ui->cs3->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;

    case 2:
    error->play();
    msgbox.setText("La marque doit être composée seulement par des lettres !");
    ui->cs2->setStyleSheet("border-image: url(:/images/images/remove.png);");

    break;

    case 3:
    error->play();
    msgbox.setText("L'année doit être composé par 4 chiffres !");
    ui->cs4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;

    case 4:
    error->play();
    msgbox.setText("Vérifier les champs vides !");
    break;
    case 5:
    error->play();
    msgbox.setText("L'année doit être supérieure à 2000 !");
     ui->cs4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;
    case 6:
    error->play();
    msgbox.setText("L'année doit être inférieure ou égale à la date actuelle !");
     ui->cs4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;
    }
if(erreur==0)
{

    bool test=E.ajouter_equipement();
    if(test)
    {
        QSqlQuery qry1;
        qry1.prepare("select * from equipements");
        qry1.exec();
        QStringList completionlist;
        while(qry1.next()){
            completionlist <<qry1.value("MARQUE_EQUIPEMENT").toString() <<qry1.value("NOM_EQUIPEMENT").toString();
        }
        stringcompleter=new QCompleter(completionlist,this);
        stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->Rechercher_equipement->setCompleter(stringcompleter);
        ui->combo_ref->addItem(refs);
        ui->combo_ref_2->addItem(refs);
        monTimer->setSingleShot(true); //active le mode singleShot

        monTimer->start(2000); //démarre une tempo de 15 secondes
     ui->cs1->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs2->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs3->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs4->setStyleSheet("border-image: url(:/images/images/correct.png);");
        success->play();
        msgbox.setText("Ajout avec succes.");
        Historique h;
        h.save(cin,refs,"Ajout");
        ui->historique->setText(h.load());
        ui->tableView->setModel(E.afficher_equipements());
          ui->lineEdit_8->clear();
          ui->lineEdit_9->clear();
          ui->lineEdit_10->clear();
          ui->lineEdit_11->clear();

    }
    else
    {
        error->play();
        msgbox.setText("Echec d'ajout");
    }

}


    //}



    msgbox.exec();
}
void MainWindow::on_Supprimer_equipement_clicked()
{
    son->play();
    equipements E1;
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        int reference_equipement = index.data(Qt::DisplayRole).toInt();
        QString refs=index.data(Qt::DisplayRole).toString();
        int cas;
        if(E.recherche_ref(refs))
            cas=1;
        else
            cas=-1;
        QSqlQuery query;

           query.prepare("Select * from equipements where reference_equipement=:reference_equipement" );
                   query.bindValue(":reference_equipement",reference_equipement) ;
                   query.exec();
            query.next() ;
            QString cin=query.value("CIN_EMP").toString();

      QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Supprimer", "Êtes-vous sûr de supprimer",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            bool test=E.supprimer_equipement(reference_equipement);
            if(test)
            {
                QSqlQuery qry1;
                qry1.prepare("select * from equipements");
                qry1.exec();
                QStringList completionlist;
                while(qry1.next())
                {
                completionlist <<qry1.value("MARQUE_EQUIPEMENT").toString()<<qry1.value("REFERENCE_EQUIPEMENT").toString() <<qry1.value("NOM_EQUIPEMENT").toString();
                }
                stringcompleter=new QCompleter(completionlist,this);
                stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                ui->Rechercher_equipement->setCompleter(stringcompleter);
                Historique h;
                h.save(cin,refs,"Supprimer");
                ui->historique->setText(h.load());
      ui->tableView->setModel(E.afficher_equipements());
      ui->combo_ref->clear();
      ui->combo_ref->addItem("");

      QSqlQuery qry;
               qry.prepare("select reference_equipement from equipements");
                   qry.exec();
                   while(qry.next()){
                    ui->combo_ref->addItem(qry.value(0).toString());
                   }
      if(cas==1)
      QMessageBox::information(nullptr,"Suppression","Equipement supprimé");
      else if(cas==-1)
      QMessageBox::information(nullptr,"Suppression","Equipement n'est pas supprimé");
            }
        }
}

void MainWindow::on_Modifier_equipement_clicked()
{
    son->play();
    int REFERENCE_EQUIPEMENT=ui->combo_ref->currentText().toInt() ;
    QString refs=ui->combo_ref->currentText();
    QString marque_EQUIPEMENT=ui->lineEdit_14->text();
    QString nom_EQUIPEMENT=ui->lineEdit_15->text();
    int annee_EQUIPEMENT=ui->lineEdit_16->text().toInt();
    //QString nom_produit=ui->lineEdit_12->text();
    QString etat1=ui->radioButton_3->text();
    QString etat2=ui->radioButton_4->text();//Jointure statique
    if(ui->radioButton_3->isChecked())
        etat1="En marche";
    else if(ui->radioButton_3->isEnabled())
        etat1="En panne";
    QString cin=ui->combo_cin_2->currentText();
    equipements E(REFERENCE_EQUIPEMENT,marque_EQUIPEMENT,nom_EQUIPEMENT,annee_EQUIPEMENT,etat1,cin);
        QMessageBox msgbox;
            int erreur=0;
            int year = QDate::currentDate().year();
                if(!E.Chaine_Valid(nom_EQUIPEMENT))
                erreur=1;
                if(!E.Chaine_Valid(marque_EQUIPEMENT))
                erreur=2;
                if((E.Longueur_entier(annee_EQUIPEMENT))!=4)
                erreur=3;
                if( REFERENCE_EQUIPEMENT==0 ||marque_EQUIPEMENT=="" || nom_EQUIPEMENT=="" || cin=="")
                {
                    erreur=4;
                }
                if(annee_EQUIPEMENT<2000)
                    erreur=5;
                if(annee_EQUIPEMENT>year)
                    erreur=6;
                switch(erreur)
                {
                case 1:
                error->play();
                msgbox.setText("Le nom doit être composé seulement par des lettres !");
                ui->cs6->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;

                case 2:
                error->play();
                msgbox.setText("La marque doit être composée seulement par des lettres !");
                ui->cs5->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;

                case 3:
                error->play();
                msgbox.setText("L'année doit être supérieure à 2000 !");
                ui->cs7->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                case 4:
                error->play();
                msgbox.setText("Vérifier les champs vides !");
                break;
                case 5:
                error->play();
                msgbox.setText("L'année doit être supérieure à 2000 !");
                ui->cs7->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                case 6:
                error->play();
                msgbox.setText("L'année doit être inférieure ou égale à la date actuelle !");
                ui->cs7->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                }

            if(erreur==0)
            {

                    E.set_ref_equipement(ui->combo_ref->currentText().toInt());
                bool test=E.modifier_equipement(E.get_refEQUIPEMENT()) ;
                if(test)
                {
                    QSqlQuery qry1;
                    qry1.prepare("select * from equipements");
                    qry1.exec();
                    QStringList completionlist;
                    while(qry1.next()){
                        completionlist <<qry1.value("MARQUE_EQUIPEMENT").toString()<<qry1.value("REFERENCE_EQUIPEMENT").toString() <<qry1.value("NOM_EQUIPEMENT").toString();
                    }
                    stringcompleter=new QCompleter(completionlist,this);
                    stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                    ui->Rechercher_equipement->setCompleter(stringcompleter);
                    monTimer->setSingleShot(true); //active le mode singleShot

                    monTimer->start(2000); //démarre une tempo de 15 secondes
                 ui->cs5->setStyleSheet("border-image: url(:/images/images/correct.png);");
                 ui->cs6->setStyleSheet("border-image: url(:/images/images/correct.png);");
                 ui->cs7->setStyleSheet("border-image: url(:/images/images/correct.png);");
                    success->play();
                    msgbox.setText("modification avec succés.");
                    Historique h;
                    h.save(cin,refs,"Modification");
                    ui->historique->setText(h.load());
                    ui->tableView->setModel(E.afficher_equipements());
                    ui->lineEdit_14->clear();
                    ui->lineEdit_15->clear();
                    ui->lineEdit_16->clear();
                }
                else{
                    error->play();
                    msgbox.setText("Échec de modification");
                    }


            }
            msgbox.exec();
}

void MainWindow::on_Trier_equipement_activated(const QString &arg1)
{
    if(arg1=="Année")
    ui->tableView->setModel(E.Trie_Annee());
    else if(arg1=="Etat")
    ui->tableView->setModel(E.Trie_Etat());
    else if(arg1=="Référence croissante")
    ui->tableView->setModel(E.Trie_RefASC());
    else if(arg1=="Référence décroissante")
    ui->tableView->setModel(E.Trie_RefDESC());
}

void MainWindow::on_Rechercher_equipement_textChanged(const QString &arg1)
{
    ui->tableView->setModel(E.Recherche_Avancee(arg1));
}

void MainWindow::on_chatbox_clicked()
{
son->play();
widget w;
w.setModal(true);
w.exec();
}

void MainWindow::on_combo_ref_activated(const QString &)
{
    QSqlQuery query;
    QString REFERENCE_EQUIPEMENT=ui->combo_ref->currentText() ;
   query.prepare("Select * from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT" );
           query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT) ;
           query.exec();
    query.next() ;
    ui->lineEdit_14->setText(query.value(1).toString());
    ui->lineEdit_15->setText(query.value(2).toString());
    ui->lineEdit_16->setText(query.value(3).toString());
    QString etat=query.value(4).toString();
    if(etat=="En panne")
    ui->radioButton_4->setChecked("");
    else
    ui->radioButton_3->setChecked("");
    ui->combo_cin_2->setCurrentText(query.value(5).toString());
}
//mon code après la temporisation
void MainWindow::finTempo()

{
         ui->cs1->setStyleSheet("");
         ui->cs2->setStyleSheet("");
         ui->cs3->setStyleSheet("");
         ui->cs4->setStyleSheet("");
         ui->cs5->setStyleSheet("");
         ui->cs6->setStyleSheet("");
         ui->cs7->setStyleSheet("");
}

void MainWindow::on_facebook_clicked()
{
    QString link = "https://www.facebook.com/MORYS-Fashion-107812848401567";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_instagram_clicked()
{
    QString link = "https://www.instagram.com/drycleaningband/";
    QDesktopServices::openUrl(QUrl(link));
}
QString MainWindow::on_combo_ref_2_activated(const QString &arg1)
{
    QSqlQuery query;
    QString REFERENCE_EQUIPEMENT=ui->combo_ref_2->currentText() ;
   query.prepare("Select etat_equipement from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT" );
           query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT) ;
           query.exec();
    query.next() ;
    return query.value("etat_equipement").toString();

}

void MainWindow::on_Demarrer_arduino_clicked()
{
    QString etat=on_combo_ref_2_activated("");
    if(etat=="En panne")
    {

        A.write_to_arduino("0"); //envoyer 0 à arduino
        QMessageBox::critical(nullptr, QObject::tr("Machine en panne"),
                    QObject::tr("demarrage echouee.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        // ecrire en panne sur l'afficheur et la machine ne demarre pas
    }
    else
    {

        A.write_to_arduino("1"); //envoyer 1 à arduino
        QMessageBox::information(nullptr, QObject::tr("Machine en marche"),
                    QObject::tr("demarrage avec succee.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        // ecrire en marche sur l'afficheur et la machine demarre correctement
    }

}

void MainWindow::on_Eteindre_arduino_clicked()
{
    A.write_to_arduino("2"); //envoyer 0 à arduino
}
void MainWindow::finTempo2()
{
    delete ui->label_28;
}
