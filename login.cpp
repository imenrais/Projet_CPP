#include "login.h"
#include "ui_login.h"
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
        ui->setupUi(this);
        ui->winStack->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(1);
        ui->passwordBox->setEchoMode(QLineEdit::Password);
        ui->passwordBox->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
        ui->pBox->setEchoMode(QLineEdit::Password);
        ui->pBox->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
        ui->pBox_2->setEchoMode(QLineEdit::Password);
        ui->pBox_2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

login::~login()
{
    delete ui;
}

void login::on_loginButton_clicked()
{
    this->loggedIn = Login(ui->usernameBox->text(), ui->passwordBox->text());

        if(this->loggedIn)
        {
            this->username = ui->usernameBox->text();
            this->password = ui->passwordBox->text();

            ui->loginLabel->setText("");
            ui->winStack->setCurrentIndex(2);

        }
        else
        {
            ui->loginLabel->setText("Login failed: Invalid credentials!");
        }
}

bool login::Login(QString u, QString p)
{
   // ui->adminButton->setVisible(false);

    bool exists = false;

    QSqlQuery Query;
    Query.prepare("SELECT username FROM login WHERE username = (:un) AND passwd = (:pw)");
    Query.bindValue(":un", u);
    Query.bindValue(":pw", p);

    if (Query.exec())
    {
        if (Query.next())
        {
            exists = true;
        }
    }

    return exists;
}

void login::on_regButton_clicked()
{
        ui->uBox->setText(ui->usernameBox->text());
        ui->pBox->setText(ui->passwordBox->text());
        ui->winStack->setCurrentIndex(1);
}


void login::on_completeRegButton_clicked()
{
    bool halt = false;

        if(ui->uBox->text() == "")
        {
            ui->uBox->setPlaceholderText("Username EMPTY!");
            halt = true;
        }

        if(ui->pBox->text() == "")
        {
            ui->pBox->setPlaceholderText("Password EMPTY!");
            halt = true;
        }



        if(ui->fBox->text() == "")
        {
            ui->fBox->setPlaceholderText("First Name EMPTY!");
            halt = true;
        }



        if(ui->lBox->text() == "")
        {
            ui->lBox->setPlaceholderText("Last Name EMPTY!");
            halt = true;
        }

        QSqlQuery cQuery;
        cQuery.prepare("SELECT username FROM login WHERE username = (:un)");
        cQuery.bindValue(":un", ui->uBox->text());

        if(cQuery.exec())
        {
            if(cQuery.next())
            {
                ui->uBox->setText("");
                ui->uBox->setPlaceholderText("Choose a different Username!");
                halt = true;
            }
        }

        QSqlQuery cQuery2;
        cQuery2.prepare("SELECT passwd FROM login WHERE passwd = (:pw)");
        cQuery2.bindValue(":pw", ui->lBox->text());

        if(cQuery2.exec())
        {
            if(cQuery2.next())
            {
                ui->lBox->setText("");
                ui->lBox->setPlaceholderText("Use another Password!");
                halt = true;
            }
        }


        if(halt)
        {
            ui->regLabel->setText("Please correct your mistakes.");
        }
        else
        {
            if (this->picName != "")
            {
                QString to = this->picDir+"/"+ui->uBox->text();

                if (QFile::exists(to))
                {
                    QFile::remove(to);
                }

                QFile::copy(this->picName, to);
                this->picName = "";
            }

            ui->regLabel->setText("");
            QSqlQuery iQuery;
            iQuery.prepare("INSERT INTO login(username, passwd, fname, lname)"\
                           "VALUES(:un, :pw, :fn,  :ln)");
            iQuery.bindValue(":un", ui->uBox->text());
            iQuery.bindValue(":pw", ui->pBox->text());
            iQuery.bindValue(":fn", ui->fBox->text());
            iQuery.bindValue(":ln", ui->lBox->text());


            if(iQuery.exec())
            {
                ui->uBox->setText("");
                ui->pBox->setText("");
                ui->fBox->setText("");
                ui->lBox->setText("");
                ui->rpLabel->setText("<img src=\":user.png\" />");
                ui->loginLabel->setText("Registration Successful! You can now login.");
                ui->winStack->setCurrentIndex(0);
                /*hide();
                mainwindow= new MainWindow(this);
                mainwindow->show();*/
            }

        }
}


