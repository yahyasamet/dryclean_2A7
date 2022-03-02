#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "employe.h"

employe::employe()
{
    cin=0;
    nom="";
    prenom="";
    email="";
    num_tel=0;
    password="";
    fonction="";
    salaire=0;
    age=0;
}

employe::employe(int cin,QString nom,QString prenom,int age,QString email,int num_tel,QString password,QString fonction,int salaire)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
    this->email=email;
    this->num_tel=num_tel;
    this->password=password;
    this->fonction=fonction;
    this->salaire=salaire;
}

int employe::getCIN()
{
    return cin;
}
QString employe::getNom()
{
    return nom;
}
QString employe::getPrenom()
{
    return prenom;
}
int employe::getAge()
{
    return age;
}
QString employe::getEmail()
{
    return email;
}
int employe::getNum()
{
    return num_tel;
}
QString employe::getPassword()
{
    return password;
}
QString employe::getFonction()
{
    return fonction;
}
int employe::getSalaire()
{
    return salaire;
}

void employe::setCIN (int cin)
{
    this->cin=cin;
}
void employe::setNom (QString nom)
{
    this->nom=nom;
}
void employe::setPrenom (QString prenom)
{
    this->prenom=prenom;
}
void employe::setAge (int age)
{
    this->age=age;
}
void employe::setEmail (QString email)
{
    this->email=email;
}
void employe::setNum (int num_tel)
{
    this->num_tel=num_tel;
}
void employe::setPassword (QString password)
{
    this->password=password;
}
void employe::setFonction (QString fonction)
{
    this->fonction=fonction;
}
void employe::setSalaire (int salaire)
{
    this->salaire=salaire;
}

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,PASSWORD,FONCTION,SALAIRE)"" VALUES(:cin, :nom, :prenom, :age, :email, :num_tel, :password,:fonction, :salaire)");
    query.bindValue(0,cin);
    query.bindValue(1,nom);
    query.bindValue(2,prenom);
    query.bindValue(3,age);
    query.bindValue(4,email);
    query.bindValue(5,num_tel);
    query.bindValue(6,password);
    query.bindValue(7,fonction);
    query.bindValue(8,salaire);
    return query.exec();
}

QSqlQueryModel * employe::afficher()
   {
       QSqlQueryModel* model=new QSqlQueryModel();

             model->setQuery("SELECT* FROM EMPLOYE");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
             model->setHeaderData(6, Qt::Horizontal, QObject::tr("PASSWORD"));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("FONCTION"));
             model->setHeaderData(9, Qt::Horizontal, QObject::tr("SALAIRE"));
       return model;

   }
bool employe::supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);
    query.prepare("Delete from EMPLOYE where cin= :cin");
    query.bindValue(":cin",res);
    return query.exec();
}
