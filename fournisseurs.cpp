#include "fournisseurs.h"
#include <QMessageBox>
#include <QDebug>

Fournisseurs::Fournisseurs(QString MATRICULE_F, QString NOMSOCIETE,int NUMERO_TEL,QString ADRESSE_SOCIETE,QString EMAIL_F,QString TYPE_ACHATF, int QUANTITE_F, int PRIX_F)
{
    this->MATRICULE_F=MATRICULE_F;
    this->NOMSOCIETE=NOMSOCIETE;
    this->NUMERO_TEL=NUMERO_TEL;
    this->ADRESSE_SOCIETE=ADRESSE_SOCIETE;
    this->EMAIL_F=EMAIL_F;
    this->TYPE_ACHATF=TYPE_ACHATF;
    this->QUANTITE_F=QUANTITE_F;
    this->PRIX_F=PRIX_F;

}


QString Fournisseurs::getMATRICULE_F()
{ return MATRICULE_F;}
QString Fournisseurs::getNOMSOCIETE()
{return NOMSOCIETE;}
int Fournisseurs::getNUMERO_TEL()
{return NUMERO_TEL;}
QString Fournisseurs::getADRESSE_SOCIETE()
{ return ADRESSE_SOCIETE;}
QString Fournisseurs::getEMAIL_F()
{return EMAIL_F;}
QString Fournisseurs::getTYPE_ACHATF()
{ return TYPE_ACHATF;}
int Fournisseurs::getQUANTITE_F()
{ return QUANTITE_F;}
int Fournisseurs::getPRIX_F()
{return PRIX_F;}

void Fournisseurs::setMATRICULE_F(QString MATRICULE_F)
{this->MATRICULE_F=MATRICULE_F;}
void Fournisseurs::setNOMSOCIETE(QString NOMSOCIETE)
{this->NOMSOCIETE=NOMSOCIETE;}
void Fournisseurs::setNUMERO_TEL(int NUMERO_TEL)
{this->NUMERO_TEL=NUMERO_TEL;}
void Fournisseurs::setADRESSE_SOCIETE (QString ADRESSE_SOCIETE)
{this->ADRESSE_SOCIETE=ADRESSE_SOCIETE;}
void Fournisseurs::setEMAIL_F (QString EMAIL_F)
{this->EMAIL_F=EMAIL_F;}
void Fournisseurs::setTYPE_ACHATF(QString TYPE_ACHATF)
{this->TYPE_ACHATF=TYPE_ACHATF;}
void Fournisseurs::setQUANTITE_F (int QUANTITE_F)
{this->QUANTITE_F=QUANTITE_F;}
void Fournisseurs::setPRIX_F (int PRIX_F)
{this->PRIX_F=PRIX_F;}


bool Fournisseurs::ajouter()
{
    QSqlQuery query;
                query.prepare("INSERT INTO fournisseur ( MATRICULE_F, NOMSOCIETE, NUMERO_TEL, ADRESSE_SOCIETE, EMAIL_F, TYPE_ACHATF,  QUANTITE_F, PRIX_F) "
                              "VALUES ( :MATRICULE_F, :NOMSOCIETE, :NUMERO_TEL, :ADRESSE_SOCIETE, :EMAIL_F, :TYPE_ACHATF,  :QUANTITE_F, :PRIX_F)");
                query.bindValue(":MATRICULE_F", MATRICULE_F);
                query.bindValue(":NOMSOCIETE", NOMSOCIETE);
                query.bindValue(":NUMERO_TEL",NUMERO_TEL);
                query.bindValue(":ADRESSE_SOCIETE",ADRESSE_SOCIETE);
                query.bindValue(":EMAIL_F", EMAIL_F);
                query.bindValue(":TYPE_ACHATF", TYPE_ACHATF);
                query.bindValue(":QUANTITE_F",QUANTITE_F);
                query.bindValue(":PRIX_F",PRIX_F);

                return query.exec();

}
QSqlQueryModel* Fournisseurs::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  fournisseur");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_F"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMSOCIETE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMERO_TEL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_SOCIETE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL_F"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE_ACHATF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("QUANTITE_F"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_F"));


    return model;
}

bool Fournisseurs::supprimer(QString MATRICULE_F){
    QSqlQuery query;


    query.prepare("Delete from fournisseur where MATRICULE_F =:MATRICULE_F");
    query.bindValue(":MATRICULE_F", MATRICULE_F);

    return query.exec();
}







