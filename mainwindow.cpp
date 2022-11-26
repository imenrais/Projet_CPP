#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statistique.h"
#include "client.h"
#include "arduino.h"
#include <QDebug>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QIntValidator>
#include<QSqlQueryModel>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QSqlRecord>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QSqlQuery>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QApplication>
#include <QSerialPortInfo>
#include <QSerialPort>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->tableView->setModel(Ctmp.afficher());

   //Set up empty display panel
   ui->displayPanel->clear();

   //Set operator and store number flags to false
   operatorClicked = false;
   hasStoredNumber = false;

   //Set number button group listener
   ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                            this, SLOT(numberGroup_clicked(QAbstractButton*)));
   //Set operator button group listener
   ui->actionGroup->connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                            this, SLOT(actionGroup_clicked(QAbstractButton*)));
   int ret=A.connect_arduino();
   switch(ret)
   {
       case(0):qDebug()<<"arduino is available and connected to:"<<A.getarduino_port_name();
       break;
       case(1):qDebug()<<"arduino is available but not connected to:"<<A.getarduino_port_name();
       break;
       case(-1):qDebug()<<"arduino is not available";
       break;
   }
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    bool test=false;
    bool halt = false;
    int cin=ui->le_cin->text().toInt();
    int tel=ui->le_tel->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    QString sexe;
    QString datedenaissance=ui->datedenaissance->text();

   if(ui->radioButton1->isChecked())
    {

         sexe="femme";
    }

    else if (ui->radioButton2->isChecked())
    {

        sexe="homme";
    }
