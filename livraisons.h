#ifndef LIVRAISONS_H
#define LIVRAISONS_H
#include<QString>
#include<QDate>
#include <QSqlQueryModel>
class livraisons
{
public:
    livraisons();
    livraisons(int,QDate,QString);
    int get_id();
    QString get_nom_lv();
    QDate get_date_lv();

    void set_nom_lv(QString);
    void set_date_lv(QDate);
    void set_id(int);

    bool ajouter_livraisons();
    QSqlQueryModel * afficher_livraisons();
    bool supprimer_livraison(int);
    bool recherche_int(int);
    bool modifier_livraison(int);
    QSqlQueryModel * afficherTrierDescDate();
    QSqlQueryModel *afficherTrierAscDate();

private:
    int id;
    QString nom_lv ;
    QDate date_lv;



};















#endif // LIVRAISONS_H
