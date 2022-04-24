#include "chat.h"
#include "ui_chat.h"

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
    //mHostName=ui->hostname->text();
    mHostName="localhost";
    //mPort=ui->port->value();
    mPort=3333;
    accept();
}

void chat::on_annuler_button_clicked()
{

}

