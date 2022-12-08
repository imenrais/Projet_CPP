#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sponsor.h"
#include <QDebug>
#include "connection.h"
#include <QFileDialog>
#include<QSystemTrayIcon>
#include <QRegExp>
#include <QPainter>
#include <QDate>
#include <QTextDocument>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQueryModel>
//je peux utiliser le bib qintvalidator si je peux faire un cds
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(s.afficher());
    ui->tableView_2->setModel(s.afficherh());
    //input__control
       ui->lineEdit_4->setValidator(new QIntValidator(0,999999,this));
       ui->lineEdit->setValidator(new QIntValidator(0,999999,this));
       ui->lineEdit_10->setValidator(new QIntValidator(0,999999,this));
       ui->lineEdit_8->setValidator(new QIntValidator(0,999999,this));
       QRegExp rx("[a-zA-Z]+");

       QValidator *validator = new
               QRegExpValidator (rx,this);
       ui->lineEdit_2->setValidator(validator);
       ui->lineEdit_3->setValidator(validator);
       ui->lineEdit_5->setValidator(validator);
       ui->lineEdit_6->setValidator(validator);
       ui->lineEdit_9->setValidator(validator);
       ui->lineEdit_7->setValidator(validator);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString nom=ui->lineEdit_2->text();
    QString type=ui->lineEdit_3->text();
    QString pays=ui->lineEdit_5->text();
    int duree=ui->lineEdit_4->text().toInt();
    sponsor s(nom,type,duree,pays);
    bool test=s.ajouter();


    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("ajoute \n"
                                                 "click to cancel"), QMessageBox::Cancel);
            ui->lineEdit_4->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_5->clear();
            ui->tableView->setModel(s.afficher());
            //historique
            QSqlQuery query;  //variable d'accees lel BD
            query.prepare("INSERT INTO historique (action)"
                                  "VALUES (:action)");
            query.bindValue(":action","ajout");
            query.exec();//exec fait retourner true or false
            ui->tableView_2->setModel(s.afficherh());
            //historique
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);



}

void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->lineEdit->text().toInt();
    bool test=s.supprimer(id);


    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("supprimer \n"
                                                 "click to cancel"), QMessageBox::Cancel);
            ui->lineEdit->clear();
            QSqlQuery query;  //variable d'accees lel BD
            //historique
            query.prepare("INSERT INTO historique (action)"
                                  "VALUES (:action)");
            query.bindValue(":action","suppression");
            query.exec();//exec fait retourner true or false
            ui->tableView->setModel(s.afficher());
            ui->tableView_2->setModel(s.afficherh());
            //historique

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);



}

void MainWindow::on_pushButton_3_clicked()
{
    int id=ui->lineEdit_10->text().toInt();
    int duree=ui->lineEdit_8->text().toInt();
    QString nom=ui->lineEdit_6->text();
    QString type=ui->lineEdit_7->text();
    QString pays=ui->lineEdit_9->text();
    bool test=s.modifier(id,nom,type,duree,pays);

    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("modifier \n"
                                                 "click to cancel"), QMessageBox::Cancel);
            ui->lineEdit_10->clear();
            ui->lineEdit_8->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->lineEdit_9->clear();
            //historique
            QSqlQuery query;  //variable d'accees lel BD
            query.prepare("INSERT INTO historique (action)"
                                  "VALUES (:action)");
            query.bindValue(":action","modification");
            query.exec();//exec fait retourner true or false
            ui->tableView->setModel(s.afficher());
            ui->tableView_2->setModel(s.afficherh());
            //historique

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);


}
// trie id
void MainWindow::on_pushButton_6_clicked()
{
    ui->tableView->setModel(s.trie_id());
}
// trie nom
void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(s.trie_nom());
}
// trie duree
void MainWindow::on_pushButton_9_clicked()
{
     ui->tableView->setModel(s.trie_duree());
}

