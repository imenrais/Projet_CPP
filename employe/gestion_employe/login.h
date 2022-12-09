#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QCoreApplication>
#include <QSqlTableModel>
#include "mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    bool Login(QString u, QString p);
        bool loggedIn;
        QString picName;
        QString picDir = QCoreApplication::applicationDirPath()+"/../../LogSys/users/avatar";
        QSqlTableModel* tblMdl;
          QByteArray data;

private slots:
        void on_loginButton_clicked();

        void on_regButton_clicked();

        void on_completeRegButton_clicked();

        void on_backButton_clicked();

        void on_logoutButton_clicked();

        void on_editButton_clicked();

        void on_delButton_clicked();

        void on_pushButton_2_clicked();

        void on_backButton_2_clicked();

        void on_uplButton_clicked();

        void on_uplButton_2_clicked();

        void on_winStack_currentChanged(int arg1);


        void on_pageButton_clicked();

        void on_editedButton_2_clicked();

        void on_backButton_5_clicked();

        void on_userBrowse_clicked();

        void on_stackedWidget_currentChanged(int arg1);

        void on_arduino_clicked();

private:
    Ui::login *ui;
    QString username;
    QString password;
    MainWindow *mainwindow;
    QSerialPort *serial;
    QString portname;
    quint16 vendorId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();
};

#endif // LOGIN_H
