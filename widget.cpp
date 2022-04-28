#include "widget.h"
#include "ui_widget.h"
#include "chat.h"
#include "equipements.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include <QDateTime>
widget::widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widget)
{
    QSqlQuery query;
    QString cin="1";
    query.prepare("Select prenom from employe " );
    query.exec();
    QString nom,image;
    //query.next();
    //nom= query.value("prenom").toString();
    nom=prenom_e;
    qDebug()<<"widget: "<<prenom_e;
    image=nom+".jpg";
    ui->setupUi(this);
    ui->nom_user->setText(nom);// la recuperation du nom de l'utilisateur connecté de la base de données(table employe)
    ui->label_4->setStyleSheet("border-image: url(:/images/images/"+image+");");
    mSocket= new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead,[&]()
    {
        QTextStream T(mSocket);
        auto text =T.readAll();
        ui->textEdit->append(text);
    });
}
widget::~widget()
{
    delete ui;
}


void widget::on_pushButton_clicked()
{

if(ui->line_message->text()!="")
{
    QTextStream T(mSocket);
    T << ui->nom_user->text()<<": "<<ui->line_message->text();
    mSocket->flush();
    QFile file ("C:/Users/Amira/Desktop/waterproof/dryclean_2A7/chat.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << ui->nom_user->text()<<": "<<ui->line_message->text()<<"\n";
    ui->line_message->clear();

}

}

void widget::on_connecter_clicked()
{
    mSocket->connectToHost("localhost",3333);
    ui->textEdit->setText(load());
    QString temps=get_temps();
    QFile file ("C:/Users/Amira/Desktop/waterproof/dryclean_2A7/chat.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"Opened at :" <<temps<<"\n\n";

}


void widget::on_connecter_2_clicked()
{
    QString temps=get_temps();
    QFile file ("C:/Users/Amira/Desktop/waterproof/dryclean_2A7/chat.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"\nClosed at :" <<temps<<"\n";
    close();
}
QString widget::load(){

    tmp="";
       QFile file("C:/Users/Amira/Desktop/waterproof/dryclean_2A7/chat.txt");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         tmp="";

       QTextStream in(&file);

      while (!in.atEnd()) {

            QString myString = in.readLine();
            tmp+=myString+"\n";

      }
      return tmp;
}
QString widget::get_temps()
{
    int heure=QDateTime::currentDateTime().time().hour(),minutes=QDateTime::currentDateTime().time().minute();
    QString minutes_st;
    if(minutes>=0 && minutes<=9)
    minutes_st="0"+QString::number(minutes);
    else
        minutes_st=QString::number(minutes);
    return(QString::number(heure)+":"+minutes_st);
}
