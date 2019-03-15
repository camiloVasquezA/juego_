#include "mainwindow_juego.h"
#include "ui_mainwindow_juego.h"
#include <QGraphicsView>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<string.h>


#include <QDebug>
using namespace std;
void MainWindow_juego::verificar()
{
    if(mArkanoid->getscena()->getvidas()==0){
        QMessageBox::information(this,"Arkanoid","Fin del juego");
        mArkanoid->getscena()->setvidas(3);}

}

MainWindow_juego::MainWindow_juego(int niv,QString puerto,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_juego)
{
    ui->setupUi(this);
    nivel=niv;
    puert=puerto;
    mArkanoid=new Arkanoid(nivel,ui->graphicsView,this);
    setCentralWidget(ui->graphicsView);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/nuevofondo.png")));
    timer=new QTimer();
   connect(timer,SIGNAL(timeout()),this,SLOT(verificar()));
    timer->start(50);
    timer_control=new QTimer();
    control=new QSerialPort(this);
    connect(timer_control,SIGNAL(timeout()),this,SLOT(Joy()));


    control->setPortName("COM6");
    //timer_control->start(100);
    if(control->open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!control->setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
            qDebug()<<control->errorString();

        if(!control->setDataBits(QSerialPort::Data8))
            qDebug()<<control->errorString();

        if(!control->setParity(QSerialPort::NoParity))
            qDebug()<<control->errorString();

        if(!control->setStopBits(QSerialPort::OneStop))
            qDebug()<<control->errorString();

        if(!control->setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<control->errorString();
            timer_control->start(20);
    }
    else{
        qDebug()<<"Serial COM6 not opened. Error: "<<control->errorString();
    }
}

MainWindow_juego::~MainWindow_juego()
{
    delete ui;

}



void MainWindow_juego::on_actionQuitar_triggered()
{
    mArkanoid->stopGame();
    close();
}

void MainWindow_juego::on_actionIniciar_juego_triggered()
{
     mArkanoid->starGame();
}



void MainWindow_juego::Joy(){
        char data;
        int l = 0;
        bool flag=true;

           if(control->waitForReadyRead(100)){

                //Data was returned
                l = control->read(&data,1);
                switch (data) {

                case '0':
                   mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()-(mArkanoid->getscena()->getplataform()->getvx())*2.0);

                    break;
                case '1':
                   mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()-(mArkanoid->getscena()->getplataform()->getvx())*1.3);

                    break;
                case '2':
                   mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()-(mArkanoid->getscena()->getplataform()->getvx()));

                    break;
                case '3':
                   mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()+(mArkanoid->getscena()->getplataform()->getvx()));

                    break;
                case '4':
                  mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()+(mArkanoid->getscena()->getplataform()->getvx())*1.3);

                    break;
                case 'X':
                    mArkanoid->getscena()->getplataform()->setx(mArkanoid->getscena()->getplataform()->getx()+(mArkanoid->getscena()->getplataform()->getvx())*2.0);

                    break;

                case 'N':
                    flag=false;
                    break;
                default:
                    flag=false;
                    break;
                }

                qDebug()<<"Response: "<<data;
                flag=false;

            }else{
                //No data
                qDebug()<<"Time out";
          }
        //}
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        //control->close();

}




