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
    QString PROVENANCE,ID_FINANCES,MATRICULE_FISC;
    int MONTANT_FINANCE,TYPE_TRANSACTION,ID_COMMANDE;
    QDate DATE_FINANCES;

public:
    finances();
    finances(QDate DATE_FINANCES,int TYPE_TRANSACTION,QString PROVENANCE,int MONTANT_FINANCE,QString ID_FINANCES,QString MATRICULE_FISC,int ID_COMMANDE);

    QString getPROVENANCE();
    QDate getDATE_FINANCES();
    int getTYPE_TRANSACTION();
    int getMONTANT_FINANCE();
    QString getID_FINANCES();
    int getID_COMMANDE();
    QString getMATRICULE_FISC();

    void setPROVENANCE(QString PROVENANCE);
    void setDATE_FINANCES(QDate DATE_FINANCES);
    void setTYPE_TRANSACTION (int TYPE_TRANSACTION);
    void setMONTANT_FINANCE (int MONTANT_FINANCE);
    void setID_FINANCES (QString ID_FINANCES);
    void setID_COMMANDE (int ID_COMMANDE);
    void setMATRICULE_FISC (QString MATRICULE_FISC);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher2();
    bool supprimer(QString);
    bool recherche_id(QString);
    bool modifier(QString);
    QSqlQueryModel* Trie_dateC();
    QSqlQueryModel* Trie_dateD();
    QSqlQueryModel* Trie_montantC();
    QSqlQueryModel* Trie_montantD();
    QSqlQueryModel* Trie_dateC2();
    QSqlQueryModel* Trie_dateD2();
    QSqlQueryModel* Trie_montantC2();
    QSqlQueryModel* Trie_montantD2();
};

#endif // FINANCES_H
