#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "employe.h"

employe::employe()
{
    cin="";
    nom="";
    prenom="";
    email="";
    num_tel="";
    password="";
    fonction="";
    salaire=0;
    age=0;
    presence=0;
    serial_number="";
}

employe::employe(QString cin,QString nom,QString prenom,int age,QString email,QString num_tel,QString password,QString fonction,int salaire,int presence,QString serial_number)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
    this->email=email;
    this->num_tel=num_tel;
    this->password=password;
    this->fonction=fonction;
    this->salaire=salaire;
    this->presence=presence;
    this->serial_number=presence;
}

QString employe::getCIN()
{
    return cin;
}
QString employe::getNom()
{
    return nom;
}
QString employe::getPrenom()
{
    return prenom;
}
int employe::getAge()
{
    return age;
}
QString employe::getEmail()
{
    return email;
}
QString employe::getNum()
{
    return num_tel;
}
QString employe::getPassword()
{
    return password;
}
QString employe::getFonction()
{
    return fonction;
}
int employe::getSalaire()
{
    return salaire;
}
int employe::getPresence()
{
    return presence;
}
QString employe::getSerial_number()
{
    return serial_number;
}

void employe::setCIN (QString cin)
{
    this->cin=cin;
}
void employe::setNom (QString nom)
{
    this->nom=nom;
}
void employe::setPrenom (QString prenom)
{
    this->prenom=prenom;
}
void employe::setAge (int age)
{
    this->age=age;
}
void employe::setEmail (QString email)
{
    this->email=email;
}
void employe::setNum (QString num_tel)
{
    this->num_tel=num_tel;
}
void employe::setPassword (QString password)
{
    this->password=password;
}
void employe::setFonction (QString fonction)
{
    this->fonction=fonction;
}
void employe::setSalaire (int salaire)
{
    this->salaire=salaire;
}
void employe::setPresence (int presence)
{
    this->presence=presence;
}
void employe::setSerial_number (QString serial_number)
{
    this->serial_number=serial_number;
}

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,PASSWORD,FONCTION,SALAIRE,PRESENCE,SERIAL_NUMBER)"" VALUES(:cin, :nom, :prenom, :age, :email, :num_tel, :password,:fonction, :salaire, :presence, :serial_number)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":email",email);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":password",password);
    query.bindValue(":fonction",fonction);
    query.bindValue(":salaire",salaire);
    query.bindValue(":presence",presence);
    query.bindValue(":serial_number",serial_number);
    return query.exec();
}

QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));
    return model;

}
bool employe::supprimer(QString cin)
{
    QSqlQuery query;
    query.prepare("Delete from EMPLOYE where cin= :cin");
    query.bindValue(":cin",cin);
    return query.exec();
}

bool employe::modifier(QString cin)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:nom , PRENOM=:prenom , AGE = :age , EMAIL= :email, NUM_TEL= :num_tel, PASSWORD=:password, FONCTION= :fonction, SALAIRE=:salaire WHERE CIN=:cin");

    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":email",email);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":password",password);
    query.bindValue(":fonction",fonction);
    query.bindValue(":salaire",salaire);

    return query.exec();
}

bool employe:: string_test(QString ch)
{
    for (int i=0; i!=ch.length(); i++)
    {
        if (!((ch[i] >= 'A' && ch[i]<='Z') || (ch[i] >= 'a' && ch[i]<='z')))
            return false;
    }
    return true;
}

QSqlQueryModel *employe:: tri_cin_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by CIN ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_cin_desc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by CIN DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_nom_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by NOM ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_nom_desc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by NOM DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_age_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by AGE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_age_desc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by AGE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_salaire_asc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by SALAIRE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *employe:: tri_salaire_desc()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE order by SALAIRE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel* employe::recherche_avancee_employe(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QSqlQuery query;
    model->setQuery("SELECT CIN,NOM,PRENOM,AGE,EMAIL,NUM_TEL,FONCTION,SALAIRE,PRESENCE FROM EMPLOYE WHERE CIN LIKE'%"+ch+"%' or LOWER(NOM) LIKE LOWER('%"+ch+"%') or LOWER(PRENOM) LIKE LOWER('%"+ch+"%') or LOWER(FONCTION) LIKE LOWER('%"+ch+"%')");
    query.bindValue(":ch",ch);
    query.exec();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

bool employe::chercher_employe(QString email)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE EMAIL= :EMAIL");
    query.bindValue(":EMAIL", email);
    if (query.exec() && query.next())
        return true;
    else
        return false;
}

bool employe::chercher_password(QString pass)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE PASSWORD= :PASSWORD");
    query.bindValue(":PASSWORD", pass);
    if (query.exec() && query.next())
        return true;
    else
        return false;
}

bool employe::update(QString data)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET PRESENCE=:PRESENCE WHERE SERIAL_NUMBER LIKE :SERIAL_NUMBER");

    query.bindValue(":PRESENCE",1);
    query.bindValue(":SERIAL_NUMBER",data);

    return query.exec();
}
