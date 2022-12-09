#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"






#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>



namespace Ui {
class MainWindow;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 Ui::MainWindow *ui;
       Etudiant E;
       QSortFilterProxyModel *proxy;
       void show_tables();


      bool fill_form(int);



      QtCharts::QChartView *chartView ;
          void choix_bar();
          void choix_pie();
void iniciar(void);

private slots:


       void on_pb_ajouter_clicked();

       void on_tab_clicked(const QModelIndex &index);

       void on_tab_doubleClicked(const QModelIndex &index);

       void on_rech_textChanged(const QString &arg1);

       void on_pb_del_clicked();

       void on_pb_modifier_clicked();


       void on_affiche_clicked();



       void on_comboBox_activated(int index);

       void on_pushButton_clicked();

       void on_pb_statistic_clicked();

       void on_formulaire_clicked();

       void on_allumer_clicked();

       void on_etindre_clicked();

       void on_pushButton_2_clicked();

       void on_camera_clicked();

       void on_return_3_clicked();

private:

    int selected=0;
    QStringList files;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionsMenu;
    QAction *mAllumerAction;
    QAction *mEtiendreAction;
    QAction *mCaptureAction;


};

#endif // MAINWINDOW_H
