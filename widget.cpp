#include "widget.h"
#include "ui_widget.h"
#include "chat.h"
#include "equipements.h"
#include <QSqlQuery>
#include "mainwindow.h"
widget::widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widget)
{
    QSqlQuery query;
    QString cin="1";
    query.prepare("Select prenom from employes " );
    query.exec();
    QString nom;
    while(query.next()){
    nom= query.value("prenom").toString();
     }
    ui->setupUi(this);
    ui->nom_user->setText(nom);// la recuperation du nom de l'utilisateur connecté de la base de données(table employe)
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


    QTextStream T(mSocket);
    T << ui->nom_user->text()<<": "<<ui->line_message->text();
    mSocket->flush();
    ui->line_message->clear();
}

void widget::on_connecter_clicked()
{
    chat C(this);
    if(C.exec()==QDialog::Rejected){
        return;
    }
    mSocket->connectToHost(C.hostname(),C.port());

}


void widget::on_connecter_2_clicked()
{
    close();
}
