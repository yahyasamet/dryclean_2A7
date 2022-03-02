#ifndef FINANCES_H
#define FINANCES_H

#include <QMainWindow>

#include <QSharedDataPointer>
#include <QWidget>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
class finances
{
    QString PROVENANCE;
    int ID_FINANCES,MONTANT_FINANCE,TYPE_TRANSACTION;
    QDate DATE_FINANCES;

public:
    finances();
    finances(QDate DATE_FINANCES,int TYPE_TRANSACTION,QString PROVENANCE,int MONTANT_FINANCE,int ID_FINANCES);

    QString getPROVENANCE();
    QDate getDATE_FINANCES();
    int getTYPE_TRANSACTION();
    int getMONTANT_FINANCE();
    int getID_FINANCES();

    void setPROVENANCE(QString PROVENANCE);
    void setDATE_FINANCES(QDate DATE_FINANCES);
    void setTYPE_TRANSACTION (int TYPE_TRANSACTION);
    void setMONTANT_FINANCE (int MONTANT_FINANCE);
    void setID_FINANCES (int ID_FINANCES);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher2();
    bool supprimer(int);
    bool recherche_id(int);
    bool modifier(int);
};

#endif // FINANCES_H