void login::on_backButton_clicked()
{
        ui->loginLabel->setText("");
        ui->winStack->setCurrentIndex(0);
}




void login::on_logoutButton_clicked()
{
    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
                                           "Login System", "Are you sure you want to logout?",
                                           QMessageBox::Yes|QMessageBox::No).exec())
        {
            this->loggedIn = false;
            ui->passwordBox->setText("");
            ui->loginLabel->setText("You signed out!");
            ui->winStack->setCurrentIndex(0);
            hide();
            mainwindow= new MainWindow(this);
            mainwindow->show();
        }
}



void login::on_editButton_clicked()
{
    QSqlQuery fetcher;
        fetcher.prepare("SELECT * FROM login WHERE username = (:un) AND passwd = (:pw)");
        fetcher.bindValue(":un", this->username);
        fetcher.bindValue(":pw", this->password);
        fetcher.exec();

        int idUsername = fetcher.record().indexOf("username");
        int idPasswd = fetcher.record().indexOf("passwd");
        int idFname = fetcher.record().indexOf("fname");
        int idLname = fetcher.record().indexOf("lname");

        while (fetcher.next())
        {
            ui->uBox_2->setText(fetcher.value(idUsername).toString());
            ui->pBox_2->setText(fetcher.value(idPasswd).toString());
            ui->fBox_2->setText(fetcher.value(idFname).toString());
            ui->lBox_2->setText(fetcher.value(idLname).toString());
        }

        ui->winStack->setCurrentIndex(3);
}


void login::on_delButton_clicked()
{
    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,
                                           "Login System", "Are you sure you want to delete your account?",
                                           QMessageBox::Yes|QMessageBox::No).exec())
        {
            QString to = this->picDir+"/"+this->username;

            if (QFile::exists(to))
            {
                QFile::remove(to);
            }

            QSqlQuery dQuery;
            dQuery.prepare("DELETE FROM login WHERE username = (:un)");
            dQuery.bindValue(":un", this->username);

            if(dQuery.exec())
            {
                ui->usernameBox->setText("");
                ui->passwordBox->setText("");
                ui->loginLabel->setText("Account deleted!");
                ui->winStack->setCurrentIndex(0);
            }
        }
}


void login::on_pushButton_2_clicked()
{
    bool halt = false;

        if(ui->uBox_2->text() == "")
        {
            ui->uBox_2->setPlaceholderText("Username EMPTY!");
            halt = true;
        }

        if(ui->pBox_2->text() == "")
        {
            ui->pBox_2->setPlaceholderText("Password EMPTY!");
            halt = true;
        }



        if(ui->fBox_2->text() == "")
        {
            ui->fBox_2->setPlaceholderText("First Name EMPTY!");
            halt = true;
        }



        if(ui->lBox_2->text() == "")
        {
            ui->lBox_2->setPlaceholderText("Last Name EMPTY!");
            halt = true;
        }

        QSqlQuery cQuery;
        cQuery.prepare("SELECT username FROM sys_users WHERE username = (:un)");
        cQuery.bindValue(":un", ui->uBox->text());

        if(cQuery.exec())
        {
            if(cQuery.next() && ui->uBox_2->text() != cQuery.value(0).toString())
            {
                ui->uBox_2->setText("");
                ui->uBox_2->setPlaceholderText("Choose a different Username!");
                halt = true;
            }
        }

        QSqlQuery cQuery2;
        cQuery2.prepare("SELECT username FROM login WHERE username = (:us)");
        cQuery2.bindValue(":us", ui->uBox_2->text());

        if(cQuery2.exec())
        {
            if(cQuery2.next() && ui->uBox_2->text() != cQuery2.value(0).toString())
            {
                ui->uBox_2->setText("");
                ui->uBox_2->setPlaceholderText("Use another username!");
                halt = true;
            }
        }


        if(halt)
        {
            ui->regLabel_2->setText("Please correct your mistakes.");
        }
        else
        {
            if (this->picName != "")
            {
                QString to = this->picDir+"/"+ui->uBox_2->text();

                if (QFile::exists(to))
                {
                    QFile::remove(to);
                }

                QFile::copy(this->picName, to);
                this->picName = "";
            }

            ui->regLabel_2->setText("");
            QSqlQuery iQuery;
            iQuery.prepare("UPDATE login SET username=(:un), passwd=(:pw), fname=(:fn), lname=(:ln) WHERE username=(:uno)");
            iQuery.bindValue(":un", ui->uBox_2->text());
            iQuery.bindValue(":pw", ui->pBox_2->text());
            iQuery.bindValue(":fn", ui->fBox_2->text());

            iQuery.bindValue(":ln", ui->lBox_2->text());

            iQuery.bindValue(":uno", ui->uBox_2->text());

            if(iQuery.exec())
            {
                ui->winStack->setCurrentIndex(2);
            }

        }
}


