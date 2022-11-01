#include "etudiant.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>


Etudiant::Etudiant()
{
    identifiant=0;
    nom="";
    prenom="";
    role="";
    date_de_naissance="";
    email="";
    salaire=0;
    numero="";


}
Etudiant::Etudiant(int identifiant,QString nom,QString prenom,QString role,QString date,QString email,int salaire,QString numero){
    this->identifiant=identifiant;
        this->nom=nom;
        this->prenom=prenom;
        this->role=role;
        this->date_de_naissance=date;
        this->email=email;
        this->salaire=salaire;
        this->numero=numero;

}
int Etudiant:: getid(){
    return identifiant;
}
QString Etudiant:: getnom () {
    return nom;
}
QString  Etudiant::getprenom(){ return prenom;}
QString  Etudiant::getrole(){ return role;}
QString  Etudiant::getdate(){ return date_de_naissance;}
QString  Etudiant::getemail(){ return email;}
QString  Etudiant::getnumero(){ return numero;}

int Etudiant:: getsalaire(){
    return salaire;
}



void Etudiant:: setid(int identifiant){
       this->identifiant=identifiant;
}
void Etudiant:: setnom(QString nom){
     this->nom=nom;
}
void Etudiant:: setprenom(QString prenom){
     this->prenom=prenom;
}
void Etudiant:: setrole(QString role){
     this->role=role;
}
void Etudiant:: setdate(QString date_de_naissance){
     this->date_de_naissance=date_de_naissance;
}
void Etudiant:: setemail(QString email){
     this->email=email;
}

void Etudiant:: setsalaire(int salaire){
       this->salaire=salaire;
}

void Etudiant:: setnumero(QString numero){
     this->numero=numero;
}


bool Etudiant :: ajouter(){

    QSqlQuery query;
    QString id_string=QString::number(identifiant);
    QString salaire_string=QString::number(salaire);
    query.prepare("INSERT INTO EMPLOYE (IDENTIFIANT, NOM, PRENOM,ROLE,DATE_DE_NAISSANCE,EMAIL,SALAIRE,NUMERO) "
                  "VALUES (:identifiant, :forename, :surname, :role, :date_de_naissance, :email, :salaire, :numero) ");
     query.bindValue(":identifiant", id_string);
     query.bindValue(":forename", nom);
     query.bindValue(":surname", prenom);
     query.bindValue(":role", role);
     query.bindValue(":date_de_naissance", date_de_naissance);
     query.bindValue(":email", email);
     query.bindValue(":salaire", salaire_string);
     query.bindValue(":numero", numero);
   return query.exec();


    //return test;
}
bool Etudiant ::supprimer(int identifiant){

    QSqlQuery query;

    query.prepare("Delete from employe where IDENTIFIANT =:identifiant  ");
    query.bindValue(0, identifiant);

   return query.exec();





}
   QSqlQueryModel* Etudiant :: afficher(){



    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("select  * from employe ");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject:: tr("role"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("date_de_naissance"));
    model->setHeaderData(5, Qt::Horizontal,QObject:: tr("email"));
    model->setHeaderData(6, Qt::Horizontal,QObject:: tr("salaire"));
    model->setHeaderData(7, Qt::Horizontal,QObject:: tr("numero"));


    return model;
}



   bool Etudiant :: modifier(int identifiant){

       QSqlQuery query;


       query.prepare("UPDATE employe set  nom=:forename,prenom=:surname,role=:role,email=:email,salaire=:salaire,numero=:numero where identifiant=:identifiant");

        query.bindValue(":identifiant", identifiant);
        query.bindValue(":forename", nom);
        query.bindValue(":surname", prenom);
        query.bindValue(":role", role);
        query.bindValue(":date_de_naissance", date_de_naissance);
        query.bindValue(":email", email);
        query.bindValue(":salaire",salaire);
        query.bindValue(":numero", numero);
      return query.exec();


       //return test;
   }


