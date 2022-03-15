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
    employe(QString,QString,QString,int,QString,QString,QString,QString,int);

    QString getCIN();
    QString getNom();
    QString getPrenom();
    int getAge();
    QString getEmail();
    QString getNum();
    QString getPassword();
    QString getFonction();
    int getSalaire();

    void setCIN (QString );
    void setNom (QString );
    void setPrenom (QString);
    void setAge(int );
    void setEmail (QString email);
    void setNum (QString );
    void setPassword (QString );
    void setFonction (QString );
    void setSalaire (int );

    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel *afficher();
    bool modifier(QString);
    bool string_test(QString ch);
    bool recherche(QString CIN);

private:
    QString nom,prenom,email,password,fonction,cin,num_tel;
    int salaire,age;
};

#endif // EMPLOYE_H
