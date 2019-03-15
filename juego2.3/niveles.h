#ifndef NIVELES_H
#define NIVELES_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class niveles;
}

class niveles : public QMainWindow
{
    Q_OBJECT

public:
    explicit niveles(QWidget *parent = nullptr);
    int niv;
    QString puerto;
    ~niveles();

private slots:
    void on_nivel1_clicked();

    void on_nivel2_clicked();

    void on_nivel3_clicked();

    void on_nivel4_clicked();

private:
    Ui::niveles *ui;

};

#endif // NIVELES_H
