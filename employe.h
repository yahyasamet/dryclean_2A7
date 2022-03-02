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
    employe(int,QString,QString,int,QString,int,QString,QString,int);

    int getCIN();
    QString getNom();
    QString getPrenom();
    int getAge();
    QString getEmail();
    int getNum();
    QString getPassword();
    QString getFonction();
    int getSalaire();

    void setCIN (int );
    void setNom (QString );
    void setPrenom (QString);
    void setAge(int );
    void setEmail (QString email);
    void setNum (int );
    void setPassword (QString );
    void setFonction (QString );
    void setSalaire (int );

    bool ajouter();
    bool supprimer(int cin);
    QSqlQueryModel *afficher();
private:
    QString nom,prenom,email,password,fonction;
    int salaire,age,cin,num_tel;
};

#endif // EMPLOYE_H
