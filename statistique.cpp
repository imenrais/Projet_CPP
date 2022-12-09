#include "statistique.h"
#include "ui_statistique.h"
#include "qcustomplot.h"
#include <QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>

Statistique::Statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistique)
{
    ui->setupUi(this);
}

Statistique::~Statistique()
{
    delete ui;
}

QVector<double> Statistique::Statistique_montant()
{
    QSqlQuery q;
    QVector<double> stat(5);
    stat[0]=0;
    stat[1]=0;
    stat[2]=0;
    stat[3]=0;
    stat[4]=0;

    q.prepare("SELECT prix FROM GDESTINATION WHERE 100<prix and prix<=200");
    q.exec();
    while (q.next())
    {
        stat[0]++;
    }
    q.prepare("SELECT prix FROM GDESTINATION WHERE 200<prix and prix<=300");
    q.exec();
    while (q.next())
    {
        stat[1]++;
    }
    q.prepare("SELECT prix FROM GDESTINATION WHERE 300<prix and prix<=400");
    q.exec();
    while (q.next())
    {
        stat[2]++;
    }
    q.prepare("SELECT prix FROM GDESTINATION WHERE 400<prix");
    q.exec();
    while (q.next())
    {
        stat[3]++;
    }
    return stat;
}
void Statistique::makePlot_Annee()
{
    QVector<double> x3(5), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customPlot2->xAxis, ui->customPlot2->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, Statistique::Statistique_montant());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customPlot2->replot();


    // move bars above graphs and grid below bars:
    ui->customPlot2->addLayer("abovemain", ui->customPlot2->layer("main"), QCustomPlot::limAbove);
    ui->customPlot2->addLayer("belowmain", ui->customPlot2->layer("main"), QCustomPlot::limBelow);
    ui->customPlot2->xAxis->grid()->setLayer("belowmain");
    ui->customPlot2->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2<<3<<4<<5<<6;
    QVector<QString> labels;
    labels<<"100-200"<<"200-300"<<"300-400"<<">400"<<">400";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customPlot2->xAxis->setTicker(textTicker);
    ui->customPlot2->xAxis->setSubTicks(false);
    ui->customPlot2->xAxis->setTickLength(0,4);
    ui->customPlot2->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot2->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(10, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customPlot2->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customPlot2->axisRect()->setBackground(axisRectGradient);

    ui->customPlot2->rescaleAxes();
    ui->customPlot2->xAxis->setRange(0, 7);
    ui->customPlot2->yAxis->setRange(0, 10);


}

void Statistique::on_pushButton_statis_clicked()
{
    Statistique::makePlot_Annee();
}
