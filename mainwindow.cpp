#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gestion_de_destination.h"
#include<QValidator>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QPdfWriter>
#include<QDesktopServices>
#include<QUrl>
#include<QPainter>
#include<QtPrintSupport/QAbstractPrintDialog>
#include<QPrinter>
#include<QTabWidget>
#include<QTableView>
#include<QGroupBox>
#include "statistique.h"
#include <QTextDocument>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);/*
   ui->le_num->setValidator(new QIntValidator(100, 999, this));
   ui->la_des->setValidator(new QRegExpValidator(QRegExp("[A-Z]*[a-z]")));
   ui->le_moy->setValidator(new QRegExpValidator(QRegExp("[A-Z]*[a-z]")));
   ui->la_duree->setValidator(new QRegExpValidator(QRegExp("[A-Z]*[a-z]")));
   //ui->le_nbvoy->setValidator(new QIntValidator(1000, 1800, this));
   //ui->le_nbticket->setValidator(new QIntValidator(1000, 1800, this));*/
   ui->tab_destination->setModel(G.afficher());
    ui->tab_destination->show();
   //this->setCentralWidget(vw);
//   ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
//   ui->quickWidget->show();
  //  ui->WebBrowser->dynamicCall("Navigate(const QString&)");

    int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
             //le slot update_label suite à la reception du signal readyRead (reception des données).


}
void MainWindow::update_label()
{
    QMessageBox msgBox;
 data="";

while((A.getdata().size()<5))
{
    QString key;
data=A.read_from_arduino();

break;

}
if(data.toInt()!=0)
{int D=data.toInt();
    if(A.chercherid(D)!=-1)
    {   msgBox.setText("valide");
        qDebug()<<"valdie";
        A.write_to_arduino("1");
         }
    else
    { A.write_to_arduino("0");
        msgBox.setText("invalide");
        qDebug()<<"invaldie"; ; }
qDebug()<<data;
msgBox.exec();

}
data="";
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{//recuperation des information saisie
    QString Destination=ui->la_des->text();
    int Numero=ui->le_num->text().toInt();
    QString MoyenDeTransport=ui->le_moy->text();
    int NombreDeTicket=ui->le_nbticket->text().toInt();
    int NombreDesVoyageurs=ui->le_nbvoy->text().toInt();
    int Prix=ui->le_prix->text().toInt();

    QString Duree=ui->la_duree->text();

    Gestion_de_destination G;
    G.setdestination(Destination);
    G.setnum(Numero);
    G.setmtransport(MoyenDeTransport);
    G.setnticket(NombreDeTicket);
    G.setnvoy(NombreDesVoyageurs);
    G.setprix(Prix);
    G.setduree(Duree);

    bool test=G.ajouter();
    if (test)
             {

        ui->tab_destination->setModel(G.afficher());
         QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("Ajout effectué.\n"
                                           "click cancel to exit."),QMessageBox::Cancel);

    }
      else
    { QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                            QObject::tr("Ajout non effectué.\n"
                                                "click cancel to exit."),QMessageBox::Cancel);

   }// Gestion_de_destination G(destination,numero,moyenDeTransport,nombreDeTicket,nombreDesVoyageurs,prix,duree);
}

void MainWindow::on_pb_supprimer_clicked()
{
   Gestion_de_destination G;
   G.setnum(ui->le_num_supp->text().toInt());
   bool test=G.supprimer(G.getnum());
   QMessageBox msgBox;
   if(test)
   {msgBox.setText("supprission avec succes");
   ui->tab_destination->setModel(G.afficher());
   }
   else
       msgBox.setText("echec de suppression");
       msgBox.exec();


}

/*void MainWindow::on_pb_modifier_clicked()
{
    Gestion_de_destination G;
    G.setnum(ui->le_num->text().toInt());
    G.setnticket(ui->le_nbticket->text().toInt());
    G.setnvoy(ui->le_nbvoy->text().toInt());
    bool test=G.modifier(ui->le_num->text());

    if (test)
              { ui->tab_destination->setModel(G.afficher());
          QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Modification effectué.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
       }
       else
          QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                             QObject::tr("Modification non effectué.\n"
                                                 "click cancel to exit."),QMessageBox::Cancel);
}*/

