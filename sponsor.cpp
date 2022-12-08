#include "sponsor.h"
#include <QString>
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QString>



using namespace std;


sponsor::sponsor()
{
   nom=" ";
   type=" ";
   duree=0;
   pays=" ";
}

sponsor::sponsor(QString nom,QString type,int duree,QString pays)
{

   this->nom=nom.toUpper();
   this->type=type.toUpper();
   this->duree=duree;
   this->pays=pays.toUpper();
}


int sponsor::get_id(){return id;}
void sponsor::Set_nom(QString val) { nom = val; }
QString sponsor::get_nom(){return nom;}
void sponsor::Set_type(QString val) { type = val; }
QString sponsor:: get_type(){return type;}
void sponsor::Set_pays(QString val) { pays = val; }
QString sponsor::get_pays(){return pays;}
void sponsor::Set_duree(int val) { duree = val; }
float sponsor::get_duree(){return duree;}


bool sponsor::ajouter()
{
    QSqlQuery query;  //variable d'accees lel BD
    query.prepare("INSERT INTO sponsor (NOM,TYPE,PAYS,DUREE)"
                          "VALUES (:nom, :type, :pays, :duree)");  //thez mel classe li fel QT lel BD
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":pays",pays);
    query.bindValue(":duree",duree);
    return query.exec();//exec fait retourner true or false
}


QSqlQueryModel *sponsor::afficher()
{//code detailed description aide
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM sponsor");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));//1ere colonne dans BD dindice 0
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PAYS"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DUREE"));
 return model;
}

QSqlQueryModel *sponsor::afficherh()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM historique");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("action"));//1ere colonne dans BD dindice 0
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("date"));
 return model;
}

bool sponsor::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from sponsor where id = :id ");
    query.bindValue(0,id);
    return query.exec();

}


bool sponsor :: modifier(   int id ,QString nom,QString type,int duree,QString pays)
{

        QSqlQuery qry;
        qry.prepare("UPDATE sponsor set NOM=(?),TYPE=(?),PAYS=(?),DUREE=(?) where id=(?) ");
        qry.addBindValue(nom);
        qry.addBindValue(type);
        qry.addBindValue(pays);
        qry.addBindValue(duree);
        qry.addBindValue(id);
        return  qry.exec();
}


QSqlQueryModel *sponsor::trie_id()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM sponsor order by id");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));//1ere colonne dans BD dindice 0
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PAYS"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DUREE"));
 return model;
}

QSqlQueryModel *sponsor::trie_nom()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM sponsor order by nom");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));//1ere colonne dans BD dindice 0
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PAYS"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DUREE"));
 return model;
}

QSqlQueryModel *sponsor::trie_duree()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM sponsor order by duree");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));//1ere colonne dans BD dindice 0
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PAYS"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("DUREE"));
 return model;
}
