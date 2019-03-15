#include "niveles.h"
#include "ui_niveles.h"
#include"mainwindow_juego.h"
#include "QString"
#include<QMainWindow>
#include <QMovie>
niveles::niveles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);
 puerto=ui->lineEdit->text();


 QSize size(151,91);
 QMovie *mov=new QMovie(":/jostick.gif");
 mov->setScaledSize(size);
 ui->label_2->setMovie(mov);
 mov->start();

}

niveles::~niveles()
{
    delete ui;
}

void niveles::on_nivel1_clicked()
{

    niv=1;
    MainWindow_juego *j=new MainWindow_juego(niv,puerto);
    j->show();
    this->close();

}

void niveles::on_nivel2_clicked()
{
    niv=2;
    MainWindow_juego *j=new MainWindow_juego(niv,puerto);

    j->show();
    this->close();

}

void niveles::on_nivel3_clicked()
{

    niv=3;
MainWindow_juego *j=new MainWindow_juego(niv,puerto);
    j->show();
    this->close();

}

void niveles::on_nivel4_clicked()
{
    niv=4;
    MainWindow_juego *j=new MainWindow_juego(niv,puerto);
    j->show();
    this->close();


}

