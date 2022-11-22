#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
class Etudiant
{
public:

    Etudiant();
        Etudiant(int,QString,QString,QString,QString,QString,int,QString);


        bool ajouter();
        bool modifier(int);
        QSqlQueryModel * afficher();
        bool supprimer(int);
        QSqlQueryModel * tri_id();
        QSqlQueryModel * tri_nom();
        QSqlQueryModel * tri_role();










          int identifiant,salaire;
          QString nom, prenom, role, date_de_naissance,email,numero;
};

#endif // EMPLOYE_H
