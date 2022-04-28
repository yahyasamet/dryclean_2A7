#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QMainWindow>
#include <QSharedDataPointer>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class employe
{
public:
    employe();
    employe(QString,QString,QString,int,QString,QString,QString,QString,int,int,QString);

    QString getCIN();
    QString getNom();
    QString getPrenom();
    int getAge();
    QString getEmail();
    QString getNum();
    QString getPassword();
    QString getFonction();
    int getSalaire();
    int getPresence();
    QString getSerial_number ();

    void setCIN (QString );
    void setNom (QString );
    void setPrenom (QString);
    void setAge(int );
    void setEmail (QString email);
    void setNum (QString );
    void setPassword (QString );
    void setFonction (QString );
    void setSalaire (int );
    void setPresence (int );
    void setSerial_number (QString);

    bool chercher_password(QString pass);
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel *afficher();
    bool modifier(QString);
    bool string_test(QString ch);
    QSqlQueryModel *tri_cin_asc();
    QSqlQueryModel *tri_cin_desc();
    QSqlQueryModel *tri_nom_asc();
    QSqlQueryModel *tri_nom_desc();
    QSqlQueryModel *tri_age_asc();
    QSqlQueryModel *tri_age_desc();
    QSqlQueryModel *tri_salaire_asc();
    QSqlQueryModel *tri_salaire_desc();
    QSqlQueryModel *recherche_avancee_employe(QString ch);
    bool chercher_employe(QString email);
    bool update(QString);

private:
    QString nom,prenom,email,password,fonction,cin,num_tel,serial_number;
    int age,salaire,presence;
};

#endif // EMPLOYE_H
