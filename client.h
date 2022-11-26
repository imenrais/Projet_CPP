#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Client
{

private:
    int cin,tel;

    float prixt;
    QString nom,prenom,email,sexe,datedenaissance;
public:
Client();

Client(int,int,QString,QString,QString,QString,QString);

int getcin();
int gettel();
QString getnom();
QString getprenom();
QString getemail();
QString getsexe();
QString getdate();

//float getprix();


void setcin(int);
void settel(int);
void setnom(QString);
void setprenom(QString);
void setemail(QString);
void setsexe(QString);
void setdate(QString);

//void setprix(float);



bool ajouter();
QSqlQueryModel * afficher ();
bool supprimer(int);
bool modifier(int);
bool rechercher(int);
QSqlQueryModel * tri_nom();
QSqlQueryModel * tri_prenom();
QSqlQueryModel * tri_date();
//QSqlQueryModel * calculer ();
bool envoyer(int, int);
};

#endif // CLIENT_H
