#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>

namespace Ui {
class Statistique;
}

class Statistique : public QDialog
{
    Q_OBJECT

public:
    explicit Statistique(QWidget *parent = nullptr);
    ~Statistique();
    void  makePlot_Annee();
    QVector<double> Statistique_montant();
private slots:
    void on_pushButton_statis_clicked();

private:
    Ui::Statistique *ui;
};

#endif // STATISTIQUE_H
