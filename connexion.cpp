#include "connexion.h"

Connexion::Connexion()
{

bool Connexion::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_SBTA");
db.setUserName("imen");//inserer nom de l'utilisateur
db.setPassword("imen");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connexion::closeconnection(){db.close();}

}
