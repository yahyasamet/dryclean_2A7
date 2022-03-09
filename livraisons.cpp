#include "livraisons.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QMessageBox>

livraisons::livraisons()
{
id=0;
nom_lv=" ";
}
livraisons::livraisons(int id ,QDate date_lv,QString nom_lv,int ref_cmd)
{
    this->id=id;
    this->nom_lv=nom_lv;
    this->date_lv=date_lv;
    this->ref_cmd=ref_cmd;

}
int livraisons::get_id()
{return id;}
QString livraisons::get_nom_lv()
{return nom_lv;}
QDate livraisons::get_date_lv()
{return date_lv;}
int livraisons::get_ref_cmd()
{return ref_cmd;}

void livraisons::set_nom_lv(QString nom_lv)
{ this->nom_lv=nom_lv;
    }
void livraisons::set_date_lv(QDate date_lv)
{this->date_lv=date_lv;}
void livraisons::set_id(int id)
{this->id=id;}
void livraisons::set_ref_cmd(int ref_cmd)
{this->ref_cmd=ref_cmd;}
bool livraisons::ajouter_livraisons()
{

    QSqlQuery query;
    QString id_string= QString ::number(id);

          query.prepare("INSERT INTO LIVRAISONS (ID_LIVR,DATE_LIVRAISON,NOM_LIVREUR,REF_CMD ) "
                        "VALUES (:ID_LIVR, :DATE_LIVRAISON, :NOM_LIVREUR, :REF_CMD)");


          query.bindValue(0, id_string);
          query.bindValue(1, date_lv);
          query.bindValue(2, nom_lv);
          query.bindValue(3,ref_cmd);



    return query.exec();



}
    QSqlQueryModel * livraisons::afficher_livraisons()
    {


        QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT* FROM livraisons");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM LIVREUR"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE COMMANDE"));

        return model;

    }
    bool livraisons::supprimer_livraison(int ID){
        QSqlQuery query;
        livraisons C;

        query.prepare("Delete from livraisons where ID_LIVR=:ID_LIVR");
        query.bindValue(":ID_LIVR", ID);

        return query.exec();
    }

    bool livraisons::recherche_int(int ID)
    {
        QMessageBox msgBox;
        QSqlQuery query;
         QString cin_string=QString::number(ID);
        query.prepare("SELECT * FROM livraisons WHERE ID_LIVR= :ID_LIVR");
        query.bindValue(":ID_LIVR", ID);
        if (query.exec() && query.next())
        {
                return true;
        }
        else
        {
            msgBox.setText("livraisons n existe pas");
            msgBox.exec();
            return false;
        }
    }
    bool livraisons::modifier_livraison(int ID)
    {
        QSqlQuery query;


        if (recherche_int(ID))
        {

              query.prepare("UPDATE livraisons SET DATE_LIVRAISON=:DATE_LIVRAISON,NOM_LIVREUR=:NOM_LIVREUR,REF_CMD=:REF_CMD  WHERE ID_LIVR=:ID_LIVR");
              query.bindValue(":ID_LIVR", ID);
              query.bindValue(":DATE_LIVRAISON",date_lv);
              query.bindValue(":NOM_LIVREUR",nom_lv);
              query.bindValue(":REF_CMD",ref_cmd);

        }
              return query.exec();
    }


    bool livraisons:: NOM_Valid(QString chaine)
    {
        int i=0;
        while(i<chaine.size())
        {
            if(! ((chaine[i]>='A' && chaine[i]<='Z')|| (chaine[i]>='a' && chaine[i]<='z')))
            {
               return false;
            }
            else
                i++;
        }
        return true;
    }

    int livraisons::entierValide(int entier)

    {

        int Retour = 0;

            while(entier !=0)

            {

                Retour++;

                entier = entier / 10;

            }



            return Retour;

    }


    bool livraisons::DateValide(QDate Date)

    {

        if (Date!=QDate::currentDate())

           {return false;}

        else return true;

    }

    QSqlQueryModel * livraisons::afficherTrierDescDate()
    {
        QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("select * from livraisons order by DATE_LIVRAISON DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM LIVREUR"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE COMMANDE"));
        return model;


    }

    QSqlQueryModel * livraisons::afficherTrierAscDate()
    {
        QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("select * from livraisons order by DATE_LIVRAISON ASC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM LIVREUR"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE COMMANDE"));
        return model;


    }
    QSqlQueryModel * livraisons::afficherTrierDescId()
    {
        QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("select * from livraisons order by ID_LIVR DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM LIVREUR"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE COMMANDE"));
        return model;


    }

    QSqlQueryModel * livraisons::afficherTrierAscId()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from livraisons order by ID_LIVR ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM LIVREUR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFERENCE COMMANDE"));
    return model;


}



