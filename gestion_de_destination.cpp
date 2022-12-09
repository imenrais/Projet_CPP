#include "gestion_de_destination.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
Gestion_de_destination::Gestion_de_destination()
{
des="";
num=0;
mtransport="";
nticket=0;
nvoy=0;
prix=0;
duree="";
}


Gestion_de_destination::Gestion_de_destination(QString des,int num,QString mtransport,int nticket,int nvoy,int prix,QString duree)
{
    this ->des=des;
    this->num=num;
    this->mtransport=mtransport;
    this->nticket=nticket;
    this->nvoy=nvoy;
    this->prix=prix;
    this->duree=duree;
}

Gestion_de_destination::~Gestion_de_destination(){} //


QString Gestion_de_destination:: getdestination()
{return des;}

int Gestion_de_destination:: getnum()
{return num;}

QString Gestion_de_destination:: getmtransport()
{return mtransport;}

int Gestion_de_destination:: getnticket()
{return nticket;}

int Gestion_de_destination:: getnvoy()
{return nvoy;}

int Gestion_de_destination:: getprix()
{return prix;}

QString Gestion_de_destination:: getduree()
{return duree;}




void Gestion_de_destination:: setdestination(QString des)
{this ->des=des;}

void Gestion_de_destination:: setnum(int num)
{this->num=num;}

void Gestion_de_destination:: setmtransport(QString mtransport)
{this->mtransport=mtransport;}

void Gestion_de_destination:: setnticket(int nticket)
{this->nticket=nticket;}

void Gestion_de_destination:: setnvoy(int nvoy)
{this->nvoy=nvoy;};

void Gestion_de_destination:: setprix(int prix)
{this->prix=prix;}

void Gestion_de_destination:: setduree(QString duree)
{this->duree=duree;}

bool Gestion_de_destination::ajouter()
{
QSqlQuery query;

    QString num_string=QString::number(num);
    QString nticket_string=QString::number(nticket);
    QString nvoy_string=QString::number(nvoy);
    QString prix_string=QString::number(prix);
         query.prepare("INSERT INTO GDESTINATION (DESTINATION,NUMERO,MOYEN_DE_TRANSPORT,NOMBRE_DE_TICKET,NOMBRE_DES_VOYAGEURS,PRIX,DUREE) "
                       "VALUES (:DESTINATION,:NUMERO,:MOYEN_DE_TRANSPORT,:NOMBRE_DE_TICKET,:NOMBRE_DES_VOYAGEURS,:PRIX,:DUREE)");

         query.bindValue(":DESTINATION", des);
         query.bindValue(":NUMERO", num_string);
         query.bindValue(":MOYEN_DE_TRANSPORT", mtransport);
         query.bindValue(":NOMBRE_DE_TICKET",nticket_string);
         query.bindValue(":NOMBRE_DES_VOYAGEURS",nvoy_string);
         query.bindValue(":PRIX",prix);
         query.bindValue(":DUREE",duree);
         return   query.exec();



}

QSqlQueryModel* Gestion_de_destination::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT * FROM GDESTINATION");
              model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Destination"));
              model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Numero"));
              model->setHeaderData(2, Qt::Horizontal, QObject:: tr("MoyDeTransport"));
              model->setHeaderData(3, Qt::Horizontal, QObject:: tr("NbTicket"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("NbVoyageurs"));
              model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prix"));
              model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Durée"));
        return model;
}

bool Gestion_de_destination::supprimer(int num)
{
    QSqlQuery query;
        query.prepare("Delete from GDESTINATION where NUMERO= :num ;");
        query.bindValue(0, num);

    return query.exec() ;
}

bool Gestion_de_destination::modifier(){
 QSqlQuery query;
      query.prepare("UPDATE GDESTINATION SET DESTINATION= :des, NUMERO= :num , MOYEN_DE_TRANSPORT= :mtransport ,NOMBRE_DE_TICKET= :nticket,NOMBRE_DES_VOYAGEURS= :nvoy,PRIX= :prix,DUREE= :duree WHERE NUMERO= :num; ");
      query.bindValue(":des", des);
      query.bindValue(":num", num);
      query.bindValue(":mtransport", mtransport);
      query.bindValue(":nticket",nticket);
      query.bindValue(":nvoy",nvoy);
      query.bindValue(":prix",prix);
      query.bindValue(":duree",duree);
return query.exec();


}

QSqlQueryModel* Gestion_de_destination::rechercherdynamique(QString input, QString filtrer) // filtre ala chnowa bich taamil recherche :destination
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    QString val= QString::number(0);

    query.prepare("SELECT * FROM GDESTINATION WHERE "+filtrer+" LIKE '%' || :inputValue || '%'");
    query.bindValue(":inputValue",input);
    query.bindValue(":val",val);

    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Destination"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Numero"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("MoyDeTransport"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("NbTicket"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("NbVoyageurs"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prix"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Durée"));
    return model;
}
QSqlQueryModel* Gestion_de_destination::afficher_des_trie_num() //selon numero
{
    QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT * FROM GDESTINATION order by numero");
              model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Destination"));
              model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Numero"));
              model->setHeaderData(2, Qt::Horizontal, QObject:: tr("MoyDeTransport"));
              model->setHeaderData(3, Qt::Horizontal, QObject:: tr("NbTicket"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("NbVoyageurs"));
              model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prix"));
              model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Durée"));
        return model;
}

QSqlQueryModel* Gestion_de_destination::afficher_des_trie_nbticket()            //selon nombre des ticket
{
    QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT * FROM GDESTINATION order by NOMBRE_DE_TICKET");
              model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Destination"));
              model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Numero"));
              model->setHeaderData(2, Qt::Horizontal, QObject:: tr("MoyDeTransport"));
              model->setHeaderData(3, Qt::Horizontal, QObject:: tr("NbTicket"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("NbVoyageurs"));
              model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prix"));
              model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Durée"));
        return model;
}
QSqlQueryModel* Gestion_de_destination::afficher_des_trie_nbvo()          //selon nombre des voys
{
    QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT * FROM GDESTINATION order by NOMBRE_DES_VOYAGEURS");
              model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Destination"));
              model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Numero"));
              model->setHeaderData(2, Qt::Horizontal, QObject:: tr("MoyDeTransport"));
              model->setHeaderData(3, Qt::Horizontal, QObject:: tr("NbTicket"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("NbVoyageurs"));
              model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prix"));
              model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Durée"));
        return model;
}
