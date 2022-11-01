#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "etudiant.h"
#include <QMessageBox>
#include<QIntValidator>
#include<QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->le_id->setValidator( new QIntValidator(100, 9999999, this));
ui->tab_etudiant->setModel(E1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int identifiant =ui->le_id->text().toInt();
       QString nom =ui->le_nom->text();
       QString prenom =ui->le_prenom->text();
       QString role =ui->le_role->text();
       QString date_de_naissance =ui->dateEdit->text();
       QString email =ui->le_email->text();
    int salaire =ui->le_salaire->text().toInt();
       QString numero =ui->le_numero->text();

Etudiant E(identifiant ,nom,prenom,role,date_de_naissance,email,salaire,numero);
bool test=E.ajouter();
ui->tab_etudiant->setModel(E1.afficher());
if(test)


    QMessageBox::information(nullptr, QObject::tr("SUCCESS"),
                QObject::tr("ajout successful.\n"
                            "ajout effectuer."), QMessageBox::Cancel);


else

    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("connection failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);




}


void MainWindow::on_pb_supp_clicked()
{
Etudiant E1;
E1.setid(ui->le_idsupp->text().toInt());
bool test=E1.supprimer(E1.getid());
if(test){


    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("suppresion successful.\n"
                            "suppresion effectuer."), QMessageBox::Cancel);
ui->tab_etudiant->setModel(E1.afficher());
}
else

    QMessageBox::critical(nullptr, QObject::tr("nope"),
                QObject::tr("suppresion failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_pushButton_clicked()
{
    ui->tab_etudiant->setModel(E1.afficher());
}


void MainWindow::on_pb_modifier_clicked()
{  Etudiant E1;
    int identifiant =ui->le_id->text().toInt();
       QString nom =ui->le_nom->text();
       QString prenom =ui->le_prenom->text();
       QString role =ui->le_role->text();
       QString date_de_naissance =ui->dateEdit->text();
       QString email =ui->le_email->text();
    int salaire =ui->le_salaire->text().toInt();
       QString numero =ui->le_numero->text();

Etudiant E(identifiant ,nom,prenom,role,date_de_naissance,email,salaire,numero);
bool test=E.modifier(identifiant);
ui->tab_etudiant->setModel(E1.afficher());
if(test)

  {
    QMessageBox::information(nullptr, QObject::tr("SUCCESS"),
                QObject::tr("update successful.\n"
                            "modifaction effectuer."), QMessageBox::Cancel);


}
else

    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("connection failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

