#include "equipements.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include "connection.h"
#include <QPushButton>
equipements::equipements()
{
REFERENCE_EQUIPEMENT=0;MARQUE_EQUIPEMENT="";NOM_EQUIPEMENT="";ANNEE_EQUIPEMENT=0;ETAT_EQUIPEMENT="";CIN="";
}
equipements::equipements(int ref,QString marque,QString nom,int annee,QString etat,QString cin)
{
   REFERENCE_EQUIPEMENT=ref;
   MARQUE_EQUIPEMENT=marque;
   NOM_EQUIPEMENT=nom;
   ANNEE_EQUIPEMENT=annee;
   ETAT_EQUIPEMENT=etat;
   CIN=cin;
}
int equipements:: get_refEQUIPEMENT()
{
   return REFERENCE_EQUIPEMENT;
}
QString equipements:: get_marqueEQUIPEMENT()
{
    return MARQUE_EQUIPEMENT;
}
QString equipements::get_nom_EQUIPEMENT()
{
    return NOM_EQUIPEMENT;
}
int equipements:: get_annee_EQUIPEMENT()
{
    return ANNEE_EQUIPEMENT;
}
QString equipements::get_etat_EQUIPEMENT()
{return ETAT_EQUIPEMENT;}
QString equipements::get_cin(){return CIN;}
void equipements::set_marque_EQUIPEMENT(QString new_marque)
{MARQUE_EQUIPEMENT=new_marque;}
void equipements::set_nom_EQUIPEMENT(QString new_nom)
{NOM_EQUIPEMENT=new_nom;}
void equipements::set_annee_EQUIPEMENT(int new_annee)
{ANNEE_EQUIPEMENT=new_annee;}
void equipements::set_etat_EQUIPEMENT(QString new_etat)
{ETAT_EQUIPEMENT=new_etat;}
void equipements::set_cin(QString new_cin){CIN=new_cin;}
bool equipements::ajouter_equipement()
{
    QString ref_string= QString::number(REFERENCE_EQUIPEMENT);
    QString annee_string= QString::number(ANNEE_EQUIPEMENT);
    QSqlQuery query;
          query.prepare("INSERT INTO EQUIPEMENTS (REFERENCE_EQUIPEMENT, MARQUE_EQUIPEMENT,NOM_EQUIPEMENT,ANNEE_EQUIPEMENT,ETAT_EQUIPEMENT,CIN_EMP ) "
                        "VALUES (:REFERENCE_EQUIPEMENT, :MARQUE_EQUIPEMENT, :NOM_EQUIPEMENT, :ANNEE_EQUIPEMENT, :ETAT_EQUIPEMENT, :CIN)");
          query.bindValue(0, ref_string);
          query.bindValue(1, MARQUE_EQUIPEMENT);
          query.bindValue(2, NOM_EQUIPEMENT);
          query.bindValue(3, annee_string);
          query.bindValue(4, ETAT_EQUIPEMENT);
          query.bindValue(5, CIN);


    return query.exec();
}
QSqlQueryModel* equipements::afficher_equipements()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM equipements");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence équipement"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque équipement"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom équipement"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Année équipement"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat équipement"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));

    return model;
}
bool equipements::modifier_equipement(int REFERENCE_EQUIPEMENT)
    {
    QSqlQuery query;
     query.prepare("Update equipements set MARQUE_EQUIPEMENT= :MARQUE_EQUIPEMENT, NOM_EQUIPEMENT= :NOM_EQUIPEMENT , ANNEE_EQUIPEMENT= :ANNEE_EQUIPEMENT , ETAT_EQUIPEMENT= :ETAT_EQUIPEMENT,CIN_EMP= :CIN  where REFERENCE_EQUIPEMENT= :REFERENCE_EQUIPEMENT ");
     query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT);
     query.bindValue(":MARQUE_EQUIPEMENT", MARQUE_EQUIPEMENT);
     query.bindValue(":NOM_EQUIPEMENT", NOM_EQUIPEMENT);
     query.bindValue(":ANNEE_EQUIPEMENT", ANNEE_EQUIPEMENT);
     query.bindValue(":ETAT_EQUIPEMENT", ETAT_EQUIPEMENT);
     query.bindValue(":CIN", CIN);

    return query.exec();
    }
bool equipements::supprimer_equipement(int ref)
{
    QSqlQuery query;
          query.prepare("Delete from equipements where REFERENCE_EQUIPEMENT=:ref" );
          query.bindValue(0, ref);
    return query.exec();
}
QSqlQueryModel *equipements:: Trie_Etat()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from equipements order by ETAT_EQUIPEMENT" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence équipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque équipement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom équipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Année équipement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat équipement"));


 return model;

}
QSqlQueryModel *equipements:: Trie_Annee()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from equipements order by ANNEE_EQUIPEMENT" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence équipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque équipement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom équipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Année équipement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat équipement"));


 return model;

}
QSqlQueryModel *equipements:: Trie_RefASC()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from equipements order by REFERENCE_EQUIPEMENT" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence équipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque équipement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom équipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Année équipement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat équipement"));


 return model;

}
QSqlQueryModel *equipements:: Trie_RefDESC()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from equipements order by REFERENCE_EQUIPEMENT DESC" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence équipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque équipement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom équipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Année équipement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat équipement"));


 return model;

}
bool equipements:: Chaine_Valid(QString chaine)
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
int equipements:: Longueur_entier(int Valeur)
{
    int Retour = 0;
    while(Valeur !=0)
    {
        Retour++;
        Valeur = Valeur / 10;
    }

    return Retour;
}

bool equipements:: recuperer_equipement(QString REFERENCE_EQUIPEMENT)
{
    QSqlQuery query;
          query.prepare("Select * from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT" );
                  query.bindValue(":REFERENCE_EQUIPEMENT",REFERENCE_EQUIPEMENT) ;
                  query.exec();
                  query.next();

          return query.exec();


}
QSqlQueryModel *equipements::Recherche_Avancee(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipements WHERE REFERENCE_EQUIPEMENT  LIKE'%"+rech+"%' or MARQUE_EQUIPEMENT  LIKE'%"+rech+"%' or NOM_EQUIPEMENT  LIKE'%"+rech+"%' or CIN_EMP  LIKE'%"+rech+"%' ");
    return model;
}
QString equipements::recuperer_nom()
{
    QSqlQuery query;
    QString cin="1";
    query.prepare("Select * from employe " );
    query.exec();
    return query.value(3).toString();
}
int equipements::longueure_bd()
{
    int i=0;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM equipements");
    qry.exec();
    while(qry.next()){
    i++;
     }
    return i;
}
bool equipements::recherche_ref(QString REFERENCE_EQUIPEMENT)
{
    QMessageBox msgBox;
    QSqlQuery query;
    query.prepare("Select * from equipements where REFERENCE_EQUIPEMENT=:REFERENCE_EQUIPEMENT");
    query.bindValue(":REFERENCE_EQUIPEMENT", REFERENCE_EQUIPEMENT);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        return false;
    }
}
