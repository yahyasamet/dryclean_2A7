#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseurs
{
private:
    QString MATRICULE_F, NOMSOCIETE, ADRESSE_SOCIETE, EMAIL_F, TYPE_ACHATF;
    int NUMERO_TEL, QUANTITE_F, PRIX_F;


public:
    Fournisseurs();
    Fournisseurs(QString MATRICULE_F, QString NOMSOCIETE,int NUMERO_TEL,QString ADRESSE_SOCIETE,QString EMAIL_F,QString TYPE_ACHATF, int QUANTITE_F, int PRIX_F );

    QString getMATRICULE_F();
    QString getNOMSOCIETE();
    int getNUMERO_TEL();
    QString getADRESSE_SOCIETE();
    QString getEMAIL_F();
    QString getTYPE_ACHATF();
    int getQUANTITE_F();
    int getPRIX_F();


    void setMATRICULE_F( QString MATRICULE_F);
    void setNOMSOCIETE(QString NOMSOCIETE);
    void setNUMERO_TEL (int NUMERO_TEL);
    void setADRESSE_SOCIETE (QString ADRESSE_SOCIETE);
    void setEMAIL_F (QString EMAIL_F);
    void setTYPE_ACHATF (QString TYPE_ACHATF);
    void setQUANTITE_F (int QUANTITE_F);
    void setPRIX_F (int PRIX_F);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier(QString);
    bool recuperer_fournisseur(QString MATRICULE_F);
    QSqlQueryModel * Recherche_Avancee(QString);
    QSqlQueryModel *Tri_quantite();
    QSqlQueryModel *Tri_prix();
    QSqlQueryModel *Tri_nom();




};

#endif // FOURNISSEURS_H
