#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include<QObject>
#include<QSqlQueryModel>
#include "statistique.h"


Client::Client()
{
   cin=0;
   nom="";
   prenom="";
   date_de_naissance="";
   email="";
   tel=0;
   sexe="";
   prixt=0;
}


Client::Client(int cin,int tel,QString nom,QString prenom,QString email)
{this->cin=cin; this->tel=tel; this->nom=nom; this->prenom=prenom; this->email=email;}
int Client::getcin(){return cin;}
int Client::gettel(){return tel;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getemail(){return email;}
void Client::setcin(int cin){this->cin=cin;}
void Client::settel(int tel){this->tel=tel;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setemail(QString email){this->email=email;}


bool Client::ajouter()
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString tel_string=QString::number(tel);
          query.prepare("insert into client (cin, tel, nom, prenom, email)" "VALUES (:cin, :tel, :nom, :prenom, :email)");
          query.bindValue(":cin", cin_string);
          query.bindValue(":tel", tel_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":email", email);
          return query.exec();
}

QSqlQueryModel * Client::afficher ()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Tel"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
          return model;
}



bool Client::supprimer(int cin)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
          query.prepare("Delete from client Where CIN=:cin");
          query.bindValue(":cin", cin_string);
          return query.exec();
}


bool  Client::rechercher(int cin)
{

        QSqlQuery query;
        QString cin_string=QString::number(cin);
        query.prepare("select * from client Where CIN=:cin");
        query.bindValue(":cin", cin_string);
        return query.exec();

}

QSqlQueryModel * Client::tri_asc(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT ORDER BY CIN ASC");

     return model;

 }

QSqlQueryModel * Client::tri_desc(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT ORDER BY CIN DESC");

     return model;

 }




bool Client::modifier(int cin){

   QSqlQuery query;

    query.prepare(" UPDATE CLIENT SET EMAIL= :email, TEL= :tel where CIN= :cin");
    query.bindValue(":cin", cin);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    return    query.exec();

}


