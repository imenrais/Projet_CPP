#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"arduino.h"

#include <QMainWindow>
#include"gestion_de_destination.h"
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QFileDialog>
#include<QProgressBar>
#include<QSlider>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
void update_label();
    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pb_pdf_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Gestion_de_destination G;
    QMediaPlayer* player;
    QVideoWidget*vw;
    QProgressBar*bar;
    QSlider*slider;
    Arduino A;
    QByteArray data;
public slots:
    int on_pb_pdf_clicked();
};

#endif // MAINWINDOW_H
