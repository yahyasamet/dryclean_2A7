#include "connection.h"

Connection::Connection()
{

}

bool Connection::connect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2a");
db.setUserName("amira");//inserer nom de l'utilisateur
db.setPassword("esprit22");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
