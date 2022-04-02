#ifndef FINANCES_H
#define FINANCES_H

#include <QMainWindow>
#include <QList>
#include <QSharedDataPointer>
#include <QWidget>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
class finances
{
    QString PROVENANCE,ID_FINANCES,MATRICULE_FISC,ID_COMMANDE;
    int MONTANT_FINANCE,TYPE_TRANSACTION;
    QDate DATE_FINANCES;

public:
    finances();
    finances(QDate DATE_FINANCES,int TYPE_TRANSACTION,QString PROVENANCE,int MONTANT_FINANCE,QString ID_FINANCES,QString MATRICULE_FISC,QString ID_COMMANDE);

    QString getPROVENANCE();
    QDate getDATE_FINANCES();
    int getTYPE_TRANSACTION();
    int getMONTANT_FINANCE();
    QString getID_FINANCES();
    QString getID_COMMANDE();
    QString getMATRICULE_FISC();

    void setPROVENANCE(QString PROVENANCE);
    void setDATE_FINANCES(QDate DATE_FINANCES);
    void setTYPE_TRANSACTION (int TYPE_TRANSACTION);
    void setMONTANT_FINANCE (int MONTANT_FINANCE);
    void setID_FINANCES (QString ID_FINANCES);
    void setID_COMMANDE (QString ID_COMMANDE);
    void setMATRICULE_FISC (QString MATRICULE_FISC);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher2();
    QSqlQueryModel* recherche_avancee(QString);
    bool supprimer(QString);
    bool recherche_id(QString);
    bool modifier(QString);
    QSqlQueryModel* Trie(int,QString);

    bool DateValide(QDate Date);
    void excel_dynamique();

};

#endif // FINANCES_H