/*void MainWindow::on_tab_destination_activated(const QModelIndex &index)
{

}*/

/*int MainWindow::on_pb_pdf_clicked()
{
    QPrinter printer;
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName("monPremierPDF.pdf");
          QPainter painter;
          if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return 1;
          }
          painter.drawText(10, 10, "Mon premier PDF");
          painter.drawText(10, 30, "Test");
          if (! printer.newPage()) {
              qWarning("failed in flushing page to disk, disk full?");
              return 1;
          }
          painter.drawText(10, 10, "Test 2");
          painter.end();
}*/

/*void MainWindow::on_pb_recherche_clicked()
{

}*/



void MainWindow::on_actionOpen_triggered()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;
    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");
    on_actionStop_triggered();

    player->setVideoOutput(vw);

    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(1000,500,500,500); //kober l aff video
    vw->show();

    on_actionPlay_triggered();

}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui->statusBar->showMessage("Paused");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->statusBar->showMessage("Stopped");
}

void MainWindow::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    QString inputValue,filtrerChecked;
            inputValue=ui->lineEdit_2->text();
            ui->tab_destination->setModel(G.rechercherdynamique(inputValue,"DESTINATION"));
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="Numero")
    {

     ui->tab_destination->setModel(G.afficher_des_trie_num());
     ui->tab_destination->show();
    }
   else if (arg1=="Nombre de Ticket")
    {

     ui->tab_destination->setModel(G.afficher_des_trie_nbticket());
     ui->tab_destination->show();
    } else if (arg1=="Nombre de Voyageurs")
    {

     ui->tab_destination->setModel(G.afficher_des_trie_nbvo());
     ui->tab_destination->show();
    }

}

void MainWindow::on_pushButton_clicked()
{
    Statistique s;
    s.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    A.write_to_arduino("0");
}

void MainWindow::on_pb_pdf_2_clicked()
{
    QString strStream;
           QTextStream out(&strStream);
          const int rowCount = ui->tab_destination->model()->rowCount();
          const int columnCount =ui->tab_destination->model()->columnCount();


          out <<  "<html>\n"
              "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             <<  QString("<title>%1</title>\n").arg("destination")
             <<  "</head>\n"
                "<body bgcolor=grey link=#5000A0>\n"
                     "<h1>Liste des Destinations</h1>"

                "<table border=1 cellspacing=0 cellpadding=2>\n";

                           // headers
                               out << "<thead><tr bgcolor=#f0f0f0>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->tab_destination->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->tab_destination->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";
                               // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tab_destination->isColumnHidden(column)) {
                                              QString data = ui->tab_destination->model()->data(ui->tab_destination->model()->index(row, column)).toString().simplified();
                                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                          }
                                      }
                                      out << "</tr>\n";
                                  }
                                  out <<  "</table>\n"
                                      "</body>\n"
                                      "</html>\n";
                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);
                   //QTextDocument document;
                   //document.setHtml(html);
                   QPrinter printer(QPrinter::PrinterResolution);
                   printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setOutputFileName("destination.pdf");
                   document->print(&printer);
}

void MainWindow::on_pushButton_3_clicked()   //modifier
{
    Gestion_de_destination G;
    G.setdestination(ui->la_des->text());
    G.setnum(ui->le_num->text().toInt());
    G.setmtransport(ui->le_moy->text());
    G.setnticket(ui->le_nbticket->text().toInt());
    G.setnvoy(ui->le_nbvoy->text().toInt());
    G.setprix(ui->le_prix->text().toInt());
    G.setduree(ui->la_duree->text());
    bool test=G.modifier();

    if (test)
              { ui->tab_destination->setModel(G.afficher());
          QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Modification effectué.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
       }
       else
          QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                             QObject::tr("Modification non effectué.\n"
                                                 "click cancel to exit."),QMessageBox::Cancel);
}
