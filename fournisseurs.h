#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QUrl>
class Fournisseurs
{
private:
    QString MATRICULE_F, NOMSOCIETE, ADRESSE_SOCIETE, EMAIL_F, TYPE_ACHATF,NUMERO_TEL,PRIX_F;
    int QUANTITE_F;


public:
    Fournisseurs();
    Fournisseurs(QString MATRICULE_F, QString NOMSOCIETE,QString NUMERO_TEL,QString ADRESSE_SOCIETE,QString EMAIL_F,QString TYPE_ACHATF, int QUANTITE_F, QString PRIX_F );

    QString getMATRICULE_F();
    QString getNOMSOCIETE();
    QString getNUMERO_TEL();
    QString getADRESSE_SOCIETE();
    QString getEMAIL_F();
    QString getTYPE_ACHATF();
    int getQUANTITE_F();
    QString getPRIX_F();


    void setMATRICULE_F( QString MATRICULE_F);
    void setNOMSOCIETE(QString NOMSOCIETE);
    void setNUMERO_TEL (QString NUMERO_TEL);
    void setADRESSE_SOCIETE (QString ADRESSE_SOCIETE);
    void setEMAIL_F (QString EMAIL_F);
    void setTYPE_ACHATF (QString TYPE_ACHATF);
    void setQUANTITE_F (int QUANTITE_F);
    void setPRIX_F (QString PRIX_F);

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
