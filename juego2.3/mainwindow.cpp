#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include "DuCrypt.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow_juego.h"
#include "niveles.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->contralineEdit_2->setEchoMode(QLineEdit::Password);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_buttonBox_accepted()
{

    bool esusuario=true;
    int cant;


    QSqlQuery q;
     Usuario u(-1,ui->UsuariolineEdit->text(),ui->contralineEdit_2->text());

        q.exec(QString("SELECT count(*) FROM usuario WHERE nombre LIKE '%1' AND "
                       "contrasenya LIKE '%2'").arg( (u.getnombre())).arg( (u.getcontra())));
        q.next();
       cant=q.value(0).toInt();







           niveles *n=new niveles;
           n->show();
           this->close();







   }




void MainWindow::on_buttonBox_rejected()
{
        close();
}

void MainWindow::on_RegistrarUsuariopushButton_clicked()
{

    Dialog d(this);
    if( d.exec()==QDialog::Rejected){
        return;
    }



  auto admi =  d.getAdmi();
  QSqlQuery q;
  q.exec(QString("INSERT INTO usuario (nombre, contrasenya) VALUES ('%1','%2')")
         .arg((admi.getnombre()))
         .arg((admi.getcontra())));



}

