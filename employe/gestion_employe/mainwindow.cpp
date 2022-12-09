#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include"ui_login.h"
#include<QIntValidator>
#include<QSqlQueryModel>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QSqlRecord>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include<QMovie>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    show_tables();
mCamera = new QCamera(this);
mCameraViewfinder= new QCameraViewfinder(this);
mCameraImageCapture= new QCameraImageCapture(mCamera, this);
mLayout= new QVBoxLayout;
mOptionsMenu= new QMenu("Options",this);
mAllumerAction= new QAction("Allumer",this);
mEtiendreAction= new QAction("Etiendre",this);
mCaptureAction= new QAction("Capture",this);
mOptionsMenu->addActions({mAllumerAction,mEtiendreAction,mCaptureAction});
ui->options->setMenu(mOptionsMenu);
mCamera->setViewfinder(mCameraViewfinder);
mLayout->addWidget( mCameraViewfinder);
mLayout->setMargin(0);
ui->scrollArea->setLayout(mLayout);
connect (mAllumerAction, &QAction::triggered,[&]()
{mCamera->start(); });

connect (mEtiendreAction, &QAction::triggered,[&]()
{mCamera->stop(); });

connect (mCaptureAction, &QAction::triggered,[&]()
{ auto filename = QFileDialog::getSaveFileName(this, "Capture" ,"/" , "Image (*,jpg; *.jpeg)");
    if(filename.isEmpty()){return;}
    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();


});





}

MainWindow::~MainWindow()
{
    delete ui;
    show_tables();
}



void MainWindow::on_allumer_clicked()
{

}


void MainWindow::on_etindre_clicked()
{

}






bool MainWindow::fill_form(int selected ) {
    QSqlQuery fetcher;
        fetcher.prepare("SELECT * FROM employe WHERE identifiant = (:sel) ");
        fetcher.bindValue(":sel", selected);
        fetcher.exec();

        int ide = fetcher.record().indexOf("identifiant");
        int nome = fetcher.record().indexOf("nom");
        int prenome = fetcher.record().indexOf("prenom");
        int rolee = fetcher.record().indexOf("role");
        int salairee= fetcher.record().indexOf("salaire");
        int emaile= fetcher.record().indexOf("email");
        int numeroe=fetcher.record().indexOf("numero");

        while (fetcher.next())
        {
            ui->le_id->setText(fetcher.value(ide).toString());
            ui->le_nom->setText(fetcher.value(nome).toString());
            ui->le_prenom->setText(fetcher.value(prenome).toString());
            ui->le_salaire->setText(fetcher.value(salairee).toString());
            ui->le_email->setText(fetcher.value(emaile).toString());
            ui->le_numero->setText(fetcher.value(numeroe).toString());
            ui->le_role->setText(fetcher.value(rolee).toString());


    }
 return    fetcher.exec();
}






















void MainWindow::on_pb_ajouter_clicked()
{
bool test;
    //recuperation des donnees
       int identifiant =ui->le_id->text().toInt();
       QString nom =ui->le_nom->text();
       QString prenom =ui->le_prenom->text();
       QString role =ui->le_role->text();
       QString date_de_naissance =ui->dateEdit->text();
       QString email =ui->le_email->text();
       int salaire =ui->le_salaire->text().toInt();
       QString numero =ui->le_numero->text();

Etudiant E(identifiant ,nom,prenom,role,date_de_naissance,email,salaire,numero);
if((identifiant!=0)&&(nom!="")&&(prenom!="")&&(role!=""))
{ test=E.ajouter();}

        //refresh du tableau (affichage)
         show_tables();


         if(test)


          ui->label_2->setText("ajout effectuer");

         else

              ui->label_2->setText("ajout echouer: le identifiant n'est pas unique.");


}

void MainWindow::show_tables(){
//creation model (masque du tableau) : permet recherche et tri
    proxy = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy->setSourceModel(E.afficher());

 //pour la recherche
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tab->setModel(proxy);

}
void MainWindow::on_tab_clicked(const QModelIndex &index)
{
    selected=ui->tab->model()->data(index).toInt();
     ui->label_2->setText("identifiant selecter");
}





void MainWindow::on_tab_doubleClicked(const QModelIndex &index)
{
    /*MainWindow ac(this);





 bool tes=ac.fill_form(selected);
 if(tes)


     QMessageBox::information(nullptr, QObject::tr("SUCCESS"),
                 QObject::tr("recuperation successful.\n"
                             "recuperation effectuer."), QMessageBox::Cancel);


 else

     QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                 QObject::tr("recuperation failed.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);*/








}


void MainWindow::on_rech_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}


