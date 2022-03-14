#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H
#include<QString>
#include <QSqlQueryModel>
class equipements
{
public:
    equipements();
    equipements(int,QString,QString,int,QString,QString);
    int get_refEQUIPEMENT();
    QString get_marqueEQUIPEMENT();
    QString get_nom_EQUIPEMENT();
    int get_annee_EQUIPEMENT();
    QString get_etat_EQUIPEMENT();
    QString get_cin();
    void set_ref_equipement(int new_ref){REFERENCE_EQUIPEMENT=new_ref;};
    void set_marque_EQUIPEMENT(QString);
    void set_nom_EQUIPEMENT(QString);
    void set_annee_EQUIPEMENT(int);
    void set_etat_EQUIPEMENT(QString);
    void set_cin(QString);
    bool ajouter_equipement();
    QSqlQueryModel * afficher_equipements();
    bool modifier_equipement(int);
    bool supprimer_equipement(int);
    QSqlQueryModel * Trie_Etat();
    QSqlQueryModel * Trie_Annee();
    QSqlQueryModel * Trie_RefASC();
    QSqlQueryModel * Trie_RefDESC();
    QSqlQueryModel * Recherche_Avancee(QString);
    bool Chaine_Valid(QString);
    int Longueur_entier(int);
    bool recuperer_equipement(QString);
    QString recuperer_nom();

private:
    int REFERENCE_EQUIPEMENT;
    QString MARQUE_EQUIPEMENT ;
    QString NOM_EQUIPEMENT;
    int ANNEE_EQUIPEMENT;
    QString ETAT_EQUIPEMENT;
    QString CIN;



};

#endif // EQUIPEMENTS_H
