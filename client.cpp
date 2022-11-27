#include "client.h"
#include "arduino.h"
#include <QSqlQuery>
#include <QDebug>
#include<QObject>
#include<QSqlQueryModel>
#include <QSqlRecord>



Client::Client()
{
   cin=0;
   tel=0;
   nom="";
   prenom="";
   email="";
   datedenaissance="";
   sexe="";
   //prixt=0;

}


Client::Client(int cin,int tel,QString nom,QString prenom,QString email,QString sexe,QString datedenaissance)
{this->cin=cin; this->tel=tel; this->nom=nom; this->prenom=prenom; this->email=email; this->sexe=sexe; this->datedenaissance=datedenaissance;}
int Client::getcin(){return cin;}
int Client::gettel(){return tel;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getemail(){return email;}
QString Client::getsexe(){return sexe;}
QString Client::getdate(){return datedenaissance;}
//QString Client::getmsg(){return msg;}

void Client::setcin(int cin){this->cin=cin;}
void Client::settel(int tel){this->tel=tel;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setemail(QString email){this->email=email;}
void Client::setsexe(QString sexe){this->sexe=sexe;}
void Client::setdate(QString datedenaissance){this->datedenaissance=datedenaissance;}

//void Client::setmsg(QString msg){this->msg=msg;}

bool Client::ajouter()
{
    QSqlQuery query;

    QString cin_string=QString::number(cin);
    QString tel_string=QString::number(tel);
          query.prepare("insert into client (cin, tel, nom, prenom, email, sexe,datedenaissance)" "VALUES (:cin, :tel, :nom, :prenom, :email, :sexe, :datedenaissance)");
          query.bindValue(":cin", cin_string);
          query.bindValue(":tel", tel_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":email", email);
          query.bindValue(":sexe", sexe);
          query.bindValue(":datedenaissance", datedenaissance);

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
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Sexe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date de naissance"));

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


/*bool  Client::rechercher(int cin)
{

        QSqlQuery query;
        QString cin_string=QString::number(cin);
        query.prepare("select * from client Where CIN=:cin");
        query.bindValue(":cin", cin_string);
        return query.exec();

}*/

bool Client::rechercher(int cin)
 {


       QSqlQuery query("SELECT * FROM client");
       QSqlQuery recherche("select * from client where  cin = "+QString::number(cin) );
        // query.prepare ("select * from client where cin="+QString::number(cin));
         QSqlRecord rec = recherche.record();

         qDebug() << "Number of columns: " << rec.count();

         int nameCol = rec.indexOf("cin"); // index of the field "name"
         while (recherche.next()){
             qDebug() << recherche.value(nameCol).toString();
             QString test= recherche.value(nameCol).toString();
         if (test!=""){query.exec("select from voyageur where cin="+QString::number(cin));

                 return true;
             }
             return false;


 }
     return query.exec();
}


QSqlQueryModel * Client::tri_nom(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT ORDER BY NOM ASC");

     return model;

 }
QSqlQueryModel * Client::tri_prenom(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT ORDER BY PRENOM ASC");

     return model;

 }


QSqlQueryModel * Client::tri_date(){

     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT ORDER BY DATEDENAISSANCE ASC");

     return model;

 }




bool Client::modifier(int cin){

   QSqlQuery query;

    query.prepare(" UPDATE CLIENT SET EMAIL= :email, TEL= :tel where CIN= :cin");
    query.bindValue(":cin", cin);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    return query.exec();

}

/*bool Client::envoyer(int cin, QByteArray tel)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString tel_string=QString::number(tel);
    tel=query.prepare("select tel from client Where CIN=:cin");
    query.bindValue(":cin", cin_string);
    query.bindValue(":tel", tel_string);
    return query.exec();
}*/
