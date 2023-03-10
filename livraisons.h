#ifndef LIVRAISONS_H
#define LIVRAISONS_H
#include<QString>
#include<QDate>

#include <QSqlQueryModel>
class livraisons
{
public:
    livraisons();
    livraisons(int,QDate,QString,QString);
    int get_id();
    QString get_nom_lv();
    QDate get_date_lv();
    QString get_ref_cmd();

    void set_nom_lv(QString);
    void set_date_lv(QDate);
    void set_id(int);
    void set_ref_cmd(QString);

    bool ajouter_livraisons();
    QSqlQueryModel * afficher_livraisons();
    bool supprimer_livraison(int);
    bool recherche_int(int);
    bool modifier_livraison(int);
    bool NOM_Valid(QString );
    int  entierValide(int);
     bool DateValide(QDate );
    QSqlQueryModel * afficherTrierDescDate();
    QSqlQueryModel *afficherTrierAscDate();
    QSqlQueryModel * afficherTrierDescId();
    QSqlQueryModel *afficherTrierAscId();
    QSqlQueryModel * Recherche_Avancee(QString);
    //
    int chercher_ref(QString );
    int chercher_id(int );


private:
    int id;
    QString nom_lv ;
    QDate date_lv;
    QString ref_cmd;



};















#endif // LIVRAISONS_H
