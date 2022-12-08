#ifndef SPONSOR_H
#define SPONSOR_H
#include <QString>
#include<QtSql/QSqlQueryModel>


class sponsor
{
public :
    sponsor();
    sponsor(QString,QString,int,QString);
    int get_id();
    void Set_nom(QString) ;
    QString get_nom();
    void Set_type(QString) ;
    QString get_type();
    void Set_pays(QString) ;
    QString get_pays();
    void Set_duree(int ) ;
    float get_duree();

    bool ajouter();
    bool  modifier(int,QString,QString,int,QString);
    bool supprimer(int idd);
    QSqlQueryModel * afficher();//retourner un tableau dune requtte de type sql    un ensemble desinfs et le resultat de cet ensemble cest le resultat dune requette(query) de type sql
    ///////////////////////////
    QSqlQueryModel * trie_id();
    QSqlQueryModel * trie_nom();
    QSqlQueryModel * trie_duree();
    QSqlQueryModel * afficherh();

  private:
    int id;
    QString nom;
    QString type;
    QString pays;
    int duree;
};

#endif // SPONSOR_H
