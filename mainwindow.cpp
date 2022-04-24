#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sys/types.h>
#include <QSqlQuery>
#include <QMap>
#include <QSqlRecord>
#include <QComboBox>
#include "smtp.h"
#include <QPixmap>
#include <QDebug>
#include <QCryptographicHash>
#include <QMovie>

#include "QWidget"
#include <QIntValidator>
#include <QRegExpValidator>
#include <QUrl>

#include "QWidget"
#include <QTextEdit>
#include <QtSql>
#include <QTabWidget>
#include<QFileDialog>
#include<QFile>
#include<QStringList>
#include <iostream>
#include<QTextDocument>
#include <QRect>
#include <QPdfWriter>
#include <QValidator>
#include <QSqlRelationalDelegate>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <iostream>
#include <QDir>
#include <regex>
#include <string>
#include <QRegularExpression>
#include <QBoxLayout>

#include <QList>
#include<QTextDocument>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

#include"widget.h"
#include <QTimer>
#include <QDesktopServices>
#include<QDate>

#include <QAbstractEventDispatcher>
#include <QtQml>
#include <QQuickView>
#include "qtquickcontrolsapplication.h"
#include "sqleventmodel.h"
#include <QSurfaceFormat>

#include <QPicture>
#include <QtGui>
#include <QtOpenGL>
#include <QPointF>
#include <QLibrary>
#include "qrcode.h"
const QString RESULTS_PATH = "C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Qrcode/";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->tab_employe->setModel(emp.afficher());
    ui->email->setPlaceholderText("email");
    ui->password->setPlaceholderText("password");
    ui->recherche_employe->setPlaceholderText("Vous pouvez rechercher par le cin, le nom, le prenom ou la fonction");

    ui->confirm_email->setPlaceholderText("Saisir votre email");
    ui->confirm_email->setFocus();
    ui->old_password->setPlaceholderText("Saisir ancien mot de passe");
    ui->new_password->setPlaceholderText("Saisir nouveau mot de passe");
    ui->new_password_2->setPlaceholderText("Confirmer nouveau mot de passe");

    int ret = ard.connect_arduino();
            switch (ret)
            {
                case(0): qDebug()<<"arduino is avaible and connected to: "<<ard.getarduino_port_name();
                break;

                case(1): qDebug()<<"arduino is avaible but not connected to: "<<ard.getarduino_port_name();
                break;

                case(-1): qDebug()<<"arduino is not avaible";
                break;
            }
        QObject::connect(ard.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));

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

    //integration zeineb//////////////////////////////////////////////////////////
    ui->tableView_f->setModel(f.afficher());
        connect(ui->sendBtn_f, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn_f, SIGNAL(clicked()),this, SLOT(close()));


        QSqlQuery qry,qry1,qry_mail;
                qry.prepare("select MATRICULE_F from fournisseur");
                qry.exec();
               ui->combo_box_modifier_f->addItem("");

                while(qry.next()){
                 ui->combo_box_modifier_f->addItem(qry.value(0).toString());
               }
                qry1.prepare("select * from fournisseur");
                qry1.exec();
                QStringList completionlist;
                while(qry1.next()){
                    completionlist <<qry1.value("MATRICULE_F").toString() <<qry1.value("NOMSOCIETE").toString() <<qry1.value("ADRESSE_SOCIETE").toString() <<qry1.value("EMAIL_F").toString();
                }
                stringcompleter=new QCompleter(completionlist,this);
                stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                ui->rechercheA_f->setCompleter(stringcompleter);
                qry_mail.prepare("select NOMSOCIETE from fournisseur");
                qry_mail.exec();
                ui->recipient_combo_f->addItem("");
                while(qry_mail.next()){
                 ui->recipient_combo_f->addItem(qry_mail.value(0).toString());
                }

    //integration ines//////////////////////////////////////////////////////////
                QPixmap pix("C:/Users/MSI/Desktop/untitled_cb/logo_c++_1.png");
                QPixmap pix1("C:/Users/MSI/Desktop/untitled_cb/search.png");
                ui->label_36->setPixmap(pix);
                ui->label_14->setPixmap(pix1);
                ui->modifier_cin_emp_cmb_2->addItem("");
                ui->modifier_combo_2->addItem("");
               // ui->modifier_etat->addItem("");
               // ui->modifier_livraison->addItem("");
                //ui->modifier_type->addItem("");


                label = new QLabel("Code：",this);

                 // cin= new QComboBox(this);
                  produceCode128Button = new QPushButton("code128",this);
                    //produceEAN13Button = new QPushButton("EAN13",this);
                    savePictureButton = new QPushButton("save",this);
                    barCodeBox = new BarCodeBox("Code",this);

                   // QHBoxLayout *hBoxLayout = new QHBoxLayout();
                    ui->hBoxLayout_2->addWidget(label);

                   ui->hBoxLayout_2->addWidget(produceCode128Button);
                 // ui-> hBoxLayout->addWidget(produceEAN13Button);
                  ui-> hBoxLayout_2->addWidget(savePictureButton);

                  // QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
                    //vBoxLayout->addLayout(hBoxLayout);
                   ui-> vBoxLayout_2->addWidget(barCodeBox);
               /*QSqlQuery qry1;
               qry1.prepare("select cin_cl from commandes");
               qry1.exec();

                     while(qry1.next()){

                     //ui->cin->addItem(qry1.value(0).toString());
                      }*/



                connect(produceCode128Button,SIGNAL(clicked()),this,SLOT(produceBarCode128Slot()));
            //    connect(produceEAN13Button,SIGNAL(clicked()),this,SLOT(produceBarCodeEAN13Slot()));
              connect(savePictureButton,SIGNAL(clicked()),this,SLOT(savePictureSlot()));

                //this->resize(1400,1300);
                ui->le_ref_2->setValidator(new QIntValidator(0,99999999,this));
                //ui->supprimer_ref->setValidator(new QIntValidator(0,99999,this));
               // ui->modifier_ref->setValidator(new QIntValidator(0,99999,this));
                ui->le_cin_2->setValidator(new QIntValidator(0,99999999,this));
                  ui->modifier_cin_2->setValidator(new QIntValidator(0,99999999,this));
                  //ui->modifier_cin_emp->setValidator(new QIntValidator(0,99999999,this));
                 //ui->cin_empl->setValidator(new QIntValidator(0,99999999,this));
                  ui->la_qtt_2->setValidator(new QIntValidator(0,999,this));
                  ui->Modifier_qtt_2->setValidator(new QIntValidator(0,999,this));
                  ui->modifier_montant_2->setValidator(new QIntValidator(0,9999,this));
                   ui->le_mt_2->setValidator(new QIntValidator(0,999,this));
            ui->date_2->setDate(QDate::currentDate());
            ui->modifier_date_2->setDate(QDate::currentDate());
                   ui->le_nbpt_2->setValidator(new QIntValidator(0,9999,this));
            ui->modifier_nbr_pts_2->setValidator(new QIntValidator(0,9999,this));
            //ui->modifier_etat->addItem("");
                   // ui->modifier_type->addItem("");
                    //ui->modifier_livraison->addItem("");

            QSqlQuery qry3,qry2,qry4;
                   qry3.prepare("select ref_cmd from commandes");
                   qry3.exec();
                   qry2.prepare("select cin from employes");
                   qry2.exec();
                   //ui->combo_cin_2->addItem("");
                  while(qry3.next()){

                 // ui->supprimer_combo->addItem(qry.value(0).toString());
                  ui->modifier_combo_2->addItem(qry.value(0).toString());
                   }
                  // ui->combo_ref->addItem("");
                   while(qry2.next()){
                   ui->cin_empl_cmb_2->addItem(qry2.value(0).toString());
                   ui->modifier_cin_emp_cmb_2->addItem(qry2.value(0).toString());}
            qry4.prepare("select * from commandes");
            qry4.exec();
            QStringList completionlist1;
            while(qry4.next()){
                          completionlist <<qry4.value("ref_cmd").toString() <<qry4.value("Nom_cl").toString();
                      }
            StringCompleter=new QCompleter(completionlist1,this);
                       StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
                       ui->recherche_2->setCompleter(StringCompleter);


                   Historique h,h1;
                             ui->historique_2->setText(h.load());

                             ui->historique_3->setText(h1.loadA());
                             ui->presence_emp->setText(h.load_door());




                  //Metier:Notification

                  mSystemTrayIcon= new QSystemTrayIcon(this);
                  mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
            mSystemTrayIcon->setVisible(true);

                 ui->tab_v_2->setModel(Etmp.afficher());


                 //gif
                 QMovie *movie=new QMovie("C:/Users/MSI/Desktop/untitled_cb/scan_gif.gif");
             ui->gif->setMovie(movie);
             movie->start();
             ui->scan_line->setPlaceholderText("Veuillez scanner le code à barre");


    //integration ramy//////////////////////////////////////////////////////////
                     ui->tabledepence->setModel(C.afficher());
                         ui->tablerevenue->setModel(C.afficher2());
                         ui->radioButton_f->setChecked(true);
                         QStringList list,list2;
                         Historique h3;
                         ui->historiquef->setText(h3.load_f());
                         list=cinlist();
                         list2=matlist();
                         ui->mat->addItems(list);
                         ui->mat_3->addItems(list);
                         ui->mat_2->addItems(list2);
                         ui->mat_4->addItems(list2);
                         QSqlQuery qry5;
                         qry5.prepare("select ID_FINANCES from finances");
                         qry5.exec();
                         while(qry5.next()){
                         ui->combo_finance->addItem(qry5.value(0).toString());
                         }
                          QSqlQuery qry6;
                         qry6.prepare("select * from finances");
                         qry6.exec();
                         QStringList completionlist3;
                         while(qry6.next()){
                         completionlist3 <<qry6.value(0).toString() <<qry6.value(4).toString()<<qry6.value(5).toString()<<qry6.value(6).toString();
                          }
                          stringcompleter=new QCompleter(completionlist3,this);
                          stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                          ui->recherche_f->setCompleter(stringcompleter);
                          C.excel_dynamique();
                             setImCorp();
                             setliq();
                             setrev();
                             setdep();
                             setfisc();
                             son =new QSound(":/son/son_QT/Simple_Beep2.wav");


    //integration mohamed//////////////////////////////////////////////////////////
                             ui->tableView_4->setModel(E.afficher_equipements());
                             ui->radioButton_marche_aj->setChecked("");
                             QSqlQuery qry7,qry8,qry9;
                                    qry7.prepare("select cin from employe");
                                    qry7.exec();
                                    qry8.prepare("select REFERENCE_EQUIPEMENT from equipements");
                                    qry8.exec();
                                    ui->combo_cin_aj->addItem("");
                                    while(qry7.next()){
                                    ui->combo_cin_aj->addItem(qry7.value(0).toString());
                                    ui->combo_cin_md->addItem(qry7.value(0).toString());
                                    }
                                    ui->combo_ref_md->addItem("");
                                    while(qry8.next()){
                                    ui->combo_ref_md->addItem(qry8.value(0).toString());
                                    ui->combo_ref_7->addItem(qry8.value(0).toString());
                                     }
                                    qry7.prepare("select * from equipements");
                                    qry7.exec();
                                    while(qry7.next()){
                                        completionlist <<qry7.value("MARQUE_EQUIPEMENT").toString()<<qry7.value("REFERENCE_EQUIPEMENT").toString() <<qry7.value("NOM_EQUIPEMENT").toString();
                                    }
                                    stringcompleter=new QCompleter(completionlist,this);
                                    stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                                    ui->Rechercher_equipement_3->setCompleter(stringcompleter);
                                    Historique h2;
                                    ui->historique_5->setText(h2.load_e());
                                    son=new QSound(":/son/son_QT/Simple_Beep2.wav");
                                    error=new QSound(":/son/son_QT/Error.wav");
                                    success=new QSound(":/son/son_QT/success.wav");
                                    monTimer=new QTimer();
                                    monTimer2=new QTimer();

                                         QObject::connect(monTimer, SIGNAL(timeout()), this,SLOT(finTempo()));
                                         QObject::connect(monTimer2, SIGNAL(timeout()), this,SLOT(finTempo2()));


                                          QMovie *movie1 = new QMovie(":/images/images/giphy.gif");
                                          ui->bubbles_3->setMovie(movie1);
                                          movie1->start();
                                          QMovie *movie2= new QMovie(":/images/images/machinef.gif");
                                          monTimer2->setSingleShot(true); //active le mode singleShot
                                          monTimer2->start(3000); //démarre une tempo de 3 secondes
                                          ui->animation_logo->setMovie(movie2);
                                          movie2->start();