void MainWindow::on_pb_del_clicked()
{
    Etudiant mc;
   bool test=  mc.supprimer(selected);

    //refresh du tableau (affichage)
      show_tables();

      if((test)&&(selected!=0))


      { ui->label_2->setText("supprimission effectuer");}


      else if(selected==0)

        {   ui->label_2->setText("supprimission echouer");}
}


void MainWindow::on_pb_modifier_clicked()
{

    int identifiant =ui->le_id->text().toInt();
    QString nom =ui->le_nom->text();
    QString prenom =ui->le_prenom->text();
    QString role =ui->le_role->text();
    QString date_de_naissance =ui->dateEdit->text();
    QString email =ui->le_email->text();
    int salaire =ui->le_salaire->text().toInt();
    QString numero =ui->le_numero->text();

           //mofication
         Etudiant E(identifiant ,nom,prenom,role,date_de_naissance,email,salaire,numero);
         bool test=  E.modifier(selected);



         //refresh du tableau (affichage)
          show_tables();


          if(test)


               ui->label_2->setText("modification effectuer");


          else

               ui->label_2->setText("modification echouer");



}




void MainWindow::on_affiche_clicked()
{
    show_tables();
}





void MainWindow::on_comboBox_activated(int index)
{
    Etudiant E;

    if(index==0)
    ui->tab->setModel(E.tri_id());
    if(index==1)
    ui->tab->setModel(E.tri_nom());
    if(index==2)
    ui->tab->setModel(E.tri_role());
}


void MainWindow::on_pushButton_clicked()
{
    QString strStream;
        QTextStream out(&strStream);
       const int rowCount = ui->tab->model()->rowCount();
       const int columnCount =ui->tab->model()->columnCount();


       out <<  "<html>\n"
           "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("employe")
          <<  "</head>\n"
             "<body bgcolor=grey link=#5000A0>\n"
                  "<h1>Liste des Employe</h1>"

             "<table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                            out << "<thead><tr bgcolor=#f0f0f0>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tab->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tab->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";
                            // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->tab->isColumnHidden(column)) {
                                           QString data = ui->tab->model()->data(ui->tab->model()->index(row, column)).toString().simplified();
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
                printer.setOutputFileName("C:/Users/user/Desktop/employe.pdf");
                document->print(&printer);
}










void MainWindow::choix_pie()
{

    QSqlQueryModel * model= new QSqlQueryModel();

           model->setQuery("select * from EMPLOYE where SALAIRE < 1000 ");
           float salaire=model->rowCount();
           model->setQuery("select * from EMPLOYE where SALAIRE  between 1000 and 2000 ");
           float salaire1=model->rowCount();
           model->setQuery("select * from EMPLOYE where SALAIRE>2000 ");
           float salaire2=model->rowCount();
           float total=salaire+salaire1+salaire2;
           QString a = QString("moins de 1000 DT  "+QString::number((salaire*100)/total,'f',2)+"%" );
           QString b = QString("entre 1000 et 2000 DT "+QString::number((salaire1*100)/total,'f',2)+"%" );
           QString c = QString("+2000 DT "+QString::number((salaire2*100)/total,'f',2)+"%" );
           QPieSeries *series = new QPieSeries();
           series->append(a,salaire);
           series->append(b,salaire1);
           series->append(c,salaire2);
           if (salaire!= 0)
           {
               QPieSlice *slice = series->slices().at(0);
               slice->setLabelVisible();
               slice->setPen(QPen());
           }
           if ( salaire1!=0)
           {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(1);
                    //slice1->setExploded();
                    slice1->setLabelVisible();
           }
           if(salaire2!=0)
           {
                    // Add labels to rest of slices
                    QPieSlice *slice2 = series->slices().at(2);
                    //slice1->setExploded();
                    slice2->setLabelVisible();
           }
                   // Create the chart widget
                   QChart *chart = new QChart();
                   // Add data to chart with title and hide legend
                   chart->addSeries(series);
                   chart->setTitle("Pourcentage Par SALAIRE :Nombre Des EMPLOYEES "+ QString::number(total));
                   chart->legend()->hide();
                   // Used to display the chart
                   QChartView *chartView = new QChartView(chart);
                   chartView->setRenderHint(QPainter::Antialiasing);
                   chart->setAnimationOptions(QChart::SeriesAnimations);
                   chartView->resize(1000,500);
                   chartView->show();
   }


void MainWindow::on_pb_statistic_clicked()
{
    MainWindow s;
    s.choix_pie();
    s.show();
}


void MainWindow::on_formulaire_clicked()
{
    fill_form(selected);

}






void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_camera_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_return_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::iniciar(void)
{
    QMovie * movie = nullptr ;
    movie->setFileName(":/user.png");
    ui->mlabel->setMovie(movie);

    movie->start();
}
