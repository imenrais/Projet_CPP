#include "connection.h"

Connection::Connection()
{

}

bool Connection::ouvrirconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("khalil");//inserer nom de l'utilisateur
db.setPassword("employe");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