//chat box/////
                                          mSocket= new QTcpSocket(this);
                                          connect(mSocket,&QTcpSocket::readyRead,[&]()
                                          {
                                              QTextStream T(mSocket);
                                              auto text =T.readAll();
                                              ui->textEdit->append(text);
                                          });

                                          //chat box//


    //integration mohamed//////////////////////////////////////////////////////////


           //integration yahya//////////////////////////////////////////////////////////
                                           /*
                                              this->showAddrWeb();
                                            connect(ui->goPushButton,SIGNAL(clicked(bool)),this,SLOT(showAddrWeb()));


                                              ui->le_id->setValidator(new QIntValidator(0,99999999,this));

                                               ui->tableView_2->setModel(L.afficher_livraisons());
                                               ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

                                               QDate date = QDate::currentDate();
                                                  ui->la_date->setDate(date);
                                                  ui->la_date_2->setDate(date);

                                                  //combox
                                               QSqlQuery qry10,qry11,qry12;
                                                   qry10.prepare("select REF_CMD from COMMANDES WHERE OPT_LIVRAISON=1 ");
                                                       qry10.exec();
                                                       while(qry10.next()){
                                                       ui->le_ref_cmd->addItem(qry10.value(0).toString());
                                                       ui->le_ref_cmd_2->addItem(qry10.value(0).toString());
                                                   }
                                                   qry11.prepare("select ID_LIVR from livraisons");
                                                       qry11.exec();
                                                       while(qry11.next()){
                                                        ui->le_id_2->addItem(qry11.value(0).toString());
                                                        ui->le_id_3->addItem(qry11.value(0).toString());
                                                        ui->le_id_4->addItem(qry11.value(0).toString());
                                                        ui->le_id_5->addItem(qry11.value(0).toString());
                                                       }

                                                   qry12.prepare("SELECT ID_LIVR,NOM_LIVREUR,DATE_LIVRAISON,REF_CMD,NOM_CL,ADR_CL FROM livraisons NATURAL JOIN COMMANDES");
                                                       qry12.exec();
                                                       QStringList completionlist6;
                                                       while(qry12.next()){
                                                           completionlist6 <<qry12.value("NOM_LIVREUR").toString()<<qry12.value("ID_LIVR").toString()<<qry12.value("DATE_LIVRAISON").toString()<<qry12.value("REF_CMD").toString()<<qry12.value("NOM_CL").toString()<<qry12.value("ADR_CL").toString();
                                                       }

                                                       stringcompleter=new QCompleter(completionlist6,this);
                                                       stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
                                                       ui->Rechercher_livraisons->setCompleter(stringcompleter);
                                                        qmlRegisterType<SqlEventModel>("org.qtproject.examples.calendar", 1, 0, "SqlEventModel");
                                                                 ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
                                                                   ui->quickWidget->show();*/
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    //arduino amira + zeineb

    bool test=true;
    QString data2 = ard.read_from_arduino();

   qDebug()<<data2;
   qDebug()<<"ind="<<ind;

   QString numstring="";
       for (int var = 0; var < data2.length(); ++var) {

           if (data2.at(var).isDigit()){
                numstring =numstring+QString::number(data2.at(var).digitValue());
           }
       }
       if(ind==5)
       {if(numstring.length()>1)
       {
       QSqlQuery query;
       query.prepare("SELECT FONCTION,SERIAL_NUMBER FROM EMPLOYE WHERE SERIAL_NUMBER LIKE :SERIAL_NUMBER");
       query.bindValue(":SERIAL_NUMBER", numstring);
       query.exec();
       query.next();
       QString serial=query.value("SERIAL_NUMBER").toString();
       QString fonction=query.value("FONCTION").toString();


   qDebug()<<"serial="<<serial;
    if(numstring == serial )
    {

        QMessageBox::information(this,"Access granted",fonction);
        ard.write_to_arduino("1");
    }

    else
    {
        QMessageBox::information(this,"Error","Access denied");
        test=false;
        ard.write_to_arduino("0");
    }
     emp.update(numstring);

    QSqlQuery query1;

        query1.prepare("SELECT * FROM EMPLOYE WHERE SERIAL_NUMBER LIKE :SERIAL_NUMBER");
        query1.bindValue(":SERIAL_NUMBER",numstring);
        query1.exec();
        query1.next();
        QString fn=query1.value("FONCTION").toString();
                QString nom=query1.value("NOM").toString();
                QString prenom=query1.value("PRENOM").toString();

        Historique h;
            ui->presence_emp->setText(h.load_door());
            h.save_door(fn,nom,prenom,test);
            ui->presence_emp->setText(h.load_door());


    }
    ui->tab_employe->setModel(emp.afficher());}
    //arduino ines + ramy
 else if(ind==7)
       {
           if (numstring.length()>=8)

          { ui->lineEditID->setText(numstring);
           QString r=Etmp.recherche_cin_arduino(numstring);
           QString c=Etmp.recherche_cin_arduino_nb_pts(numstring);
            QString g=Etmp.recherche_cin_arduino_emp(numstring);

            //timer

          timer =new QTimer();
          QObject::connect(timer, SIGNAL(timeout()), this,SLOT(finTempo()));

           QMovie *movie2=new QMovie("C:/Users/MSI/Desktop/untitled_cb/gif_error.gif");
           QMovie *movie1=new QMovie("C:/Users/MSI/Desktop/untitled_cb/gif_confirmation.gif");
           timer->setSingleShot(true);
           timer->start(5000);
           if(r=="false")

           {ui->gif->setMovie(movie2);

           movie2->start();
           ui->label_106->setText("code scanné");
           ui->scan_line->setPlaceholderText("le CIN est introuvable.Veuillez rescanner le code à nouveau");
           ui->lineEdit1->setText("Nom est introuvable");

             ui->nb_pts->setText("Nombre de points est introuvable");
           }
           else
           {ui->gif->setMovie(movie1);
               movie1->start();
                ui->scan_line->setPlaceholderText("Opération réussite");
               ui->nb_pts->setText(c);
                    ui->lineEdit1->setText(r);

                    Historique h;
                        h.saveA(r,numstring,c,g);
                        ui->historique_2->setText(h.loadA());

           }

           ui->tab_v_2->setModel(Etmp.afficher());

       QString t=r+" "+c;

           ard.write_to_arduino(t);
          // A.write_to_arduino(c);
               }
            ui->scan_line->setPlaceholderText("Veuillez scanner le code à barre");
           // ui->lineEditID->clear();
           // ui->nb_pts->clear();
        //    ui->lineEdit1->clear();
       }

    //arduino yahya + mohamed
