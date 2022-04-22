#include "chat.h"
#include "ui_chat.h"
#include <QProcess>

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
}

chat::~chat()
{
    delete ui;
}

void chat::on_accepter_button_clicked()
{
    //executer le serveur locale ****************************************************************
    QProcess*   process = new QProcess();
    //QString program = "C:/Qt/Qt5.9.9/Tools/QtCreator/bin/kjjk/messengerLANserver.exe";
    QString program = "C:/Users/Amira/Desktop/esprit/sem2/qt/integration/serveur_locale/messengerLANserver.exe";
    process->start(program);
    //executer le serveur locale ****************************************************************
    //mHostName=ui->hostname->text();
    mHostName="localhost";
    //mPort=ui->port->value();
    mPort=3333;
    accept();
}

void chat::on_annuler_button_clicked()
{

}

