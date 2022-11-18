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
    QString nom,prenom,email,date_de_naissance,sexe;
public:
Client();

Client(int,int,QString,QString,QString);

int getcin();
int gettel();
QString getnom();
QString getprenom();
QString getemail();
float getprix();
QString getdate();
QString getsexe();

void setcin(int);
void settel(int);
void setnom(QString);
void setprenom(QString);
void setemail(QString);
void setdate(QString);
void setsexe(QString);
void setprix(float);


bool ajouter();
QSqlQueryModel * afficher ();
bool supprimer(int);
bool modifier(int);
bool rechercher(int);
QSqlQueryModel * tri_asc();
QSqlQueryModel * tri_desc();
QSqlQueryModel * calculer ();
};

#endif // CLIENT_H
