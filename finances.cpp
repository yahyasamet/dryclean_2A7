#include "finances.h"
#include <QMessageBox>
#include <QDebug>

finances::finances()
{
   QDate date1(1995,2,2);

   ID_FINANCES="";
   MONTANT_FINANCE=0;
   PROVENANCE="";
   TYPE_TRANSACTION=0;
   DATE_FINANCES=date1;
   MATRICULE_FISC="";
   ID_COMMANDE="";

}

finances::finances(QDate DATE_FINANCES,int TYPE_TRANSACTION,QString PROVENANCE,int MONTANT_FINANCE,QString ID_FINANCES,QString MATRICULE_FISC,QString ID_COMMANDE)
{
    this->ID_FINANCES=ID_FINANCES;
    this->MONTANT_FINANCE=MONTANT_FINANCE;
    this->PROVENANCE=PROVENANCE;
    this->TYPE_TRANSACTION=TYPE_TRANSACTION;
    this->DATE_FINANCES=DATE_FINANCES;
    this->TYPE_TRANSACTION=TYPE_TRANSACTION;
    this->DATE_FINANCES=DATE_FINANCES;
    this->MATRICULE_FISC=MATRICULE_FISC;
    this->ID_COMMANDE=ID_COMMANDE;
}
QString finances::getPROVENANCE()
{ return PROVENANCE;}
QDate finances::getDATE_FINANCES()
{return DATE_FINANCES;}
int finances::getTYPE_TRANSACTION()
{ return TYPE_TRANSACTION;}
int finances::getMONTANT_FINANCE()
{return MONTANT_FINANCE;}
QString finances::getID_FINANCES()
{return ID_FINANCES;}
QString finances::getID_COMMANDE()
{return ID_COMMANDE;}
QString finances::getMATRICULE_FISC()
{return MATRICULE_FISC;}

void finances::setPROVENANCE(QString PROVENANCE)
{this->PROVENANCE=PROVENANCE;}
void finances::setDATE_FINANCES(QDate DATE_FINANCES)
{this->DATE_FINANCES=DATE_FINANCES;}
void finances::setTYPE_TRANSACTION (int TYPE_TRANSACTION)
{this->TYPE_TRANSACTION=TYPE_TRANSACTION;}
void finances::setMONTANT_FINANCE (int MONTANT_FINANCE)
{this->MONTANT_FINANCE=MONTANT_FINANCE;}
void finances::setID_FINANCES (QString ID_FINANCES)
{this->ID_FINANCES=ID_FINANCES;}
void finances::setID_COMMANDE(QString ID_COMMANDE)
{this->ID_COMMANDE=ID_COMMANDE;}
void finances::setMATRICULE_FISC(QString MATRICULE_FISC)
{this->MATRICULE_FISC=MATRICULE_FISC;}

bool finances::ajouter()
{
    QSqlQuery query;
                query.prepare("INSERT INTO finances (ID_FINANCES,DATE_FINANCES,MONTANT_FINANCE,TYPE_TRANSACTION,PROVENANCE,ID_COMMANDE,MATRICULE_FISC) "
                              "VALUES (:ID_FINANCES,:DATE_FINANCES,:MONTANT_FINANCE,:TYPE_TRANSACTION,:PROVENANCE,:ID_COMMANDE,:MATRICULE_FISC)");
                query.bindValue(":ID_FINANCES", ID_FINANCES);
                query.bindValue(":DATE_FINANCES", DATE_FINANCES);
                query.bindValue(":MONTANT_FINANCE",MONTANT_FINANCE);
                query.bindValue(":TYPE_TRANSACTION",TYPE_TRANSACTION);
                query.bindValue(":PROVENANCE",PROVENANCE);
                query.bindValue(":ID_COMMANDE",ID_COMMANDE);
                query.bindValue(":MATRICULE_FISC",MATRICULE_FISC);
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
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MATRICULE_FISC"));


    return model;
}
QSqlQueryModel* finances::recherche_avancee(QString terme)
{
    QSqlQueryModel * model =new QSqlQueryModel();
       QSqlQuery query;
       query.prepare("select * from finances where PROVENANCE=:terme or ID_FINANCES=:terme or ID_COMMANDE=:terme or MATRICULE_FISC=:terme ");
       query.bindValue(":terme",terme);
       query.exec();
       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FINANCES"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_FINANCES"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_FINANCE"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_TRANSACTION"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("PROVENANCE"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("MATRICULE_FISC"));

       return model;

}
QSqlQueryModel* finances::afficher2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  finances where TYPE_TRANSACTION=1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FINANCES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_FINANCES"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_FINANCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PROVENANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MATRICULE_FISC"));


    return model;
}
bool finances::supprimer(QString ID_FINANCES){
    QSqlQuery query;
    finances C;

    query.prepare("Delete from finances where ID_FINANCES=:ID_FINANCES");
    query.bindValue(":ID_FINANCES", ID_FINANCES);

    return query.exec();
}

bool finances::recherche_id(QString ID_FINANCES)
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
        return false;
    }
}
bool finances::modifier(QString ID_FINANCES)
{
    QSqlQuery query;

    if (recherche_id(ID_FINANCES))
    {

          query.prepare("UPDATE finances SET DATE_FINANCES=:DATE_FINANCES, MONTANT_FINANCE=:MONTANT_FINANCE,TYPE_TRANSACTION=:TYPE_TRANSACTION,PROVENANCE=:PROVENANCE,ID_COMMANDE=:ID_COMMANDE,MATRICULE_FISC=:MATRICULE_FISC WHERE ID_FINANCES=:ID_FINANCES");

          query.bindValue(":ID_FINANCES", ID_FINANCES);
          query.bindValue(":DATE_FINANCES", DATE_FINANCES);
          query.bindValue(":MONTANT_FINANCE",MONTANT_FINANCE);
          query.bindValue(":TYPE_TRANSACTION",TYPE_TRANSACTION);
          query.bindValue(":PROVENANCE",PROVENANCE);
          query.bindValue(":ID_COMMANDE",ID_COMMANDE);
          query.bindValue(":MATRICULE_FISC",MATRICULE_FISC);


    }
          return query.exec();
}
QSqlQueryModel* finances::Trie(int type,QString ordres)
{
    QSqlQueryModel * model =new QSqlQueryModel();
           QSqlQuery query;
           QString type_s = QString::number(type);
           if (ordres=="DATE_FINANCES")
           query.prepare("SELECT* FROM  finances where TYPE_TRANSACTION=:type_s order by DATE_FINANCES");
           else if (ordres=="DATE_FINANCES DESC")
           query.prepare("SELECT* FROM  finances where TYPE_TRANSACTION=:type_s order by DATE_FINANCES DESC");
           else if(ordres=="MONTANT_FINANCE")
           query.prepare("SELECT* FROM  finances where TYPE_TRANSACTION=:type_s order by MONTANT_FINANCE");
           else
           query.prepare("SELECT* FROM  finances where TYPE_TRANSACTION=:type_s order by MONTANT_FINANCE DESC");

           query.bindValue(":type_s",type_s);
           query.exec();
           model->setQuery(query);

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FINANCES"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_FINANCES"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_FINANCE"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_TRANSACTION"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("PROVENANCE"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("MATRICULE_FISC"));

           return model;
}
bool finances::DateValide(QDate Date)

    {

        if (Date > QDate::currentDate())

           {return true;}

        else
            return false;

    }
void finances::excel_dynamique()
{

                   QFile file("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/sheet.csv");
                   QSqlQueryModel* model=new QSqlQueryModel();
                   model->setQuery("SELECT* FROM  finances");

                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
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
