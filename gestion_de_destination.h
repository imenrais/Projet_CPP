#ifndef GESTION_DE_DESTINATION_H
#define GESTION_DE_DESTINATION_H
#include<QString>
#include<QSqlQueryModel>

class Gestion_de_destination
{

private:
    QString des,mtransport,duree;
    int num,nticket,nvoy,prix;



public:
    Gestion_de_destination();
    Gestion_de_destination(QString,int,QString,int,int,int,QString);



    ~Gestion_de_destination();

    QString getdestination();
    int getnum();
    QString getmtransport();
    int getnticket();
    int getnvoy();
    int getprix();
    QString getduree();

    void setdestination(QString);
    void setnum(int);
    void setmtransport(QString);
    void setnticket(int);
    void setnvoy(int);
    void setprix(int);
    void setduree(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* rechercherdynamique(QString input, QString filtrer);
    QSqlQueryModel* afficher_des_trie_num();
    QSqlQueryModel* afficher_des_trie_nbticket();
    QSqlQueryModel* afficher_des_trie_nbvo();

};

#endif // GESTION_DE_DESTINATION_H