else if(ind==10)
       {
           QString dataa=ard.read_from_arduino();
               qDebug()<< "nb_pieces: "<< dataa;
            ui->nb_pieces_3->setText(dataa+"    Terminé !") ;// si les données reçues de arduino via la liaison série sont égales à 1
               QSqlQuery query;
                query.prepare("Update equipements set nb_pieces= :nb_pieces  where REFERENCE_EQUIPEMENT= :REFERENCE_EQUIPEMENT ");
                QString REFERENCE_EQUIPEMENT=ui->combo_ref_md->currentText() ;
                query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT);
                int d=dataa.toInt();
                query.bindValue(":nb_pieces", d);

                query.exec();
                ui->tableView_4->setModel(E.afficher_equipements());
       }
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
        if (fn=="Gerant" || fn=="Manager")
        {
            ui->stackedWidget->setCurrentIndex(2);
            deplacement=2;
        }
            else if (fn=="Magasinier" || fn=="Storekeeper")
        {
            ui->stackedWidget->setCurrentIndex(3);
            deplacement=3;
        }
        else if (fn=="Caissier" || fn=="Cashier")
        {
            ui->stackedWidget->setCurrentIndex(4);
            deplacement=4;
        }
        else if (fn=="Rh" || fn=="HR")
        {
            ui->stackedWidget->setCurrentIndex(5);
        }
        else if (fn=="Comptable" || fn=="Accountant")
        {
            ui->stackedWidget->setCurrentIndex(8);
        }
    }
    QString image;
    prenom_e=map["prenom"];
     qDebug()<<"widget: "<<map["prenom"];
     image=map["prenom"]+".jpg";
     ui->nom_user->setText(map["prenom"]);// la recuperation du nom de l'utilisateur connecté de la base de données(table employe)
     ui->label_38->setStyleSheet("border-image: url(:/images/images/"+image+");");

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
        double salaire=ui->salaire_employe->text().toInt();
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

        else if(salaire<=0 || salaire>5000)
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
            employe e( cin, nom, prenom, age, email, num_tel, password, fonction, salaire,0,0);

            bool q=e.ajouter();
            if (q)
                QMessageBox::information(this,"success","success");
            else QMessageBox::critical(this,"echec", "query problem");
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

            QSqlQuery query,query2;
            query.prepare("select CIN from Employe");
            query.exec();
            ui->cin_employe_2->addItem("");
            while(query.next())
                ui->cin_employe_2->addItem(query.value(0).toString());

            QStringList CompletionList;
            query2.prepare("select * from Employe");
            query2.exec();
            while(query2.next())
                CompletionList <<query2.value("CIN").toString() <<query2.value("NOM").toString()<<query2.value("AGE").toString()<<query2.value("SALAIRE").toString();
            StringCompleter=new QCompleter(CompletionList, this);
            StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
            ui->recherche_employe->setCompleter(StringCompleter);
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
    ind=0;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_annuler_pass_clicked()
{ind=1;
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_fournisseurs_2_clicked()
{ind=6;
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_commandes_2_clicked()
{ind=7;
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_livraisons_2_clicked()
{ind=10;
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_equipements_2_clicked()
{ind=9;
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_gestion_equipements_clicked()
{ind=9;
     ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_gestion_fournisseurs_clicked()
{ind=6;
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_gestion_commandes_clicked()
{ind=7;
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_gestion_livraisons_clicked()
{ind=10;
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_gestion_finances_clicked()
{
    ind=8;
            ui->stackedWidget->setCurrentIndex(8);
}

//integration zeineb//////////////////////////////////////////////////////////


void MainWindow::on_ajouter_f_clicked()
{
  QString typeachats;
 QMessageBox msgBox;

    QString MATRICULE_F=ui->lineEdit_MATRICULE_F_2->text();
    QString NOMSOCIETE=ui->lineEdit_NOMSOCIETE_2->text();
    QString NUMERO_TEL=ui->lineEdit_NUMERO_TEL_2->text();
     QString ADRESSE_SOCIETE=ui->lineEdit_ADRESSE_SOCIETE_2->text();
       QString EMAIL_F=ui->lineEdit_EMAIL_F_2->text();
       int QUANTITE_F=ui->spinBox_QUANTITE_F_2->text().toInt();
       int PRIX_F=ui->lineEdit_PRIX_F_2->text().toInt();

       int testid=0;
       for (int i=0;i==5;i++)
       {
                  if ((MATRICULE_F[i] >= 'A' && MATRICULE_F[i]<='Z') || (MATRICULE_F[i] >= 'a' && MATRICULE_F[i]<='z'))
                      testid=1;
       }

       int testid2=0;
       for (int i=8;i==10;i++)
       {
                  if ((MATRICULE_F[i] >= 'A' && MATRICULE_F[i]<='Z') || (MATRICULE_F[i] >= 'a' && MATRICULE_F[i]<='z'))
                      testid2=1;
       }



     if  (MATRICULE_F=="" )
            {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                        QObject::tr("Donner la matricule fiscale!"), QMessageBox::Cancel);}

     else if (NOMSOCIETE=="")
      {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                  QObject::tr("Donner le nom de la société!"), QMessageBox::Cancel);}

     else if (NUMERO_TEL=="" )
           {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                       QObject::tr("Donner le numero tel!"), QMessageBox::Cancel);}

     else if (ADRESSE_SOCIETE=="")
           {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                       QObject::tr("Donner l'adresse de la société!"), QMessageBox::Cancel);}

     else if(!ui->lineEdit_ADRESSE_SOCIETE_2->text().contains(" "))
         {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                             QObject::tr("Adresse invalide!"), QMessageBox::Cancel);}

     else if (EMAIL_F=="" )
           {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                       QObject::tr("Donner l'adresse mail!"), QMessageBox::Cancel);}

    else if(!ui->lineEdit_EMAIL_F_2->text().contains("@") || !ui->lineEdit_EMAIL_F_2->text().contains("."))
        {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                            QObject::tr("Adresse mail invalide!"), QMessageBox::Cancel);}

    else if (!((testid!=1) && (MATRICULE_F[6] >= 'A' && MATRICULE_F[6]<='Z') && (MATRICULE_F[7]=="/")&&(testid2!=1)))
          QMessageBox::critical(nullptr, QObject::tr("Echec"),
                      QObject::tr("Matricule fiscale doit etre de la forme 000000A/000!"), QMessageBox::Cancel);
      else

     {
            if (ui->radioButton_TYPE_ACHATF_Machine_2->isChecked())
            typeachats="machine";

            else if (ui->radioButton_TYPE_ACHATF_Produit_2->isChecked())
            typeachats="produit";


            Fournisseurs f( MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, typeachats, QUANTITE_F, PRIX_F);

      bool test=f.ajouter();

      if(test)
      {  ui->tableView_f->setModel(f.afficher());
      QMessageBox::information(nullptr, QObject::tr("success"),
                         QObject::tr("Ajout Effectué\n"
                                     "click cancel to exit"), QMessageBox::Cancel);
      QSqlQuery qry1;

      qry1.prepare("select * from fournisseur");
      qry1.exec();
      QStringList completionlist;
      while(qry1.next()){
          completionlist <<qry1.value("MATRICULE_F").toString() <<qry1.value("NOMSOCIETE").toString() <<qry1.value("ADRESSE_SOCIETE").toString() <<qry1.value("EMAIL_F").toString();
      }
      stringcompleter=new QCompleter(completionlist,this);
      stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
      ui->rechercheA_f->setCompleter(stringcompleter);


      }

      else
         {
          QMessageBox::critical(nullptr, QObject::tr("error"),
                             QObject::tr("Ajout non Effectué\n"
                                         "click cancel to exit"), QMessageBox::Cancel);
      }
      ui->tableView_f->setModel(f.afficher());
                     ui->lineEdit_MATRICULE_F_2->clear();
                     ui->lineEdit_NOMSOCIETE_2->clear();
                     ui->lineEdit_NUMERO_TEL_2->clear();
                     ui->lineEdit_ADRESSE_SOCIETE_2->clear();
                     ui->lineEdit_EMAIL_F_2->clear();
                     ui->spinBox_QUANTITE_F_2->clear();
                     ui->lineEdit_PRIX_F_2->clear();
                    ui->combo_box_modifier_f->clear();
                    ui->recipient_combo_f->clear();

                    ui->lineEdit_MATRICULE_F_2->setFocus();


                    QSqlQuery qry, qry_mail;
                            qry.prepare("select MATRICULE_F from fournisseur");
                            qry.exec();
                           ui->combo_box_modifier_f->addItem("");

                            while(qry.next()){
                             ui->combo_box_modifier_f->addItem(qry.value(0).toString());
                             }

                            qry_mail.prepare("select NOMSOCIETE from fournisseur");
                            qry_mail.exec();
                            ui->recipient_combo_f->addItem("");
                            while(qry_mail.next()){
                             ui->recipient_combo_f->addItem(qry_mail.value(0).toString());
                            }
      }
}


void MainWindow::on_supprimer_f_clicked()
{

    QString MATRICULE_F = ui->tableView_f->selectionModel()->currentIndex().data(Qt::DisplayRole).toString();
     bool test=f.supprimer( MATRICULE_F);
     ui->tableView_f->setModel(f.afficher());
       ui->recipient_combo_f->clear();
     QSqlQuery qry_mail;
     qry_mail.prepare("select NOMSOCIETE from fournisseur");
     qry_mail.exec();
     ui->recipient_combo_f->addItem("");
     ui->rcpt_f->clear();
     while(qry_mail.next()){
      ui->recipient_combo_f->addItem(qry_mail.value(0).toString());
     }

    if(test)
  {
    QMessageBox::information(nullptr, QObject::tr("success"),
                       QObject::tr("Suppression Effectué\n"
                                   "click cancel to exit"), QMessageBox::Cancel);
    }

    else
       {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                           QObject::tr("Suppression non Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);
    }
}


void MainWindow::on_modifier_f_clicked()
{
  QString typeachats1;
    QString MATRICULE_F=ui->combo_box_modifier_f->currentText();
    QString NOMSOCIETE=ui->nom_f->text();
   QString NUMERO_TEL=ui->num_f->text();
    QString ADRESSE_SOCIETE=ui->adresse_f->text();
    QString EMAIL_F=ui->email_f->text();
    int QUANTITE_F=ui->quantite_f->text().toInt();
    int PRIX_F=ui->prix_f->text().toInt();

    if  (MATRICULE_F=="" )
           {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                       QObject::tr("Donner la matricule fiscale!"), QMessageBox::Cancel);}

    else if (NOMSOCIETE=="")
     {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                 QObject::tr("Donner le nom de la société!"), QMessageBox::Cancel);}

    else if (NUMERO_TEL=="" )
          {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                      QObject::tr("Donner le numero tel!"), QMessageBox::Cancel);}

    else if (ADRESSE_SOCIETE=="")
          {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                      QObject::tr("Donner l'adresse de la société!"), QMessageBox::Cancel);}

    else if(!ui->adresse_f->text().contains(" "))
        {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                            QObject::tr("Adresse invalide!"), QMessageBox::Cancel);}

    else if (EMAIL_F=="" )
          {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                      QObject::tr("Donner l'adresse mail!"), QMessageBox::Cancel);}


 else if(!ui->email_f->text().contains("@") || !ui->email_f->text().contains("."))
     {QMessageBox::critical(nullptr, QObject::tr("Echec"),
                         QObject::tr("Adresse mail invalide!"), QMessageBox::Cancel);}

else {
    if (ui->machine_f->isChecked())
    typeachats1="machine";

    else if (ui->produit_f->isChecked())
    typeachats1="produit";

 Fournisseurs f(MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, typeachats1, QUANTITE_F, PRIX_F);

        bool test=f.modifier(f.getMATRICULE_F());

        if(test)
      {  ui->tableView_f->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("success"),
                           QObject::tr("Modification Effectué\n"
                                       "click cancel to exit"), QMessageBox::Cancel);
        }

        else
           {
            QMessageBox::critical(nullptr, QObject::tr("error"),
                               QObject::tr("Modification non Effectué\n"
                                           "click cancel to exit"), QMessageBox::Cancel);
        }
        ui->tableView_f->setModel(f.afficher());
                       ui->combo_box_modifier_f->clear();
                       ui->nom_f->clear();
                       ui->num_f->clear();
                       ui->adresse_f->clear();
                       ui->email_f->clear();
                       ui->quantite_f->clear();
                       ui->prix_f->clear();
                      ui->combo_box_modifier_f->setFocus();

                      QSqlQuery qry;
                                                    qry.prepare("select MATRICULE_F from fournisseur");
                                                    qry.exec();
                                                   ui->combo_box_modifier_f->addItem("");

                                                    while(qry.next()){
                                                     ui->combo_box_modifier_f->addItem(qry.value(0).toString());
                                                     }
   }
}

void MainWindow::on_rechercheA_f_textChanged(const QString & arg1)
{
    ui->tableView_f->setModel(f.Recherche_Avancee(arg1));

}

void MainWindow::on_rechercheA_f_textEdited(const QString & arg1)
{
    ui->tableView_f->setModel(f.Recherche_Avancee(arg1));

}

