#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include"mainwindow.h"

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









bool Etudiant::ajouter(){

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

    return    query.exec();

}




bool Etudiant::modifier(int selected){

   QSqlQuery query;




    query.prepare(" UPDATE EMPLOYE SET NOM= :nom , PRENOM= :prenom , ROLE= :role, DATE_DE_NAISSANCE= :date_de_naissance ,EMAIL= :email ,SALAIRE= :salaire ,NUMERO= :numero where IDENTIFIANT= :sel");
    query.bindValue(":sel", selected);
    query.bindValue(":nom",nom); //remplir la valeur d'une maniere securisée
    query.bindValue(":prenom", prenom);
    query.bindValue(":role", role);
    query.bindValue(":date_de_naissance", date_de_naissance);
    query.bindValue(":email", email);
    query.bindValue(":salaire", salaire);
    query.bindValue(":numero", numero);

    return    query.exec();

}


QSqlQueryModel * Etudiant::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM EMPLOYE");

     return modal;

 }



bool Etudiant::supprimer(int selected){

      QSqlQuery query;
      query.prepare("Delete from EMPLOYE where IDENTIFIANT = :sel ");
      query.bindValue(":sel", selected);
      return    query.exec();


  }




QSqlQueryModel * Etudiant::tri_id(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM EMPLOYE ORDER BY IDENTIFIANT ASC");

     return model;

 }


QSqlQueryModel * Etudiant::tri_nom(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM EMPLOYE ORDER BY NOM ASC");

     return model;

 }


QSqlQueryModel * Etudiant::tri_role(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM EMPLOYE ORDER BY ROLE ASC");

     return model;

 }