// pdf
void MainWindow::on_pushButton_7_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        qDebug()<<dir;
        QPdfWriter pdf(dir+"/PdfList.pdf");
                               QPainter painter(&pdf);
                              int i = 4000;

                                   painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/houss/Downloads/logo.jpg"));
                                   painter.drawText(900,650,"Travel Sense");
                                   painter.setPen(Qt::red);
                                   painter.setFont(QFont("Time New Roman", 25));
                                   painter.drawText(3000,1400,"Sponsor list");
                                   painter.setPen(Qt::black);
                                   painter.setFont(QFont("Time New Roman", 15));
                                   painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                   painter.drawRect(100,3000,9400,500);
                                   painter.setFont(QFont("Time New Roman", 9));
                                   painter.drawText(300,3300,"ID");
                                   painter.drawText(2000,3300,"Nom entreprise");
                                   painter.drawText(4000,3300,"Type");
                                   painter.drawText(5600,3300,"Duree");
                                   painter.drawText(7000,3300,"Pays");
                                   painter.drawRect(100,3000,9400,10700);
                                   QTextDocument previewDoc;
                                   //QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                   QTextCursor cursor(&previewDoc);
                                   QSqlQuery query;
                                   query.prepare("select * from sponsor");
                                   query.exec();
                                   while (query.next())
                                   {
                                       painter.drawText(300,i,query.value(0).toString());
                                       painter.drawText(2000,i,query.value(1).toString());
                                       painter.drawText(4000,i,query.value(2).toString());
                                       painter.drawText(5600,i,query.value(3).toString());
                                       painter.drawText(7000,i,query.value(4).toString());
                                      i = i +500;
                                   }
                                   int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                       QMessageBox::Yes|QMessageBox::No);
                                       if (reponse == QMessageBox::Yes)
                                       {
                                           QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                           painter.end();
                                       }
                                       else
                                       {
                                            painter.end();
    }
}
// recherche
void MainWindow::on_lineEdit_11_textChanged(const QString &arg1)
{
            QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT * FROM sponsor WHERE ID LIKE'"+arg1+"%' or NOM  LIKE'"+arg1+"%' or PAYS  LIKE'"+arg1+"%' or TYPE LIKE'"+arg1+"%'");
             query->exec();
             if (query->next()) {
             model->setQuery(*query);
             ui->tableView->setModel(model);
             }
             else {
                 QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                                 QObject::tr("NO MATCH FOUND !!\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
              ui->lineEdit_11->clear();}
}
// stat
void MainWindow::on_pushButton_5_clicked()
{
                                QSqlQueryModel * model= new QSqlQueryModel();
                                model->setQuery("select * from sponsor where duree >= 5 ");
                                float cat1=model->rowCount();
                                model->setQuery("select * from sponsor where duree < 5 ");
                                float cat2=model->rowCount();
                                float total=cat1+cat2;
                                QString a=QString("sponsor fidele "+QString::number((cat1*100)/total,'f',2)+"%" );
                                QString b=QString("sponsor normal "+QString::number((cat2*100)/total,'f',2)+"%" );

                                QPieSeries *series = new QPieSeries();
                                series->append(a,cat1);
                                series->append(b,cat2);


                        if (cat1!=0)
                        {QPieSlice *slice = series->slices().at(0);
                         slice->setLabelVisible();
                         slice->setPen(QPen());}
                        if (cat2!=0)
                        {
                                 // Add label, explode and define brush for 2nd slice
                                 QPieSlice *slice1 = series->slices().at(1);
                                 //slice1->setExploded();
                                 slice1->setLabelVisible();
                        }
                                // Create the chart widget
                                QChart *chart = new QChart();
                                // Add data to chart with title and hide legend
                                chart->addSeries(series);
                                chart->setTitle("Pourcentage sponsor : nombre total des sponsors : "+ QString::number(total));
                                //chart->legend()->hide();
                                // Used to display the chart
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                chartView->resize(1000,500);
                                chartView->show();

}
// calendrier
void MainWindow::on_pushButton_8_pressed()
{
    QCalendarWidget *calendar = new QCalendarWidget();//declaration
       QDate date = QDate::currentDate();
                calendar->setSelectedDate(date);
                QTextCharFormat format = calendar->weekdayTextFormat(Qt::Wednesday);
                     format.setForeground(QBrush(Qt::yellow, Qt::SolidPattern));
                     calendar->selectedDate();

        calendar->show();
}
// modification
void MainWindow::on_tableView_activated(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from sponsor  where ID='"+val+"' or NOM='"+val+"' or type ='"+val+"' or pays ='"+val+"' or duree='"+val+"'");

    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->lineEdit_10->setText(qry.value(0).toString());
            // nom
            ui->lineEdit_6->setText(qry.value(1).toString());
            //type
            ui->lineEdit_9->setText(qry.value(2).toString());
            //pays
            ui->lineEdit_7->setText(qry.value(3).toString());
            //duree
            ui->lineEdit_8->setText(qry.value(4).toString());
        }
    }
}


void MainWindow::on_calendarWidget_selectionChanged()
{
    QString rech=ui->calendarWidget->selectedDate().toString();
    ui->lineEdit_4->setText(ui->calendarWidget->selectedDate().toString());
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM sponsor where (duree like '%"+rech+"%')");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));//1ere colonne dans BD dindice 0
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("PAYS"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("DUREE"));
      ui->tableView->setModel(model);
   // qInfo()<<"Date: "<<rech<<endl;
}