void login::on_backButton_2_clicked()
{
    ui->winStack->setCurrentIndex(2);
}


void login::on_uplButton_clicked()
{
    this->picName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
        ui->rpLabel->setText("<img src=\"file:///"+this->picName+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
}


void login::on_uplButton_2_clicked()
{
    this->picName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
        ui->rpLabel->setText("<img src=\"file:///"+this->picName+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
}


void login::on_winStack_currentChanged(int arg1)
{
    if(arg1 == 3 && this->loggedIn)
       {
           if(QFile::exists(this->picDir+"/"+this->username))
           {
               ui->rpLabel_2->setText("<img src=\"file:///"+this->picDir+"/"+this->username+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
           }
       }

       if(arg1 == 2 && this->loggedIn)
       {
           if(QFile::exists(this->picDir+"/"+this->username))
           {
               ui->loggedPic->setText("<img src=\"file:///"+this->picDir+"/"+this->username+"\" alt=\"Image read error!\" height=\"128\" width=\"128\" />");
           }

           QSqlQuery fetcher;
           fetcher.prepare("SELECT * FROM login WHERE username = (:un)");
           fetcher.bindValue(":un", this->username);
           fetcher.exec();

           int idFname = fetcher.record().indexOf("fname");

           int idLname = fetcher.record().indexOf("lname");
           int idRank = fetcher.record().indexOf("rank");


           QString fullname,  rank;

           while (fetcher.next())
           {
               fullname = fetcher.value(idFname).toString();

               fullname += " " + fetcher.value(idLname).toString();
               rank = fetcher.value(idRank).toString();

           }
           if(rank == "-1")
           {
               //ui->adminButton->setVisible(true);
           }
           ui->nameLabel->setText(fullname);
          // ui->rankLabel->setText(rank);

       }

       if(arg1 == 4 && this->loggedIn)
       {
           ui->stackedWidget->setCurrentIndex(0);
       }
}





void login::on_pageButton_clicked()
{
    ui->winStack->setCurrentIndex(2);
}


void login::on_editedButton_2_clicked()
{
    if(this->tblMdl->submitAll())
        {
            this->tblMdl->database().commit();
            ui->adminLabel->setText("Saved to database!");
        }
        else
        {
            this->tblMdl->database().rollback();
        }
}


void login::on_backButton_5_clicked()
{
    this->tblMdl->revertAll();
        this->tblMdl->database().rollback();
}


void login::on_userBrowse_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void login::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 0 && this->loggedIn)
        {
            ui->headLabel->setText("USERS");
            this->tblMdl = new QSqlTableModel;
            this->tblMdl->setTable("login");
            this->tblMdl->setFilter("rank != -1 AND rank != 0");
            this->tblMdl->select();
            ui->tableView->setModel(this->tblMdl);
            this->tblMdl->database().transaction();
        }

        if(arg1 == 1 && this->loggedIn)
        {
            ui->headLabel->setText("ADMINS");
            this->tblMdl = new QSqlTableModel;
            this->tblMdl->setTable("login");
            this->tblMdl->setFilter("rank == -1 OR rank == 0");
            this->tblMdl->select();
            ui->tableView_2->setModel(this->tblMdl);
            this->tblMdl->database().transaction();}
}

