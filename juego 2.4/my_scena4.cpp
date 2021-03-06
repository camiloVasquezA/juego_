#include "my_scena4.h"
#include "global_defines.h"
#include "timer.h"
#include <QKeyEvent>
#include "ball_item.h"
#include "platafor_item.h"
#include "d_util.h"
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include "vidas.h"
#include<QMediaPlayer>
#define MILISECONDS 10



my_scena4::my_scena4(QObject *parent)
    :QGraphicsScene (0.0,0.0,XSIZE,YSIZE,parent)
{
    createObjects();
    confingureObjects();
    conectObjects();


}

void my_scena4::startScene()
{
    mtimer->start();
}

void my_scena4::stopScene()
{
    mtimer->terminate();
}

void my_scena4::keyPressEvent(QKeyEvent *event)
{
    mplataform->move(event->key());
}

void my_scena4::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
}

void my_scena4::createObjects()
{
    mtimer=new Timer(MILISECONDS, this);
    QString amarillo(":/amarillo.png");
    QString amarilloq(":/amarillo.png");
    QString morado(":/verde.png");
    QString moradoq(":/verde.png");
    QString azul(":/azul.png");
    QString azulq(":/azul.png");
    QString rojo(":/rojo.png");
    QString verde(":/morado.png");
    mtimer=new Timer(MILISECONDS, this);
    mball=new Ball_Item(XBALL,YBALL,WBALL,HBALL,VXBALL,VYBALL);
    mplataform=new Platafor_Item(XPLATAFORM,575,WPLATAFORM,HPLATAFORM, VXPLATAFORM,VYPLATAFORM);
    l1=new QGraphicsLineItem(0,614,1000,614);
    vida1=new vidas(20,615,30,40,0,0);
    vida2=new vidas(75,615,30,40,0,0);
    vida3=new vidas(130,615,30,40,0,0);
    int xb=68,yb=50,wb=80,hb=36;

for (int i=0 ;i<11;i++){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,amarilloq,amarillo));
            xb=xb+80;
            //xb=xb+80;
  }

yb=yb+37;
xb=68;
for (int i=0 ;i<6;i++){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,amarilloq,amarillo));
            xb=xb+80;
            xb=xb+80;
  }

yb=yb+37;
xb=68;
for (int i=0 ;i<6;i++){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azul));
            xb=xb+80;
            xb=xb+80;
  }
yb=yb+37;
xb=68;

for (int i=0 ;i<11;i++){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,rojo,rojo));
            xb=xb+80;
            //xb=xb+80;
  }
}

void my_scena4::confingureObjects()
{   addItem(mball);
    addItem(mplataform);
    addItem(l1);
    addItem(vida1);
    addItem(vida2);
    addItem(vida3);

    addItem(bloques.last());
    addItem(bloques.last()->getlin1());
    addItem(bloques.last()->getlin2());
    for(int i=0;i<bloques.length();i++){
        addItem( bloques.at(i));
        addItem(bloques.at(i)->getlin1());
        addItem(bloques.at(i)->getlin2());
    }


    addRect(0.0,0.0,XSIZE,YSIZE,QPen(QColor(Qt::blue)));
}

void my_scena4::conectObjects()
{
    connect(mtimer,&Timer::timeOut,this,&my_scena4::updateScene);
}

void my_scena4::updateScene()
{

    mball->move();
    if(mball->collidesWithItem(mplataform)){
        checkoCollisions();



    }
    else if(mball->collidesWithItem(l1)){
        mtimer->terminate();

        vida-=1;
        if(vida==2)
            removeItem(vida3);
        else if(vida==1)
            removeItem(vida2);
        else if(vida==0)
            removeItem(vida1);




        mball->setx(XSIZE/2);
        mball->sety(YSIZE/2);
    }
    for(int i=0; i<bloques.length();i++){
        if(bloques.at(i)->collidesWithItem(mball)){
            collisionsWhitbloque();
            bloques.at(i)->setcambio(true);


            removeItem(bloques.at(i));
            removeItem(bloques.at(i)->getlin1());
            removeItem(bloques.at(i)->getlin2());
            bloques.removeAt(i);
            puntaje+=10;
            nbloq-=1;




        }
     else if(mball->collidesWithItem(bloques.at(i)->getlin1())){
             collinsWhitLine1();
             bloques.at(i)->setcambio(true);
             removeItem(bloques.at(i));
             removeItem(bloques.at(i)->getlin1());
             removeItem(bloques.at(i)->getlin2());
             bloques.removeAt(i);
             puntaje+=10;
             nbloq-=1;



    }
        else if(mball->collidesWithItem(bloques.at(i)->getlin2())){
            collinsWhitLine2();
            bloques.at(i)->setcambio(true);
            removeItem(bloques.at(i));
            removeItem(bloques.at(i)->getlin1());
            removeItem(bloques.at(i)->getlin2());
            bloques.removeAt(i);
            puntaje+=10;
            nbloq-=1;

       }
}

 update();

}