Client C(cin,tel,nom,prenom,email,sexe,datedenaissance);

        if(ui->le_cin->text() == "")
        {
            ui->le_cin->setPlaceholderText("cin est vide!");
            halt = true;
        }

        if(ui->le_tel->text() == "")
        {
            ui->le_tel->setPlaceholderText("le numéro de téléphone est vide!");
            halt = true;
        }

        if(ui->le_nom->text() == "")
        {
            ui->le_nom->setPlaceholderText("le nom est vide!");
            halt = true;
        }

        if(ui->le_prenom->text() == "")
        {
            ui->le_prenom->setPlaceholderText("le prenom est vide!");
            halt = true;
        }

        if(ui->le_email->text() == "")
        {
            ui->le_email->setPlaceholderText("l'email est vide!");
            halt = true;
        }

    if((cin!=0)&&(nom!="")&&(prenom!="")&&(tel!=0)&&(datedenaissance!="")&&(sexe!=""))
    { test=C.ajouter();}
        //Refresh
        ui->tableView->setModel(Ctmp.afficher());
        if(test)
        {


        QMessageBox::information(nullptr, QObject::tr("SUCCESS"),
                    QObject::tr("Client(e) ajouté(e)\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

       }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Client(e) non ajouté(e)\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_clicked()
{
    int cin=ui->le_cin2->text().toInt();
    bool test=Ctmp.supprimer(cin);
    if(test)
    {
        //Refresh
        ui->tableView->setModel(Ctmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer"),
                    QObject::tr("Client(e) supprimé(e)\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("Client(e)non supprimé(e)\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_afficher_clicked()
{
    ui->tableView->setModel(Ctmp.afficher());
}



void MainWindow::on_pb_rechercher_clicked()
{
    int cin=ui->le_cin2->text().toInt();
    bool test=Ctmp.rechercher(cin);
    ui->tableView->setModel(Ctmp.afficher());
        if(test)
           {
            QMessageBox::information(nullptr,QObject::tr("searching"),
                                    QObject::tr("search successful.\n"
                                                "click Cancel to exit."),QMessageBox::Cancel );
}
        else
            QMessageBox::critical(nullptr,QObject::tr("seraching"),
                                    QObject::tr("search failed.\n"
                                                "click Cancel to exit."),QMessageBox::Cancel );
}





void MainWindow::on_pb_modifier_clicked()
{
    int cin =ui->le_cin2->text().toInt();
    QString nom =ui->le_nom->text();
    QString prenom =ui->le_prenom->text();
    int tel=ui->le_tel->text().toInt();
    QString email =ui->le_email->text();

    QString sexe;
     QString datedenaissance =ui->datedenaissance->text();


         Client C(cin,tel,nom,prenom,email,sexe,datedenaissance);
         bool test= C.modifier(cin);
    //refresh du tableau (affichage)
          ui->tableView->setModel(Ctmp.afficher());


         if(test)

              QMessageBox::information(nullptr, QObject::tr("SUCCESS"),
                          QObject::tr("update successful.\n"
                                      "modification effectuer."), QMessageBox::Cancel);


          else

              QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                          QObject::tr("update failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

}


/*void MainWindow::on_pb_envoyer_clicked()
{

    QByteArray msg ="";


    //QString tel="";
    //int cin=ui->le_cin4->text().toInt();
    //QString tel=ui->le_tel->text();
    msg += ui->le_msg->toPlainText();



    A.write_to_arduino(msg);
    //A.write_to_arduino(tel);
    qDebug()<< msg ;

    //QByteArray msg =QByteArrayLiteral("\x12\x00\xa4\x42\x51\x00\x00\x99") ;
    ui->le_msg->clear();


}*/



void MainWindow::on_pb_pdf_clicked()
{
    const QString format("<td>%1</td>");
                QString html;
                QAbstractItemModel *md = ui->tableView->model();
                html = "<html><body><table border=\"0\">";

                html += "<td></td>";
                for(int column = 0; column < md->columnCount();
                    column++) {
                    QString data = md->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
                    html += format.arg(data);
                }
                for(int row = 0; row < md->rowCount() ; row++) {
                    html += "<tr>";
                    QString data = md->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
                    html += format.arg(data);
                    for(int column = 0; column < md->columnCount();
                        column++) {
                        QString data = md->index(row, column).data(Qt::DisplayRole).toString();
                        html += format.arg(data);
                    }
                    html += "</tr>";
                }
                html += "</table></body></html>";

                QPrinter printer;
                QPrintDialog *dialog = new QPrintDialog(&printer,this);
                if(dialog->exec() == QDialog::Accepted) {
                    QTextDocument document;
                    document.setHtml(html);
                    document.print(&printer);
                }

}

void MainWindow::on_tri_nom_clicked()
{
 Client C;
    ui->tableView->setModel(C.tri_nom());
}


void MainWindow::on_tri_prenom_clicked()
{
    Client C;
       ui->tableView->setModel(C.tri_prenom());
}

void MainWindow::on_tri_date_clicked()
{
    Client C;
       ui->tableView->setModel(C.tri_date());
}

void MainWindow::on_le_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from CLIENT where sexe like '%femme' ");
                            float s=model->rowCount();
                            model->setQuery("select * from CLIENT where sexe like '%homme'  ");
                            float s1=model->rowCount();
                            float total=s+s1;
                            QString a = QString("femmes "+QString::number((s*100)/total,'f',2)+"%" );
                            QString b=QString("hommes "+QString::number((s1*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,s);
                            series->append(b,s1);
                            //series->append(c,eee);
                    if (s!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( s1!=0)
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
                            chart->setTitle("nombre total des femmes et des hommes : "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();
}




 // Called whenever a number button is clicked
 void MainWindow::numberGroup_clicked(QAbstractButton* button)
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();

     /* Check if the previous button that was clicked was an operator button.
      * If so, clear the display and set the flag to false. Then proceed to
      * add the digit requested. */
     if (operatorClicked) {
         displayLabel.clear();
         operatorClicked = false;
     }

     //Append the digit only if we are not exceeding the digit limit
     if (displayLabel.length() >= DIGIT_LIMIT) {
         return;
     }

     //Append requested digit
     displayLabel.append(button->text());

     //Set number back to display
     ui->displayPanel->setText(displayLabel);
 }

 // Called whenever an action button is clicked
 void MainWindow::actionGroup_clicked(QAbstractButton* button)
 {
     /* If the previous button that was clicked was not an operator, then we just need to save the operator
      * that was requested and exit.
      * If it was though, we need to see whether we just need to save the number that is
      * displayed or if there is already a number stored in memory, perform the calculation and
      * store the result.
      * Example for this case: 5 + 7 + -> We need to save 12 in memory and then save operator. */

     if (operatorClicked) {
         storedOperator = button->text().at(0);
     }
     else {
         if (hasStoredNumber) {
             calculate_result();
         }
         else {
             //Set the flag to indicate that we now have a number stored in memory
             hasStoredNumber = true;
             //Get string from display
             QString displayLabel = ui->displayPanel->text();
             //Convert string to double and save
             storedNumber = displayLabel.toDouble();
         }
         //Set the flag that the last button that was clicked was an operator
         operatorClicked = true;
         //Store operator in memory
         storedOperator = button->text().at(0);
     }
 }

 void MainWindow::on_actionDel_clicked()
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();

     //Check if label is empty
     if (displayLabel.length() == 0) {
         return;
     }

     //Delete last digit from string
     displayLabel.QString::chop(1);
     //Set number back to display
     ui->displayPanel->setText(displayLabel);
 }

 void MainWindow::on_actionCalc_clicked()
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();
     /* A number must be saved in memory to be able calculate a result.
      * In addition, a number with at least one digit should be present in the display and
      * The last button that was clicked should not be an operator */

     if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
         return;
     }

     //Calculate result and set in on display
     calculate_result();

     //Set stored number flag to false (we have it on screen now)
     hasStoredNumber = false;

 }

 void MainWindow::on_comma_clicked()
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();

     /* Append the digit only if we are not exceeding the digit limit.
      * More specifically in this case, we need 2 digits to be available.
      * One for the comma and at least another one for a remaining digit.
      * Also check if whether there is another comma already present. */
     if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
         displayLabel.contains('.', Qt::CaseSensitive)) {
         return;
     }

     //If label is empty, add zero and then append comma
     if (displayLabel.length() == 0) {
         displayLabel = "0";
     }

     //Append comma
     displayLabel.append('.');
     //Set number back to display
     ui->displayPanel->setText(displayLabel);
 }

 void MainWindow::on_actionClear_clicked()
 {
     //Clear display label (for now)
     ui->displayPanel->clear();
     //Set operator and store number flags to false
     operatorClicked = false;
     hasStoredNumber = false;
 }

 void MainWindow::on_actionPercent_clicked()
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();
     //Convert to double
     double percentage = displayLabel.toDouble();
     //Just multiply with 0.01 to make it a percentage
     percentage *= 0.01;
     //Since there might be an overflow, its best to convert the number carefully
     displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
     //Set number back to display
     ui->displayPanel->setText(displayLabel);
 }

 void MainWindow::on_actionSign_clicked()
 {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();
     //Convert to double
     double percentage = displayLabel.toDouble();
     //Just multiply with -1 to change its sign
     percentage *= -1;
     //Convert the number carefully
     displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
     //Set number back to display
     ui->displayPanel->setText(displayLabel);
 }

 //==================================================================================
 //Helper functions
 //==================================================================================
 void MainWindow::calculate_result() {
     //Get string from display
     QString displayLabel = ui->displayPanel->text();

     //If the displayed number ends with a comma, drop the comma.
      if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
          displayLabel.QString::chop(1);
      }

      //Decide what to do according to operation
      if (storedOperator == '+') {
          storedNumber += displayLabel.toDouble();
      }
      else if (storedOperator == '-') {
          storedNumber -= displayLabel.toDouble();
      }
      else if (storedOperator == 'x') {
          storedNumber *= displayLabel.toDouble();
      }
      else if (storedOperator == '/') {
          storedNumber /= displayLabel.toDouble();
      }

      //Since there might be an overflow, its best to convert the number carefully
      displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);

      //Set number back to display
      ui->displayPanel->setText(displayLabel);
 }

 //Keyboard buttons should call the corresponding functions
 void MainWindow::keyPressEvent(QKeyEvent *e) {
     switch (e->key()) {
         //Numbers
         case Qt::Key_1:
             numberGroup_clicked(ui->num1);
             break;
         case Qt::Key_2:
             numberGroup_clicked(ui->num2);
             break;
         case Qt::Key_3:
             numberGroup_clicked(ui->num3);
             break;
         case Qt::Key_4:
             numberGroup_clicked(ui->num4);
             break;
         case Qt::Key_5:
             numberGroup_clicked(ui->num5);
             break;
         case Qt::Key_6:
             numberGroup_clicked(ui->num6);
             break;
         case Qt::Key_7:
             numberGroup_clicked(ui->num7);
             break;
         case Qt::Key_8:
             numberGroup_clicked(ui->num8);
             break;
         case Qt::Key_9:
             numberGroup_clicked(ui->num9);
             break;
         case Qt::Key_0:
             numberGroup_clicked(ui->num0);
             break;
         //Operators
         case Qt::Key_Plus:
             actionGroup_clicked(ui->actionPlus);
             break;
         case Qt::Key_Minus:
             actionGroup_clicked(ui->actionMinus);
             break;
         case Qt::Key_Asterisk:
             actionGroup_clicked(ui->actionMul);
             break;
         case Qt::Key_Slash:
             actionGroup_clicked(ui->actionDiv);
             break;
         //Comma
         case Qt::Key_Period:
             on_comma_clicked();
             break;
         //Return (enter)
         case Qt::Key_Enter:
         case Qt::Key_Return:
             on_actionCalc_clicked();
             break;
         //Backspace and delete
         case Qt::Key_Backspace:
             on_actionDel_clicked();
             break;
         case Qt::Key_Delete:
             on_actionClear_clicked();
             break;
         //Percentage
         case Qt::Key_Percent:
             on_actionPercent_clicked();
             break;
     }


}





