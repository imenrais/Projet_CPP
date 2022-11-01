#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QString>
#include<QSqlQueryModel>

class Etudiant
{
public:
    Etudiant();
    Etudiant(int,QString,QString,QString,QString,QString,int,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getrole();
    QString getdate();
    QString getemail();
     int getsalaire();
     QString getnumero();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setrole(QString);
    void setdate(QString);
    void setemail(QString);
    void setsalaire(int);
    void setnumero(QString);

    bool ajouter();
    bool test/*=false*/;
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);

private :
    int identifiant,salaire;
    QString nom,prenom,role,date_de_naissance,email,numero;
};

#endif // ETUDIANT_H