void my_scena4::checkoCollisions()
{

    QMediaPlayer *rebote=new QMediaPlayer();
    rebote->setMedia(QUrl("qrc:/Rebote pelota 2D-[AudioTrimmer.com].mp3"));
    int bvx=mball->getvx();
    int bvy=mball->getvy();
   const int pvx=mplataform->getvx();
  const  int pvy=mplataform->getvy();

    if(bvx>0&&bvy>0&&pvx>0&&pvy==0){
       bvx=D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy);
       rebote->setVolume(60);
       rebote->play();
    }

    else if(bvx<0&&bvy>0&&pvx>0&&pvy==0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);
        rebote->setVolume(60);
        rebote->play();

    }
    else if (bvx>0&&bvy>0&&pvx<0&&pvy==0) {
        bvx=D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy)-0.5;
        rebote->setVolume(50);
        rebote->play();

    }
    else if(bvx<0&&bvy>0&&pvx<0&&pvy==0){

       bvx=-D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy)-0.5;
       rebote->setVolume(50);
       rebote->play();
    }

    mball->setvx(bvx);
    mball->setvy(bvy);
}

void my_scena4::collisionsWhitbloque()
{
    QMediaPlayer *sonidoBloque=new QMediaPlayer();
    sonidoBloque->setMedia(QUrl("qrc:/GOLPE DE BATE BASEBALL.mp3"));
    sonidoBloque->setVolume(40);
    int bvx=mball->getvx();
    int bvy=mball->getvy();

    if(bvx>0&&bvy>0){
       bvx=D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy);
       sonidoBloque->setVolume(40);
       sonidoBloque->play();
    }

    else if(bvx<0&&bvy>0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);
        sonidoBloque->setVolume(40);
        sonidoBloque->play();

    }
    else if (bvx>0&&bvy<0) {
        bvx=D_Util::abs(bvx);
        bvy=D_Util::abs(bvy);
        sonidoBloque->setVolume(40);
        sonidoBloque->play();


    }
    else if(bvx<0&&bvy<0){

       bvx=-D_Util::abs(bvx);
       bvy=D_Util::abs(bvy);
       sonidoBloque->setVolume(40);
       sonidoBloque->play();
    }
  mball->setvx(bvx);
  mball->setvy(bvy);
    }

void my_scena4::collinsWhitLine1(){
    QMediaPlayer *sonidoBloque=new QMediaPlayer();
    sonidoBloque->setMedia(QUrl("qrc:/GOLPE DE BATE BASEBALL.mp3"));
 int bvx=mball->getvx();
 int bvy=mball->getvy();
 if(bvx<0 && bvy<0){
     bvx=D_Util::abs(bvx);
     bvy=-D_Util::abs(bvy);
     sonidoBloque->setVolume(40);
     sonidoBloque->play();

 }
 else if(bvx<0 && bvy>0){
     bvx=D_Util::abs(bvx);
     bvy=D_Util::abs(bvy);
     sonidoBloque->setVolume(40);
     sonidoBloque->play();

 }

 mball->setvx(bvx);
 mball->setvy(bvy);


}

void my_scena4::collinsWhitLine2()
{
    QMediaPlayer *sonidoBloque=new QMediaPlayer();
    sonidoBloque->setMedia(QUrl("qrc:/GOLPE DE BATE BASEBALL.mp3"));
    int bvx=mball->getvx();
    int bvy=mball->getvy();
    if(bvx>0 && bvy<0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);
        sonidoBloque->setVolume(40);
        sonidoBloque->play();


    }
    else if(bvx>0 && bvy>0){
        bvx=-D_Util::abs(bvx);
        bvy=D_Util::abs(bvy);
        sonidoBloque->setVolume(40);
        sonidoBloque->play();

    }

    mball->setvx(bvx);
    mball->setvy(bvy);

}

bool my_scena4::choqueBloque()
{   choque=true;
    bool choq=choque;
    choque=false;
    return  choq;

}


