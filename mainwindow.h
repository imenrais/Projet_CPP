#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sponsor.h"


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_11_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_8_pressed();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_9_clicked();



    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    sponsor s ;
};
#endif // MAINWINDOW_H