void MainWindow::on_Tri_f_activated(const QString &arg1)
{
    if(arg1=="Quantité")
    ui->tableView_f->setModel(f.Tri_quantite());
    else if(arg1=="Prix")
    ui->tableView_f->setModel(f.Tri_prix());
    else if(arg1=="Nom Société")
    ui->tableView_f->setModel(f.Tri_nom());

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("waterproof.application@gmail.com" , "waterproofwaterproof", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("waterproof.application@gmail.com", ui->rcpt_f->text() , ui->subject_f->text(),ui->msg_f->toPlainText());
}


void MainWindow::on_recipient_combo_f_activated(const QString &)
{
    QSqlQuery query;
    QString NOMSOCIETE=ui->recipient_combo_f->currentText() ;
   query.prepare("Select EMAIL_F from fournisseur where NOMSOCIETE=:NOMSOCIETE" );
           query.bindValue(":NOMSOCIETE",NOMSOCIETE) ;
           query.exec();
    query.next() ;

    ui->rcpt_f->setText(query.value("EMAIL_F").toString());
}

void MainWindow::on_combo_box_modifier_f_activated(const QString &arg1)
{
    QSqlQuery query;
    QString MATRICULE_F=ui->combo_box_modifier_f->currentText() ;
   query.prepare("Select * from fournisseur where MATRICULE_F=:MATRICULE_F" );
           query.bindValue(":MATRICULE_F",MATRICULE_F) ;
           query.exec();
    query.next() ;
    ui->nom_f->setText(query.value(1).toString());
    ui->num_f->setText(query.value(2).toString());
    ui->adresse_f->setText(query.value(3).toString());
    ui->email_f->setText(query.value(4).toString());


    QString type=query.value(5).toString();
    if(type=="machine")
    ui->machine_f->setChecked("");
    else
    ui->produit_f->setChecked("");

    ui->quantite_f->setSpecialValueText(query.value(6).toString());
    ui->prix_f->setText(query.value(7).toString());
}

//integration ines//////////////////////////////////////////////////////////

void MainWindow::on_pb_ajouter_2_clicked()
{
    QString ref_cmd=ui->le_ref_2->text();
    QString cin_cl =ui->le_cin_2->text();
    int qtt_vet =ui->la_qtt_2->text().toInt();
    int montant_cmd =ui->le_mt_2->text().toInt();
    int etat=ui->etat_cmb_2->currentIndex();
    int nb_pts=ui->le_nbpt_2->text().toInt();
    int type_v=ui->type_cmb_2->currentIndex();
    int livraison=ui->type_livr_cmb_2->currentIndex();
   QString cin=ui->cin_empl_cmb_2->currentText();
    QString Nom_cl=ui->le_nom_2->text();
    QString adr_cl=ui->la_adr_2->text();
    QDate Date_cmd=ui->date_2->date();
    QMessageBox msgbox;

QString qtt_vetS =ui->la_qtt_2->text();
QString montant_cmdS =ui->le_mt_2->text();
QString nb_ptsS=ui->le_nbpt_2->text();
QString type_vS=ui->type_cmb_2->currentText();
QString livraisonS=ui->type_livr_cmb_2->currentText();

QString Date_cmdS=ui->date_2->date().toString();

    Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);

    int erreur=0;

    QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
    bool hasMatch= re.exactMatch(Nom_cl);

    QRegExp rex("^[a-zA-Z0-9_, ]*$");
    bool match=rex.exactMatch(adr_cl);

    if (!hasMatch)
        erreur=1;
    if(cin_cl.length()!=8)
        erreur=2;
        if(C.entierValide(qtt_vet)>5)
            erreur=3;
        if(C.entierValide(montant_cmd)>5)
            erreur=4;
        if(!C.DateValide(Date_cmd))
            erreur=5;
        if(!match)
            erreur=7;
        if(!C.entierValide(nb_pts))
            erreur=8;
        //if(cin.length()!=8)
           // erreur=11;

if (erreur==0)
  {  bool test =C.ajouter();
    if (test)
       {



        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
        bool test1=genererFacture(ref_cmd,cin_cl,qtt_vetS,Date_cmdS,montant_cmdS,type_vS,livraisonS,cin,Nom_cl);

        Historique h;
            h.save(cin,ref_cmd,montant_cmdS,"Ajout");
            ui->historique_2->setText(h.load());
        if(!test1)
           { QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                                       QObject::tr("Facture non générer\n"
                                                   "click cancel to exit"),QMessageBox::Cancel);  }
        else
        {QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("Facture générer avec succés\n"
                                              "Click cancel to exit."),QMessageBox::Cancel);}



        ui->tab_v_2->setModel(Etmp.afficher());
    ui->le_ref_2->clear();
    ui->le_cin_2->clear();
    ui->le_mt_2->clear();
    ui->la_adr_2->clear();
    ui->la_qtt_2->clear();
    ui->le_nom_2->clear();
     ui->le_nbpt_2->clear();
     //ui->supprimer_combo->clear();
     ui->modifier_combo_2->clear();
     QSqlQuery qry;
     qry.prepare("select ref_cmd from commandes");
     qry.exec();
     while(qry.next()){

    // ui->supprimer_combo->addItem(qry.value(0).toString());
     ui->modifier_combo_2->addItem(qry.value(0).toString());
     QSqlQuery qry4;
     qry4.prepare("select * from commandes");
     qry4.exec();
     QStringList completionlist2;
     while(qry4.next()){
                   completionlist2 <<qry4.value("ref_cmd").toString() <<qry4.value("Nom_cl").toString();
               }
     StringCompleter=new QCompleter(completionlist2,this);
                StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
                ui->recherche_2->setCompleter(StringCompleter);
     }

    }
    else
    {QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                           QObject::tr("Ajout non effectué.\n"
                                       "click cancel to exit"),QMessageBox::Ok);}

}else  if (erreur==1)
{ QMessageBox::critical(nullptr,QObject::tr("Nom non valide"),
                         QObject::tr("Ajout nn effectue\n"
                                     "click cancel to exit"),QMessageBox::Cancel);  }
