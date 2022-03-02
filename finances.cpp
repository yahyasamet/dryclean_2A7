#include "finances.h"
#include <QMessageBox>
#include <QDebug>

finances::finances()
{
   QDate date1(1995,2,2);

   ID_FINANCES=0;
   MONTANT_FINANCE=0;
   PROVENANCE="";
   TYPE_TRANSACTION=0;
   DATE_FINANCES=date1;

}

finances::finances(QDate DATE_FINANCES,int TYPE_TRANSACTION,QString PROVENANCE,int MONTANT_FINANCE,int ID_FINANCES)
{
    this->ID_FINANCES=ID_FINANCES;
    this->MONTANT_FINANCE=MONTANT_FINANCE;
    this->PROVENANCE=PROVENANCE;
    this->TYPE_TRANSACTION=TYPE_TRANSACTION;
    this->DATE_FINANCES=DATE_FINANCES;
}
QString finances::getPROVENANCE()
{ return PROVENANCE;}
QDate finances::getDATE_FINANCES()
{return DATE_FINANCES;}
int finances::getTYPE_TRANSACTION()
{ return TYPE_TRANSACTION;}
int finances::getMONTANT_FINANCE()
{return MONTANT_FINANCE;}
int finances::getID_FINANCES()
{return ID_FINANCES;}

void finances::setPROVENANCE(QString PROVENANCE)
{this->PROVENANCE=PROVENANCE;}
void finances::setDATE_FINANCES(QDate DATE_FINANCES)
{this->DATE_FINANCES=DATE_FINANCES;}
void finances::setTYPE_TRANSACTION (int TYPE_TRANSACTION)
{this->TYPE_TRANSACTION=TYPE_TRANSACTION;}
void finances::setMONTANT_FINANCE (int MONTANT_FINANCE)
{this->MONTANT_FINANCE=MONTANT_FINANCE;}
void finances::setID_FINANCES (int ID_FINANCES)
{this->ID_FINANCES=ID_FINANCES;}
bool finances::ajouter()
{
    QSqlQuery query;
                query.prepare("INSERT INTO finances (ID_FINANCES,DATE_FINANCES,MONTANT_FINANCE,TYPE_TRANSACTION,PROVENANCE) "
                              "VALUES (:ID_FINANCES,:DATE_FINANCES,:MONTANT_FINANCE,:TYPE_TRANSACTION,:PROVENANCE)");
                query.bindValue(":ID_FINANCES", ID_FINANCES);
                query.bindValue(":DATE_FINANCES", DATE_FINANCES);
                query.bindValue(":MONTANT_FINANCE",MONTANT_FINANCE);
                query.bindValue(":TYPE_TRANSACTION",TYPE_TRANSACTION);
                query.bindValue(":PROVENANCE",PROVENANCE);
                return query.exec();

}
QSqlQueryModel* finances::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  finances where TYPE_TRANSACTION=0");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FINANCES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_FINANCES"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_FINANCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PROVENANCE"));


    return model;
}
QSqlQueryModel* finances::afficher2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FINANCES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_FINANCES"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_FINANCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PROVENANCE"));


    return model;
}
bool finances::supprimer(int ID_FINANCES){
    QSqlQuery query;
    finances C;
    QString res=QString::number(ID_FINANCES);

    query.prepare("Delete from finances where ID_FINANCES=:ID_FINANCES");
    query.bindValue(":ID_FINANCES", res);

    return query.exec();
}

bool finances::recherche_id(int ID_FINANCES)
{
    QMessageBox msgBox;
    QSqlQuery query;
    query.prepare("SELECT * FROM finances WHERE ID_FINANCES= :ID_FINANCES");
    query.bindValue(":ID_FINANCES", ID_FINANCES);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("finances n existe pas");
        msgBox.exec();
        return false;
    }
}
bool finances::modifier(int ID_FINANCES)
{
    QSqlQuery query;
    QString id_string=QString::number(ID_FINANCES);

    if (recherche_id(ID_FINANCES))
    {

          query.prepare("UPDATE finances SET DATE_FINANCES=:DATE_FINANCES, MONTANT_FINANCE=:MONTANT_FINANCE,TYPE_TRANSACTION=:TYPE_TRANSACTION,PROVENANCE=:PROVENANCE WHERE ID_FINANCES=:ID_FINANCES");

          query.bindValue(":ID_FINANCES", ID_FINANCES);
          query.bindValue(":DATE_FINANCES", DATE_FINANCES);
          query.bindValue(":MONTANT_FINANCE",MONTANT_FINANCE);
          query.bindValue(":TYPE_TRANSACTION",TYPE_TRANSACTION);
          query.bindValue(":PROVENANCE",PROVENANCE);

    }
          return query.exec();
}