else if(erreur==2)
{QMessageBox::critical(nullptr,QObject::tr("le cin du client est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==3)
{QMessageBox::critical(nullptr,QObject::tr("la quantité est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==4)
{QMessageBox::critical(nullptr,QObject::tr("le montant est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==5)
{QMessageBox::critical(nullptr,QObject::tr("la date est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==7)
{QMessageBox::critical(nullptr,QObject::tr("l'adresse est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                  "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==8)
{QMessageBox::critical(nullptr,QObject::tr("le nombre de points est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}
else if(erreur==11)
{QMessageBox::critical(nullptr,QObject::tr("le cin de l'employe est non valide"),
                       QObject::tr("Ajout non effectué.\n"
                                   "click cancel to exit"),QMessageBox::Cancel);}


}
void MainWindow::on_pb_supprimer_2_clicked()
{
    QString ref_cmd = ui->tab_v_2->selectionModel()->currentIndex().data(Qt::DisplayRole).toString();
 QString cin,mt;
 QSqlQuery query;

            query.prepare("Select * from commandes where ref_cmd=:ref_cmd" );
                    query.bindValue(":ref_cmd",ref_cmd) ;

                    query.exec();

                    query.next() ;
                   cin=query.value(11).toString();
                    mt=query.value(4).toString();




 Etmp.supprimer(ref_cmd);
        ui->tab_v_2->setModel(Etmp.afficher());



        Historique h;
                        h.save(cin,ref_cmd,mt,"Supprimer");
                        ui->historique_2->setText(h.load());

}


void MainWindow::on_pb_modifier_2_clicked()
{
    QString ref_cmd=ui->modifier_combo_2->currentText();
       QString adr_cl=ui->modifier_adr_2->text();
       QString Nom_cl=ui->modifier_nom_2->text();
       QString cin_cl =ui->modifier_cin_2->text();
       QString cin =ui->modifier_cin_emp_cmb_2->currentText();
       int qtt_vet =ui->Modifier_qtt_2->text().toInt();
       int montant_cmd =ui->modifier_montant_2->text().toInt();
       int etat=ui->modifier_etat_2->currentIndex();
       int nb_pts=ui->modifier_nbr_pts_2->text().toInt();
       int type_v=ui->modifier_type_2->currentIndex();
       int livraison=ui->modifier_livraison_2->currentIndex();
         QDate Date_cmd=ui->modifier_date_2->date();
         QString cin_clS=ui->modifier_cin_emp_cmb_2->currentText();
 QString montant_cmds =ui->modifier_montant_2->text();
 QString ref=ui->modifier_combo_2->currentText();


       Commande C(ref_cmd,cin_cl,Nom_cl,qtt_vet,montant_cmd,Date_cmd,etat,adr_cl,nb_pts,type_v,livraison,cin);
       //C.set_ref_equipement(ui->lineEdit_13->text().toInt());
      int erreur=0;
       QRegExp re("([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*");
       bool hasMatch= re.exactMatch(Nom_cl);

       QRegExp rex("^[a-zA-Z0-9_ ]*$");
       bool match=rex.exactMatch(adr_cl);

       if (!hasMatch)
           erreur=1;
           if(C.entierValide(qtt_vet)>5)
               erreur=3;
           if(C.entierValide(montant_cmd)>5)
               erreur=4;
           if(!match)
               erreur=7;
           if(!C.entierValide(nb_pts))
               erreur=8;
         //  if(cin.length()!=8)
               //erreur=11;


           if (erreur==0)
             {if(C.recherche_id(ref_cmd)==true)
      { bool test=C.modifier(C.getRef()) ;

           QMessageBox msgBox;
           if(test)
           {QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Modification effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);
               Historique h;
                              h.save(cin_clS,ref,montant_cmds,"Modification");
                              ui->historique_2->setText(h.load());
               if(etat==1)
               {mSystemTrayIcon ->showMessage(tr("Notification"),tr("La commande n° %1 est prete.").arg(ref_cmd));}
               ui->tab_v_2->setModel(C.afficher());
           }
           else
         {  QMessageBox::information(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification Non effectué\n"
                                                 "Click cancel to exit."),QMessageBox::Cancel);}

               }

else {QMessageBox::critical(nullptr,QObject::tr("Reference introuvable"),
                               QObject::tr("Modification non effectué\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);}

           }
           else  if (erreur==1)
           { QMessageBox::critical(nullptr,QObject::tr("Nom non valide"),
                                    QObject::tr("Modification nn effectue\n"
                                                "click cancel to exit"),QMessageBox::Cancel);  }

           else if(erreur==3)
           {QMessageBox::critical(nullptr,QObject::tr("la quantité est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==4)
           {QMessageBox::critical(nullptr,QObject::tr("le montant est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}

           else if(erreur==7)
           {QMessageBox::critical(nullptr,QObject::tr("l'adresse est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                             "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==8)
           {QMessageBox::critical(nullptr,QObject::tr("le nombre de points est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}
           else if(erreur==11)
           {QMessageBox::critical(nullptr,QObject::tr("le cin de l'employe est non valide"),
                                  QObject::tr("Modification non effectué.\n"
                                              "click cancel to exit"),QMessageBox::Cancel);}

}

void MainWindow::on_comboBox_3_activated(int index)
{
    if(index==0)
    {
          ui->tab_v_2->setModel(Etmp.afficherTrierDescDate());
    }
    else if(index==1)
    {
        ui->tab_v_2->setModel(Etmp.afficherTrierAscDate());
    }
    else if(index==2)
    {
      ui->tab_v_2->setModel(Etmp.afficherTrierDescMontant());
    }
    else if(index==3)
    {
      ui->tab_v_2->setModel(Etmp.afficherTrierAscMontant());
    }
    else if(index==4)
    {
      ui->tab_v_2->setModel(Etmp.afficherTrierDescLivr());
    }
}

void MainWindow::on_modifier_combo_2_activated(int index)
{
    QSqlQuery query;
        QString ref_cmd=ui->modifier_combo_2->currentText() ;
       query.prepare("Select * from commandes where ref_cmd=:ref_cmd" );
               query.bindValue(":ref_cmd",ref_cmd) ;
               query.exec();
        query.next() ;

        ui->modifier_cin_2->setText(query.value(1).toString());
        ui->modifier_nom_2->setText(query.value(2).toString());
        ui->Modifier_qtt_2->setText(query.value(3).toString());
       ui->modifier_montant_2->setText(query.value(4).toString());
       ui->modifier_date_2->setDate(query.value(5).toDate());
       ui->modifier_etat_2->setCurrentIndex(query.value(6).toInt());
        ui->modifier_adr_2->setText(query.value(7).toString());
       ui->modifier_nbr_pts_2->setText(query.value(8).toString());
       ui->modifier_type_2->setCurrentIndex(query.value(9).toInt());
       ui->modifier_livraison_2->setCurrentIndex(query.value(10).toInt());
       ui->modifier_cin_emp_cmb_2->setCurrentText(query.value(11).toString());
}

void MainWindow::produceBarCode128Slot()
{
    QString code= ui->tab_v_2->selectionModel()->currentIndex().data(Qt::DisplayRole).toString();
   // QString code=lineEdit->text();
    BarCode code128;//Définit l'objet qui encode le numéro de code-barres
    QString barCodes;//Enregistrez la chaîne bs, indiquant b : ligne noire s : ligne blanche
    if((barCodes=code128.process128BCode(code))!=NULL)
    {
        barCodeBox->setBarCodes(barCodes);//Définir les valeurs des variables utilisées dans les fonctions de dessin
        barCodeBox->update();
    }
}

/*void MainWindow::produceBarCodeEAN13Slot()
{
    QString code=lineEdit->text();//Obtenir le numéro saisi

    BarCode codeEAN13;//Définit l'objet qui encode le numéro de code-barres
    QString barCodes;//Enregistrez 01 chaînes, indiquant 1 : ligne noire 0 : ligne blanche
    if((barCodes=codeEAN13.processEAN13Code(code))!=NULL)
    {
        barCodeBox->setBarCodes(barCodes);//Définir les valeurs des variables utilisées dans les fonctions de dessin
        barCodeBox->update();//repeindre
    }
}*/

void MainWindow::savePictureSlot()
{
    barCodeBox->savePicture();
}

void MainWindow::on_recherche_2_textChanged(const QString &arg)
{
ui->tab_v_2->setModel(Etmp.Recherche_Avancee(arg));
}
bool MainWindow::genererFacture(QString ref, QString cinS, QString qtt, QString Date, QString mt, QString type, QString livr, QString cin_e, QString nom)
{
    //QPrinter printer;
       //printer.setOutputFormat(QPrinter::PdfFormat);
        QPrinter * impr;
        QPrintDialog pd(this);
        if (pd.exec()==QDialog::Rejected)
            return false;
        impr = pd.printer();
           impr->setOutputFormat(QPrinter::PdfFormat);
          // printer.setOutputFileName("C:/Users/MSI/Desktop/untitled_cb/Facture43.pdf");
        impr->setOutputFileName("C:/Users/MSI/Desktop/untitled_cb/Facture43.pdf");
        QPainter painter;
           QImage logo("C:/Users/MSI/Desktop/Projet_C++_2A7/untitled/logo_c++_1.png");
           QImage logo_scale=logo.scaled(200, 200, Qt::KeepAspectRatio);
           if (!painter.begin(impr))
           {qWarning("failed to open file.");
           return false;}
           painter.drawImage(15,15,logo_scale);
            painter.setPen(Qt::red);
            painter.setFont(QFont("Time New Roman", 30));
                            painter.drawText(490,140,"FACTURE");
                            painter.setPen(Qt::black);
                            painter.setFont(QFont("Time New Roman", 15));
                            painter.setFont(QFont("Time New Roman", 10));
          painter.drawText(10,400,"Reference"); //x,y,txt
          painter.drawText(20,550,ref);
           painter.drawText(100,400,"CIN client");
           painter.drawText(100,550,cinS);
           painter.drawText(190,400,"Nom client");
           painter.drawText(200,550,nom);
           painter.drawText(280,400,"Qtt vetements");
           painter.drawText(320,550,qtt);
           painter.drawText(420,400,"Date");
           painter.drawText(365,550,Date);
           painter.drawText(490,400,"Montant");
           painter.drawText(520,550,mt);
           painter.drawText(570,400,"Type de vetements");

           if(type=="Pontalon")
           {painter.drawText(590,550,"Pontalon");}
           else if(type=="Robe")
           {painter.drawText(590,550,"Robe");}
           else if(type=="Costume")
           {painter.drawText(590,550,"Costume");}

           painter.drawText(740,400,"Livraison");

           if(livr=="Non Livrable")
           {painter.drawText(730,550,"non livrable");}
           else if(livr=="Livraison")
           {painter.drawText(740,550,"livrable");}
           painter.drawText(840,400,"Cin employe");
           painter.drawText(850,550,cin_e);

                             painter.drawRect(350,50,500,150);
                             painter.drawRect(-1,350,950,95);

 painter.setPen(Qt::red);
 painter.setFont(QFont("Times New Roman", 25));
           painter.drawText(180,710,"Merci de nous avoir fait confiance");
          // (*Facture)=&printer;
          // Facture=printer;
           painter.end();

           return true;

}
void MainWindow::finTempo1()
{
    QMovie *movie=new QMovie("C:/Users/MSI/Desktop/untitled_cb/scan_gif.gif");
ui->gif->setMovie(movie);
movie->start();

ui->lineEditID->clear();
ui->nb_pts->clear();
  ui->lineEdit1->clear();

}


//integration ramy//////////////////////////////////////////////////////////

void MainWindow::on_ajouterf_clicked()
{

    son->play();
    QIntValidator v(0, 1000000, this);
    int pos = 0;
    QString ID_FINANCES=id_increment();
    int MONTANT_FINANCE=ui->montant_ajout_f->text().toInt();
    QString MATRICULE_FISC=ui->mat_2->currentText();
    QString ID_COMMANDE=ui->mat->currentText();
    int TYPE_TRANSACTION1;
    if (ui->radioButton_f->isChecked())
    TYPE_TRANSACTION1=0;
    else if (ui->radioButton_2_f->isChecked())
    TYPE_TRANSACTION1=1;
    QDate DATE_FINANCES=ui->date_ajout_f->date();
    QString PROVENANCE=ui->provenance_f->text();
    finances C( DATE_FINANCES, TYPE_TRANSACTION1, PROVENANCE, MONTANT_FINANCE, ID_FINANCES, MATRICULE_FISC, ID_COMMANDE);

    QString montantstring=ui->montant_ajout_f->text();

    if (PROVENANCE=="")
    {
        QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
    }

    else if (C.recherche_id(ID_FINANCES))
    {
        QMessageBox::information(this, "erreur d'ajout","id déjà existant =");
    }
    else if (C.DateValide(DATE_FINANCES))
    {
        QMessageBox::information(this, "erreur d'ajout","date doit être inferieur à la date actuelle");

    }
    else if (!(v.validate(montantstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
    }
    else if (montantstring==NULL)
    {
        QMessageBox::information(this, "erreur d'ajout","le montant ne doit pas être vide");
    }
    else
    {
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    idout(ID_FINANCES.toInt());
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    Historique h;
    h.save_f(ID_FINANCES,"Ajout",prenom_e);
    ui->historiquef->setText(h.load_f());
    QStringList list,list2;
    ui->mat->clear();
    ui->mat_2->clear();
    ui->mat_3->clear();
    ui->mat_4->clear();
    ui->combo_finance->clear();
    list=cinlist();
    list2=matlist();
    ui->mat->addItems(list);
    ui->mat_3->addItems(list);
    ui->mat_2->addItems(list2);
    ui->mat_4->addItems(list2);

    ui->montant_ajout_f->clear();
    ui->provenance_f->clear();
    ui->date_ajout_f->clear();
    QSqlQuery qry;
    qry.prepare("select ID_FINANCES from finances");
    qry.exec();
    while(qry.next()){
    ui->combo_finance->addItem(qry.value(0).toString());
    }
    C.excel_dynamique();
    // Put the focus back into the input box so they can type again:
   QSqlQuery qry1;
  qry1.prepare("select * from finances");
  qry1.exec();
  QStringList completionlist;
  while(qry1.next()){
  completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
   }
   stringcompleter=new QCompleter(completionlist,this);
   stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
   ui->recherche_f->setCompleter(stringcompleter);
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
    }
}
void MainWindow::on_supprimerf_clicked()
{
    son->play();
    QModelIndex index = ui->tabledepence->selectionModel()->currentIndex();
        QString id = index.data(Qt::DisplayRole).toString();
        QModelIndex index2 = ui->tablerevenue->selectionModel()->currentIndex();
            QString id2 = index2.data(Qt::DisplayRole).toString();
       if (id!="")
       {
           if (!C.recherche_id(id))
           {
                QMessageBox::information(this, "erreur de suppression","Id non valide");
           }
           else
           {
      QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            bool test=C.supprimer(id);
            if(test)
            {
      ui->tabledepence->setModel(C.afficher());
      Historique h;
      h.save_f(id,"supprimer",prenom_e);
      ui->historiquef->setText(h.load_f());
      QMessageBox::information(nullptr,"Suppression","operation supprimé");
      QStringList list,list2;
      ui->mat->clear();
      ui->mat_2->clear();
      ui->mat_3->clear();
      ui->mat_4->clear();
      ui->combo_finance->clear();
      list=cinlist();
      list2=matlist();
      ui->mat->addItems(list);
      ui->mat_3->addItems(list);
      ui->mat_2->addItems(list2);
      ui->mat_4->addItems(list2);
      QSqlQuery qry;
      qry.prepare("select ID_FINANCES from finances");
      qry.exec();
      while(qry.next()){
      ui->combo_finance->addItem(qry.value(0).toString());
      }      }
        }
           }
       }
       else if (id2!="")
       {
           if (!C.recherche_id(id2))
           {
                QMessageBox::information(this, "erreur de suppression","Id non valide");
           }
           else
           {
           QMessageBox::StandardButton reply;
             reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                           QMessageBox::Yes|QMessageBox::No);
             if (reply == QMessageBox::Yes) {
                 bool test=C.supprimer(id2);
                 if(test)
                 {
           ui->tablerevenue->setModel(C.afficher2());
           QMessageBox::information(nullptr,"Suppression","operation modifié");
           QSqlQuery qry1;
          qry1.prepare("select * from finances");
          qry1.exec();
          QStringList completionlist;
          while(qry1.next()){
          completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
           }
           stringcompleter=new QCompleter(completionlist,this);
           stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
           ui->recherche_f->setCompleter(stringcompleter);
           QStringList list,list2;
           ui->mat->clear();
           ui->mat_2->clear();
           ui->mat_3->clear();
           ui->mat_4->clear();
           ui->combo_finance->clear();
           list=cinlist();
           list2=matlist();
           ui->mat->addItems(list);
           ui->mat_3->addItems(list);
           ui->mat_2->addItems(list2);
           ui->mat_4->addItems(list2);
           QSqlQuery qry;
           qry.prepare("select ID_FINANCES from finances");
           qry.exec();
           while(qry.next()){
           ui->combo_finance->addItem(qry.value(0).toString());
           }}
                 C.excel_dynamique();
             }
           }       }
}

void MainWindow::on_modifierf_clicked()
{
    son->play();
    QMessageBox msg;
    QIntValidator v(0, 10000, this);
    int pos = 0;

    QString id=ui->combo_finance->currentText();
    QString montantstring=ui->montant_2_f->text();
    QString PROVENANCE=ui->provenance_2_f->text();

    if (PROVENANCE=="")
    {
        QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
    }
    else if (!(v.validate(montantstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
    }
    else
    {

    finances C;
    C.setID_FINANCES(id);
    C.setDATE_FINANCES(ui->date_2_f->date());
    C.setPROVENANCE(ui->provenance_2_f->text());
    C.setMONTANT_FINANCE(ui->montant_2_f->text().toInt());
    C.setID_COMMANDE(ui->mat_3->currentText());
    C.setMATRICULE_FISC(ui->mat_4->currentText());
    if (ui->radioButton_3_f->isChecked())
     C.setTYPE_TRANSACTION(0);
    else if (ui->radioButton_4_f->isChecked())
     C.setTYPE_TRANSACTION(1);


    bool test=C.modifier(C.getID_FINANCES());
    if(test)
    {
        QSqlQuery qry1;
       qry1.prepare("select * from finances");
       qry1.exec();
       QStringList completionlist;
       while(qry1.next()){
       completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
        }
        stringcompleter=new QCompleter(completionlist,this);
        stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->recherche_f->setCompleter(stringcompleter);
        Historique h;
        h.save_f(id,"modifier",prenom_e);
        ui->historiquef->setText(h.load_f());
        msg.setText("modification avec succès");
        ui->tabledepence->setModel(C.afficher());
        ui->tablerevenue->setModel(C.afficher2());
        QStringList list,list2;
        ui->mat->clear();
        ui->mat_2->clear();
        ui->mat_3->clear();
        ui->mat_4->clear();
        ui->combo_finance->clear();
        list=cinlist();
        list2=matlist();
        ui->mat->addItems(list);
        ui->mat_3->addItems(list);
        ui->mat_2->addItems(list2);
        ui->mat_4->addItems(list2);
        QSqlQuery qry;
        qry.prepare("select ID_FINANCES from finances");
        qry.exec();
        while(qry.next()){
        ui->combo_finance->addItem(qry.value(0).toString());
        }
        C.excel_dynamique();
    }
    else
        msg.setText("echec de modification");

    msg.exec();
    }

}

void MainWindow::on_comboBox_trie_f_activated(int index)
{
    if(index==0)
    {
        ui->tabledepence->setModel(C.Trie(0,"DATE_FINANCES"));
    }
    else if (index==1)
    {
        ui->tabledepence->setModel(C.Trie(0,"DATE_FINANCES DESC"));
    }
    else if (index==2)
    {
        ui->tabledepence->setModel(C.Trie(0,"MONTANT_FINANCE"));
    }
    else if (index==3)
    {
        ui->tabledepence->setModel(C.Trie(0,"MONTANT_FINANCE DESC"));
    }

}

void MainWindow::on_comboBox_trie_f_2_activated(int index)
{
    if(index==0)
    {
        ui->tablerevenue->setModel(C.Trie(1,"DATE_FINANCES"));
    }
    else if (index==1)
    {
        ui->tablerevenue->setModel(C.Trie(1,"DATE_FINANCES DESC"));
    }
    else if (index==2)
    {
        ui->tablerevenue->setModel(C.Trie(1,"MONTANT_FINANCE"));
    }
    else if (index==3)
    {
        ui->tablerevenue->setModel(C.Trie(1,"MONTANT_FINANCE DESC"));
    }

}
//************************fin crud************************



void MainWindow::on_Statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances WHERE TYPE_TRANSACTION = 0");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model->setQuery("SELECT SUM(MONTANT_FINANCE) FROM finances WHERE TYPE_TRANSACTION = 1");
    float tranche_montant2=model->data(model->index(0, 0)).toFloat();







    float total=tranche_montant1+tranche_montant2;
    QString a=QString("depenses . "+QString::number((tranche_montant1*100)/total,'f',2)+"%" );
    QString b=QString("revenues .  "+QString::number((tranche_montant2*100)/total,'f',2)+"%" );

    QPieSeries *series = new QPieSeries();
    series->append(a,tranche_montant1);
    series->append(b,tranche_montant2);
    if (tranche_montant1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tranche_montant2!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(" gain: NB: "+ QString::number(tranche_montant2-tranche_montant1));
    chart->legend()->show();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
    QStringList list;
    for(int i=0;i<2;i++)
    {
        if (i==0)
    list.push_back(a);
        else
        list.push_back(b);

    }
    int i=0;
    for(auto slice : series->slices())
    {
       slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
       slice->setLabel(list[i]);
       i++;
    }

    chartView->resize(851,591);
    chartView->setParent(ui->horizontalFramestat);
    chartView->show();

}

void MainWindow::on_Statistique_3_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM finances where TYPE_TRANSACTION = 0 ");
    QPieSeries *series = new QPieSeries();
     QStringList list;
    if(qry.exec())
    {
        while(qry.next())
        {
            series->append(qry.value(0).toString(),qry.value(2).toInt());
            list.push_back(qry.value(4).toString());
        }
    }

   QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("depenses");
    chart->legend()->show();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    QStringList list2;
    int i=0;
    for(auto slice : series->slices())
    {
        list2.push_back(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
        slice->setLabel(list2[i]+" "+list[i]);
      //  slice->setLabel(list[i]);
        i++;
     }

    chartView->resize(851,591);
    chartView->setParent(ui->horizontalFramestat);
    chartView->show();
}
QStringList MainWindow::cinlist()
{
    QSqlQuery query;


    query.prepare("SELECT DISTINCT REF_CMD FROM finances f full join commandes c on c.REF_CMD = f.ID_COMMANDE where REF_CMD is not null");
   QStringList list;
   list.push_back(NULL);
      if(query.exec())
      {
          while( query.next() )
          {
              list.push_back(query.value(0).toString()) ;
          }
      }
      return list;
}
QStringList MainWindow::matlist()
{
    QSqlQuery query;


    query.prepare("SELECT DISTINCT matricule_f FROM finances f full join fournisseur f2 on f.MATRICULE_FISC = f2.matricule_f where matricule_f is not null  "); //MATRICULE_FISC IS not NULL
   QStringList list;
    list.push_back(NULL);
      if(query.exec())
      {
          while( query.next() )
          {
              list.push_back(query.value(0).toString()) ;
          }
      }
      return list;
}


void MainWindow::on_combo_finance_activated(int index)
{
    QSqlQuery query;
    QString ID_FINANCES=ui->combo_finance->currentText() ;
   query.prepare("Select * from finances where ID_FINANCES=:ID_FINANCES" );
           query.bindValue(":ID_FINANCES",ID_FINANCES) ;
           query.exec();
    query.next() ;
   // E.recuperer_equipement(REFERENCE_EQUIPEMENT);
    ui->montant_2_f->setText(query.value(2).toString());
    ui->date_2_f->setDate(query.value(1).toDate());
    ui->provenance_2_f->setText(query.value(4).toString());
    int TYPE_TRANSACTION=query.value(3).toString().toInt();
    if(TYPE_TRANSACTION==0)
    ui->radioButton_3_f->setChecked("");
    else
    ui->radioButton_4_f->setChecked("");
   // ui->combo_cin_2->setCurrentIndex(query.value(5).toInt());
    ui->mat_3->setCurrentText(query.value(5).toString());
    ui->mat_4->setCurrentText(query.value(6).toString());

}

void MainWindow::on_mat_activated(int index)
{
    QSqlQuery query;
    QString REF_CMD=ui->mat->currentText() ;
   query.prepare("Select * from commandes where REF_CMD=:REF_CMD" );
           query.bindValue(":REF_CMD",REF_CMD) ;
           query.exec();
    query.next() ;
    ui->montant_ajout_f->setText(query.value(4).toString());
    ui->date_ajout_f->setDate(query.value(5).toDate());
    ui->provenance_f->setText(query.value(3).toString());

    ui->radioButton_2_f->setChecked("");

    ui->mat_2->setCurrentText("");

}

void MainWindow::on_mat_2_activated(int index)
{
    QSqlQuery query;
    QString MATRICULE_F=ui->mat_2->currentText() ;
   query.prepare("Select * from fournisseur where MATRICULE_F=:MATRICULE_F" );
           query.bindValue(":MATRICULE_F",MATRICULE_F) ;
           query.exec();
    query.next() ;
    ui->montant_ajout_f->setText(query.value(7).toString());
    ui->provenance_f->setText(query.value(1).toString());

    ui->radioButton_f->setChecked("");

    ui->mat->setCurrentText(NULL);

}

void MainWindow::on_recherche_f_textChanged(const QString &arg1)
{
    if (arg1 != NULL)
    ui->tabledepence->setModel(C.recherche_avancee(arg1));
    else
     ui->tabledepence->setModel(C.afficher());

}

void MainWindow::on_tabledepence_doubleClicked(const QModelIndex &index)
{
        QString id = index.data(Qt::DisplayRole).toString();
        bool test=C.supprimer(id);
        if(test)
        {
  ui->tabledepence->setModel(C.afficher());
        }
}

void MainWindow::on_tablerevenue_doubleClicked(const QModelIndex &index)
{
    QString id = index.data(Qt::DisplayRole).toString();
    bool test=C.supprimer(id);
    if(test)
    {
ui->tablerevenue->setModel(C.afficher2());
    }
}
//************************bilan financier************************
void MainWindow::setImCorp()
{
    QStringList list= { "terrain", "batiment(s)", "materiels informatique", "equipements", "divers","total" };
    ui->ImCorp->setRowCount(1);
    ui->ImCorp->setColumnCount(6);
    ui->ImCorp->setHorizontalHeaderLabels(list);
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (MATRICULE_FISC IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();
    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->ImCorp->setItem(0,3,item);
}
void MainWindow::setliq()
{
    QStringList list= { "caisse", "banque","total" };
    ui->liq->setRowCount(1);
    ui->liq->setColumnCount(3);
    ui->liq->setHorizontalHeaderLabels(list);
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (ID_COMMANDE IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();
    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->liq->setItem(0,0,item);
}
void MainWindow::setrev()
{
    QStringList list= { "caisse", "divers","total" };
    ui->rev->setRowCount(1);
    ui->rev->setColumnCount(3);
    ui->rev->setHorizontalHeaderLabels(list);

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQueryModel * model2= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (ID_COMMANDE IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model2->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 1) AND (ID_COMMANDE IS NULL) AND (MATRICULE_FISC IS NULL) ");
    float tranche_montant2=model2->data(model2->index(0, 0)).toFloat();

    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->rev->setItem(0,0,item);

    QString s2 = QString::number(tranche_montant2);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s2);
    ui->rev->setItem(0,1,item2);

    float sum=0;

    for (int i=0;i<2;i++)
    {
     const QAbstractItemModel *model = ui->rev->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s3 = QString::number(sum);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
     ui->rev->setItem(0,2,item3);
}
void MainWindow::setdep()
{
    QStringList list= { "achat", "divers","facture", "salaire","total" };
    ui->dep->setRowCount(1);
    ui->dep->setColumnCount(5);
    ui->dep->setHorizontalHeaderLabels(list);

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQueryModel * model2= new QSqlQueryModel();
    QSqlQueryModel * model3= new QSqlQueryModel();
    QSqlQueryModel * model4= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (MATRICULE_FISC IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model2->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 0) AND (ID_COMMANDE IS NULL) AND (MATRICULE_FISC IS NULL) AND (PROVENANCE not like 'facture')");
    float tranche_montant2=model2->data(model2->index(0, 0)).toFloat();

    model3->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 0) AND (PROVENANCE = 'facture')");
    float tranche_montant3=model3->data(model3->index(0, 0)).toFloat();

    model4->setQuery("SELECT SUM(salaire) AS salaire FROM finances T1 INNER JOIN commandes T2 ON T2.REF_CMD = T1.ID_COMMANDE INNER JOIN EMPLOYES T3 ON T3.cin = T2.CIN_EMPLOYE ");
    float tranche_montant4=(model4->data(model4->index(0, 0)).toFloat())*12;

    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->dep->setItem(0,0,item);

    QString s2 = QString::number(tranche_montant2);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s2);
    ui->dep->setItem(0,1,item2);

    QString s3 = QString::number(tranche_montant3);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
    ui->dep->setItem(0,2,item3);

    QString s4 = QString::number(tranche_montant4);
    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText(s4);
    ui->dep->setItem(0,3,item4);

    float sum=0;

    for (int i=0;i<4;i++)
    {
     const QAbstractItemModel *model = ui->dep->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s5 = QString::number(sum);
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setText(s5);
     ui->dep->setItem(0,4,item5);
}
void MainWindow::setfisc()
{
    QStringList list= { "résultat Net Fiscal", "pourcentage impôt","impôt","résulat fiscal final" };
    ui->fisc->setRowCount(1);
    ui->fisc->setColumnCount(4);
    ui->fisc->setHorizontalHeaderLabels(list);

     QAbstractItemModel *model = ui->rev->model();
     QString revenue_string = model->data(model->index(0, 2), Qt::DisplayRole).toString();
     float revenue= revenue_string.toInt();

     QAbstractItemModel *model2 = ui->dep->model();
     QString depense_string = model2->data(model2->index(0, 4), Qt::DisplayRole).toString();
     float depense= depense_string.toInt();

     QString somme = QString::number(revenue-depense);
     QTableWidgetItem *item = new QTableWidgetItem;
     item->setText(somme);
      ui->fisc->setItem(0,0,item);

}
void MainWindow::on_calcultotal_clicked()
{
    float sum=0;

    for (int i=0;i<5;i++)
    {
     const QAbstractItemModel *model = ui->ImCorp->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s = QString::number(sum);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s);
     ui->ImCorp->setItem(0,5,item2);

}

void MainWindow::on_calcultotal_2_clicked()
{
    float sum=0;

    for (int i=0;i<3;i++)
    {
     const QAbstractItemModel *model = ui->liq->model();
     const QString value = model->data(model->index(0,i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s = QString::number(sum);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s);
     ui->liq->setItem(0,2,item2);
}

void MainWindow::on_calcultotal_3_clicked()
{
    float sum=0;

    for (int i=0;i<2;i++)
    {
     const QAbstractItemModel *model = ui->rev->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s3 = QString::number(sum);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
     ui->rev->setItem(0,2,item3);
}

void MainWindow::on_calcultotal_4_clicked()
{
    float sum=0;

    for (int i=0;i<5;i++)
    {
     const QAbstractItemModel *model = ui->dep->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s5 = QString::number(sum);
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setText(s5);
     ui->dep->setItem(0,4,item5);
}

void MainWindow::on_calcultotal_5_clicked()
{
    double impot=0;
    float resfinal=0;


      QAbstractItemModel *model = ui->fisc->model();
      QAbstractItemModel *model2 = ui->fisc->model();

      QString restring = model->data(model->index(0, 0), Qt::DisplayRole).toString();
      QString pourimpstring = model2->data(model2->index(0, 1), Qt::DisplayRole).toString();
       impot = (restring.toInt())*(pourimpstring.toInt()*0.01);
        QString impostring = QString::number(impot);
     resfinal = (restring.toInt())-(impot);
     QString resfinalstring = QString::number(resfinal);


    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(impostring);
     ui->fisc->setItem(0,2,item);

     QTableWidgetItem *item2 = new QTableWidgetItem;
     item2->setText(resfinalstring);
      ui->fisc->setItem(0,3,item2);


}

void MainWindow::on_excel_clicked()
{
    QTableView *table;


                        table = ui->ImCorp;
                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("export excel"),
                                                 QObject::tr("export avec succes .\n"
                                                           "Click OK to exit."), QMessageBox::Ok);
                       ligne(fileName);
                       part2(fileName);
                       ligne(fileName);
                       part3(fileName);
                       ligne(fileName);
                       part4(fileName);
                       ligne(fileName);
                       part5(fileName);
                   }
}
void MainWindow::part2(QString fileName)
{
    QTableView *table;
                   table = ui->liq;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();

                   }
}
void MainWindow::part3(QString fileName)
{
    QTableView *table;
                   table = ui->rev;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();

                   }
}
void MainWindow::part5(QString fileName)
{
    QTableView *table;
                   table = ui->fisc;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();

                   }
}
void MainWindow::part4(QString fileName)
{
    QTableView *table;
                   table = ui->dep;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();

                   }
}

void MainWindow::ligne(QString fileName)
{
    QTableView *table;
                   table = ui->tableWidget;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");

                       }

                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }

                       file.close();

                   }
}

void MainWindow::on_tabWidget_2_f_tabBarClicked(int index)
{
    setImCorp();
    setliq();
    setrev();
    setdep();
    setfisc();
}
QString MainWindow::id_increment()
{
    QString tmp="";

    int i=0;
    QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/id.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          tmp="";
    QTextStream in(&file);
    QString line;
    while(!file.atEnd()){
    line = file.readLine();
    i++;
    }
    file.close();
    QString is=QString::number(i);
    return is;
}
void MainWindow::idout (int i)
{
    QFile file ("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/id.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << i << "\n";
}


//*******************integration mohamed********************************************
void MainWindow::on_Ajouter_equipement_in_clicked()
{
    son->play();
    int ref=ui->lineEdit_ref_aj->text().toInt();
    QString refs=ui->lineEdit_ref_aj->text();
    QString marque_EQUIPEMENT=ui->lineEdit_marque_aj->text();
    QString nom_EQUIPEMENT=ui->lineEdit_nom_aj->text();
    int annee_EQUIPEMENT=ui->lineEdit_annee_aj->text().toInt();
    //QString nom_produit=ui->lineEdit_12->text();
    QString etat1=ui->radioButton_marche_aj->text();
    QString etat2=ui->radioButton_panne_aj->text();//Jointure statique
    if(ui->radioButton_marche_aj->isChecked() && ui->radioButton_panne_aj->isEnabled())
        etat1="En marche";
    else if(ui->radioButton_panne_aj->isChecked() && ui->radioButton_marche_aj->isEnabled())
        etat1="En panne";
    QString cin=ui->combo_cin_aj->currentText();
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
    ui->cs3_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;

    case 2:
    error->play();
    msgbox.setText("La marque doit être composée seulement par des lettres !");
    ui->cs2_4->setStyleSheet("border-image: url(:/images/images/remove.png);");

    break;

    case 3:
    error->play();
    msgbox.setText("L'année doit être composé par 4 chiffres !");
    ui->cs4_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;

    case 4:
    error->play();
    msgbox.setText("Vérifier les champs vides !");
    break;
    case 5:
    error->play();
    msgbox.setText("L'année doit être supérieure à 2000 !");
     ui->cs4_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
    break;
    case 6:
    error->play();
    msgbox.setText("L'année doit être inférieure ou égale à la date actuelle !");
     ui->cs4_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
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
        ui->Rechercher_equipement_3->setCompleter(stringcompleter);
        ui->combo_ref_md->addItem(refs);
        ui->combo_ref_7->addItem(refs);
        monTimer->setSingleShot(true); //active le mode singleShot

        monTimer->start(2000); //démarre une tempo de 15 secondes
     ui->cs1_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs2_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs3_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
     ui->cs4_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
        success->play();
        msgbox.setText("Ajout avec succes.");
        Historique h;
        h.save_e(cin,refs,"Ajout",prenom_e);
        ui->historique_5->setText(h.load_e());
        ui->tableView_4->setModel(E.afficher_equipements());
          ui->lineEdit_ref_aj->clear();
          ui->lineEdit_nom_aj->clear();
          ui->lineEdit_marque_aj->clear();
          ui->lineEdit_annee_aj->clear();

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
//*******************integration mohamed********************************************

//integration yahya//////////////////////////////////////////////////////////
void MainWindow::on_pushButton_2_clicked()
{

 int id=ui->le_id->text().toInt();
 QString nom_lv=ui->le_nom->text();
 QDate date_lv=ui->la_date->date();


 QString ref_cmd=ui->le_ref_cmd->currentText();



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
         ui->tableView_2->setModel(L.afficher_livraisons());
         ui->le_id->clear();
         //mise a jour des id
          ui->le_id_2->clear();
          ui->le_id_3->clear();
          ui->le_id_4->clear();
          ui->le_id_5->clear();
         QSqlQuery qry1;
         qry1.prepare("select ID_LIVR from livraisons");
             qry1.exec();
             while(qry1.next()){
              ui->le_id_2->addItem(qry1.value(0).toString());
              ui->le_id_3->addItem(qry1.value(0).toString());
              ui->le_id_4->addItem(qry1.value(0).toString());
              ui->le_id_5->addItem(qry1.value(0).toString());
             }

         ui->le_nom->clear();
         QDate date = QDate::currentDate();
            ui->la_date->setDate(date);
//            ui->quickWidget->close();
//            ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
//            ui->quickWidget->show();



     }
     else
         msgbox.setText("Echec d'ajout");

   }
msgbox.exec();

}
void MainWindow::on_supprimer_clicked()
{


    QModelIndex index = ui->tableView_2->selectionModel()->currentIndex();
           int id = index.data(Qt::DisplayRole).toInt();

         QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {

               bool test=L.supprimer_livraison(id);
               if(test)
               {
         ui->tableView_2->setModel(L.afficher_livraisons());
         QMessageBox::information(nullptr,"Suppression","case supprimé");
         //mise a jour des id
          ui->le_id_2->clear();
          ui->le_id_3->clear();
          ui->le_id_4->clear();
          ui->le_id_5->clear();
//          ui->quickWidget->close();
//          ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
//          ui->quickWidget->show();
         QSqlQuery qry1;
         qry1.prepare("select ID_LIVR from livraisons");
             qry1.exec();
             while(qry1.next()){
              ui->le_id_2->addItem(qry1.value(0).toString());
              ui->le_id_3->addItem(qry1.value(0).toString());
              ui->le_id_4->addItem(qry1.value(0).toString());
               ui->le_id_5->addItem(qry1.value(0).toString());

             }

               }
               else
                   QMessageBox::information(nullptr,"Suppression","echc de supprimé");
           }
}


void MainWindow::on_modifier_clicked()
{
    livraisons L;
    QMessageBox msg;






    L.set_id(ui->le_id_2->currentText().toInt());
    L.set_nom_lv(ui->le_nom_3->text());
    L.set_date_lv(ui->la_date_2->date());
    L.set_ref_cmd(ui->le_ref_cmd_2->currentText());
    int erreur=0;

        switch(erreur)
        {
        case 1:
        msg.setText("Le nom doit être composé seulement par des lettres !");
        break;
        case 2:
        msg.setText("La date doit être suppérieur à la date actuel !");
        break;
       // case 3:
       // msg.setText("reference deja existe !");
        //break;


        }
if(erreur==0)
  {
    bool test=L.modifier_livraison(L.get_id());
    if(test)
    {
        msg.setText("modification avec succès");
       ui->tableView_2->setModel(L.afficher_livraisons());
       ui->le_nom_3->clear();
       QDate date = QDate::currentDate();
          ui->la_date_2->setDate(date);
//          ui->quickWidget->close();
//          ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
//          ui->quickWidget->show();


    }
    else
        msg.setText("echec de modification");

  }




    msg.exec();
}




void MainWindow::on_comboBox_activated(const QString &arg1)
{


    if(arg1=="date decroissante")
    ui->tableView_2->setModel(L.afficherTrierDescDate());
    else if(arg1=="date croissante")
    ui->tableView_2->setModel(L.afficherTrierAscDate());
    else if(arg1=="ID decroissant")
    ui->tableView_2->setModel(L.afficherTrierAscId());
    else if(arg1=="ID croissant")
    ui->tableView_2->setModel(L.afficherTrierDescId());


}

void MainWindow::on_pushButton_5_clicked()
{
    QPdfWriter pdf("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/PDF_livraisons.pdf");

                QPainter painter(&pdf);
                QImage image("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/images/logo_c++-1.png");
                painter.drawImage(15,15,image);

                 painter.setPen(Qt::red);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3200,1400,"Bon de Livraison");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.setFont(QFont("Time New Roman", 9));
                                  painter.drawText(400,3800,"ID: ");

                                  painter.drawText(400,4650,"NOM  LIVREUR: ");

                                  painter.drawText(400,5600,"DATE  LIVRAISON: ");

                                  painter.drawText(400,6550,"REF COMMANDE: ");

                                  painter.drawText(400,7500,"NOM CLIENT: ");

                                  painter.drawText(400,8450,"ADRESSE CLIENT:");

                                  painter.drawText(7800,10100,"Signature");
                                  painter.drawText(8150,10300,".");

                 painter.drawRect(100,3000,9400,9000);

                 QSqlQuery query;
                 int id=ui->le_id_4->currentText().toInt();
                 query.prepare("select  ID_LIVR,NOM_LIVREUR,DATE_LIVRAISON,REF_CMD,NOM_CL,ADR_CL FROM livraisons NATURAL JOIN COMMANDES where ID_LIVR=:ID_LIVR");   //on supprime  where ID_LIVR=:ID_LIVR si tout livraisins
                 query.bindValue(":ID_LIVR", id);
                 query.exec();

                 query.next();
                                  painter.drawText(800,3800,query.value(0).toString());
                                  painter.drawText(1550,4650,query.value(1).toString());
                                  painter.drawText(1750,5600,query.value(2).toString());
                                  painter.drawText(1600,6550,query.value(3).toString());
                                  painter.drawText(1400,7500,query.value(4).toString());
                                  painter.drawText(1700,8450,query.value(5).toString());



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

        ui->le_nom_3->setText(query.value(2).toString());
        ui->la_date_2->setDate(query.value(1).toDate());
        ui->le_ref_cmd_2->setCurrentText(query.value(3).toString());

}



void MainWindow::on_Rechercher_livraisons_textEdited(const QString &arg1)
{
   ui->tableView_2->setModel(L.Recherche_Avancee(arg1));
}





void MainWindow::on_Rechercher_livraisons_textChanged(const QString &arg1)
{
  ui->tableView_2->setModel(L.Recherche_Avancee(arg1));
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


void MainWindow::on_Calendrier_clicked()
{

    secDialog= new SECFORMDialog(this);
    secDialog->show();


}

void MainWindow::on_goPushButton_2_clicked()
{

    QDir().rmpath(RESULTS_PATH);
        QDir().mkpath(RESULTS_PATH);

    int ID_LIVR=ui->le_id_5->currentText().toInt();


                 QSqlQuery qry;
                 qry.prepare("select * from LIVRAISONS where ID_LIVR=:ID_LIVR");
                 qry.bindValue(":ID_LIVR",ID_LIVR);
                 qry.exec();

                  QString nom,ref,id,date;//attributs


                while(qry.next()){

                     id=qry.value(0).toString();
                     nom=qry.value(2).toString();
                     date=qry.value(1).toString();
                     ref=qry.value(3).toString();



                 }

                const QString RESULTS_PATH = "C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Qrcode/";
                 QString cc;
                        cc=id+ " " +nom+ " " +date+ " " +ref;


                        using namespace ::qrcodegen;
                 QrCode qr = QrCode::encodeText(cc.toUtf8().constData(), QrCode::Ecc::HIGH);

                 // Read the black & white pixels
                 QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                 for (int y = 0; y < qr.getSize(); y++) {
                     for (int x = 0; x < qr.getSize(); x++) {
                         int color = qr.getModule(x, y);  // 0 for white, 1 for black

                         // You need to modify this part
                         if(color==0)
                             im.setPixel(x, y,qRgb(254, 254, 254));
                         else
                             im.setPixel(x, y,qRgb(0, 0, 0));
                     }
                 }
                 im=im.scaled(100,100);
                 QString nomimg=nom+".PNG";
                 im.save(RESULTS_PATH + nomimg,"PNG");
                ui->qr_code->setPixmap(QPixmap::fromImage(im));
}



void MainWindow::on_Supprimer_equipement_eq_clicked()
{
    son->play();
    equipements E1;
    QModelIndex index = ui->tableView_4->selectionModel()->currentIndex();
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
                ui->Rechercher_equipement_3->setCompleter(stringcompleter);
                Historique h;
                h.save_e(cin,refs,"Supprimer",prenom_e);
                ui->historique_5->setText(h.load_e());
      ui->tableView_4->setModel(E.afficher_equipements());
      ui->combo_ref_md->clear();
      ui->combo_ref_md->addItem("");
      ui->combo_ref_7->clear();
      ui->combo_ref_7->addItem("");

      QSqlQuery qry;
               qry.prepare("select reference_equipement from equipements");
                   qry.exec();
                   while(qry.next()){
                    ui->combo_ref_md->addItem(qry.value(0).toString());
                    ui->combo_ref_7->addItem(qry.value(0).toString());
                   }
      if(cas==1)
      QMessageBox::information(nullptr,"Suppression","Equipement supprimé");
      else if(cas==-1)
      QMessageBox::information(nullptr,"Suppression","Equipement n'est pas supprimé");
            }
        }
}

void MainWindow::on_Modifier_equipement_md_clicked()
{
    son->play();
    int REFERENCE_EQUIPEMENT=ui->combo_ref_md->currentText().toInt() ;
    QString refs=ui->combo_ref_md->currentText();
    QString marque_EQUIPEMENT=ui->lineEdit_marque_md->text();
    QString nom_EQUIPEMENT=ui->lineEdit_nom_md->text();
    int annee_EQUIPEMENT=ui->lineEdit_annee_md->text().toInt();
    //QString nom_produit=ui->lineEdit_12->text();
    QString etat1=ui->radioButton_marche_md->text();
    QString etat2=ui->radioButton_panne_md->text();//Jointure statique
    if(ui->radioButton_marche_md->isChecked())
        etat1="En marche";
    else if(ui->radioButton_panne_md->isEnabled())
        etat1="En panne";
    QString cin=ui->combo_cin_md->currentText();
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
                ui->cs6_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;

                case 2:
                error->play();
                msgbox.setText("La marque doit être composée seulement par des lettres !");
                ui->cs5_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;

                case 3:
                error->play();
                msgbox.setText("L'année doit être supérieure à 2000 !");
                ui->cs7_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                case 4:
                error->play();
                msgbox.setText("Vérifier les champs vides !");
                break;
                case 5:
                error->play();
                msgbox.setText("L'année doit être supérieure à 2000 !");
                ui->cs7_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                case 6:
                error->play();
                msgbox.setText("L'année doit être inférieure ou égale à la date actuelle !");
                ui->cs7_4->setStyleSheet("border-image: url(:/images/images/remove.png);");
                break;
                }

            if(erreur==0)
            {

                    E.set_ref_equipement(ui->combo_ref_md->currentText().toInt());
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
                    ui->Rechercher_equipement_3->setCompleter(stringcompleter);
                    monTimer->setSingleShot(true); //active le mode singleShot

                    monTimer->start(2000); //démarre une tempo de 15 secondes
                 ui->cs5_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
                 ui->cs6_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
                 ui->cs7_4->setStyleSheet("border-image: url(:/images/images/correct.png);");
                    success->play();
                    msgbox.setText("modification avec succés.");
                    Historique h;
                    h.save_e(cin,refs,"Modification",prenom_e);
                    ui->historique_5->setText(h.load_e());
                    ui->tableView_4->setModel(E.afficher_equipements());
                    ui->lineEdit_marque_md->clear();
                    ui->lineEdit_nom_md->clear();
                    ui->lineEdit_annee_md->clear();
                }
                else{
                    error->play();
                    msgbox.setText("Échec de modification");
                    }


            }
            msgbox.exec();
}
//mon code après la temporisation
void MainWindow::finTempo()

{
         ui->cs1_4->setStyleSheet("");
         ui->cs2_4->setStyleSheet("");
         ui->cs3_4->setStyleSheet("");
         ui->cs4_4->setStyleSheet("");
         ui->cs5_4->setStyleSheet("");
         ui->cs6_4->setStyleSheet("");
         ui->cs7_4->setStyleSheet("");
}

void MainWindow::on_combo_ref_md_activated(const QString &arg1)
{
    QSqlQuery query;
    QString REFERENCE_EQUIPEMENT=ui->combo_ref_md->currentText() ;
   query.prepare("Select * from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT" );
           query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT) ;
           query.exec();
    query.next() ;
    ui->lineEdit_marque_md->setText(query.value(1).toString());
    ui->lineEdit_nom_md->setText(query.value(2).toString());
    ui->lineEdit_annee_md->setText(query.value(3).toString());
    QString etat=query.value(4).toString();
    if(etat=="En panne")
    ui->radioButton_panne_md->setChecked("");
    else
    ui->radioButton_marche_md->setChecked("");
    ui->combo_cin_md->setCurrentText(query.value(5).toString());
}

QString MainWindow::on_combo_ref_7_activated(const QString &arg1)
{
    QSqlQuery query;
    QString REFERENCE_EQUIPEMENT=ui->combo_ref_7->currentText() ;
   query.prepare("Select etat_equipement from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT" );
           query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT) ;
           query.exec();
    query.next() ;
    return query.value("etat_equipement").toString();
}

void MainWindow::on_facebook_5_clicked()
{
    QString link = "https://www.facebook.com/MORYS-Fashion-107812848401567";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_instagram_3_clicked()
{
    QString link = "https://www.instagram.com/drycleaningband/";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_Demarrer_arduino_3_clicked()
{
    QString etat=on_combo_ref_7_activated("");
        if(etat=="En panne")
        {

            ard.write_to_arduino("0"); //envoyer 0 à arduino
            QMessageBox::critical(nullptr, QObject::tr("Machine en panne"),
                        QObject::tr("demarrage echouee.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            // ecrire en panne sur l'afficheur et la machine ne demarre pas
            QSqlQuery query;
             query.prepare("Update equipements set nb_pieces= :nb_pieces  where REFERENCE_EQUIPEMENT= :REFERENCE_EQUIPEMENT ");
             QString REFERENCE_EQUIPEMENT=ui->combo_ref_7->currentText() ;
             query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT);
             query.bindValue(":nb_pieces", 0);

             query.exec();
             ui->tableView_4->setModel(E.afficher_equipements());
        }
        else
        {

            ard.write_to_arduino("1"); //envoyer 1 à arduino
            QMessageBox::information(nullptr, QObject::tr("Machine en marche"),
                        QObject::tr("demarrage avec succee.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            // ecrire en marche sur l'afficheur et la machine demarre correctement
        }
}

void MainWindow::on_Trier_equipement_3_activated(const QString &arg1)
{
    if(arg1=="Année")
    ui->tableView_4->setModel(E.Trie_Annee());
    else if(arg1=="Etat")
    ui->tableView_4->setModel(E.Trie_Etat());
    else if(arg1=="Référence croissante")
    ui->tableView_4->setModel(E.Trie_RefASC());
    else if(arg1=="Référence décroissante")
    ui->tableView_4->setModel(E.Trie_RefDESC());
}


void MainWindow::on_Rechercher_equipement_3_textChanged(const QString &arg1)
{
ui->tableView_4->setModel(E.Recherche_Avancee(arg1));
}

void MainWindow::on_chatbox_3_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(11);

}

void MainWindow::on_facebook_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_connecter_clicked()
{
    mSocket->connectToHost("localhost",3333);
    ui->textEdit->setText(load());
    QString temps=get_temps();
    QFile file ("C:/Users/ASUS/Documents/interface/interface/chat.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"Opened at :" <<temps<<"\n\n";
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->line_message->text()!="")
    {
        QTextStream T(mSocket);
        T << ui->nom_user->text()<<": "<<ui->line_message->text();
        mSocket->flush();
        QFile file ("C:/Users/ASUS/Documents/interface/interface/chat.txt");
         if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
          qDebug()<<"erreur";
         QTextStream out(&file);
         out << ui->nom_user->text()<<": "<<ui->line_message->text()<<"\n";
        ui->line_message->clear();

    }
}
QString MainWindow::load(){

    tmp="";
       QFile file("C:/Users/ASUS/Documents/interface/interface/chat.txt");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         tmp="";

       QTextStream in(&file);

      while (!in.atEnd()) {

            QString myString = in.readLine();
            tmp+=myString+"\n";

      }
      return tmp;
}
QString MainWindow::get_temps()
{
    int heure=QDateTime::currentDateTime().time().hour(),minutes=QDateTime::currentDateTime().time().minute();
    QString minutes_st;
    if(minutes>=0 && minutes<=9)
    minutes_st="0"+QString::number(minutes);
    else
        minutes_st=QString::number(minutes);
    return(QString::number(heure)+":"+minutes_st);
}

void MainWindow::on_connecter_2_clicked()
{
    QString temps=get_temps();
    QFile file ("C:/Users/ASUS/Documents/interface/interface/chat.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"\nClosed at :" <<temps<<"\n";
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_connecter_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(deplacement);
}

void MainWindow::on_connecter_4_clicked()
{
  ui->stackedWidget->setCurrentIndex(deplacement);
}

void MainWindow::on_facebook_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_facebook_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_facebook_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_connecter_5_clicked()
{
  ui->stackedWidget->setCurrentIndex(deplacement);
}

void MainWindow::on_connecter_6_clicked()
{
  ui->stackedWidget->setCurrentIndex(deplacement);
}

void MainWindow::on_facebook_10_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::finTempo2()
{
delete ui->animation_logo;

}
