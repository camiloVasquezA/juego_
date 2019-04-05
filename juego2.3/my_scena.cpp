#include "my_scena.h"
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



my_scena::my_scena(QObject *parent)
    :QGraphicsScene (0.0,0.0,XSIZE,YSIZE,parent)
{
    createObjects();
    confingureObjects();
    conectObjects();


}

void my_scena::startScene()
{
    mtimer->start();
}

void my_scena::stopScene()
{
    mtimer->terminate();
}

void my_scena::keyPressEvent(QKeyEvent *event)
{
    mplataform->move(event->key());
}

void my_scena::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
}

void my_scena::createObjects()
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
    int xb=100,yb=50,wb=80,hb=36;

    for(int i=0;i<=21;i++){



         if(i<=1){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,amarilloq,amarillo));

            xb=xb+720;
            if(i==1){
                yb=yb+hb;
                xb=100;
            }



         }
         else if(i>1&&i<=5){

             if(i>1&&i<4){
                    bloques.append(new bloque(xb,yb,wb,hb,0,0,moradoq,morado));
                 xb=xb+wb;}
             if(i==3){
                 xb=820;
             }
             else if(i>3){
                    bloques.append( new bloque(xb,yb,wb,hb,0,0,moradoq,morado));
                 xb=xb-wb;}
             if(i==5){
                 xb=100;
                 yb=yb+hb;
             }




         }
         else if(i>5&&i<=11){
             if(i>5&&i<9){
                  bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azulq));
                  xb=xb+wb;


             }
             if(i==8){
                 xb=820;
             }
             else if(i>8){
                 bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azulq));
                 xb=xb-wb;

             }
             if(i==11){
                 xb=100;
                 yb=yb+hb;
             }




         }
         else if(i>11){

                 bloques.append(new bloque(xb,yb,wb,hb,0,0,rojo,rojo));
                  xb=xb+wb;


         }


    }

 xb=100,yb=195;

for(int i=0;i<=20;i++){
    if(i<10)
    {
    bloques.append(new bloque(xb,yb,wb,hb,0,0,rojo,rojo));
     xb=xb+wb;
    }
    if (i==10)
        xb=100,yb=195+36;
    if(i>10)
    {
      bloques.append(new bloque(xb,yb,wb,hb,0,0,rojo,verde));
      xb=xb+wb;
    }

}

yb=yb+hb+1;
xb=100;
for(int i=0;i<10;i++){
    bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azul));
    xb=xb+wb;
}
}

void my_scena::confingureObjects()
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

void my_scena::conectObjects()
{
    connect(mtimer,&Timer::timeOut,this,&my_scena::updateScene);
}

void my_scena::updateScene()
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




        }
     else if(mball->collidesWithItem(bloques.at(i)->getlin1())){
             collinsWhitLine1();
             bloques.at(i)->setcambio(true);
             removeItem(bloques.at(i));
             removeItem(bloques.at(i)->getlin1());
             removeItem(bloques.at(i)->getlin2());
             bloques.removeAt(i);



    }
        else if(mball->collidesWithItem(bloques.at(i)->getlin2())){
            collinsWhitLine2();
            bloques.at(i)->setcambio(true);
            removeItem(bloques.at(i));
            removeItem(bloques.at(i)->getlin1());
            removeItem(bloques.at(i)->getlin2());
            bloques.removeAt(i);








       }



        }


 update();

}

void my_scena::checkoCollisions()
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
       rebote->play();
    }

    else if(bvx<0&&bvy>0&&pvx>0&&pvy==0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);
        rebote->play();

    }
    else if (bvx>0&&bvy>0&&pvx<0&&pvy==0) {
        bvx=D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy)-0.5;
        rebote->play();

    }
    else if(bvx<0&&bvy>0&&pvx<0&&pvy==0){

       bvx=-D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy)-0.5;
       rebote->play();
    }

    mball->setvx(bvx);
    mball->setvy(bvy);
}

void my_scena::collisionsWhitbloque()
{
    int bvx=mball->getvx();
    int bvy=mball->getvy();

    if(bvx>0&&bvy>0){
       bvx=D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy);
    }

    else if(bvx<0&&bvy>0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);

    }
    else if (bvx>0&&bvy<0) {
        bvx=D_Util::abs(bvx);
        bvy=D_Util::abs(bvy);


    }
    else if(bvx<0&&bvy<0){

       bvx=-D_Util::abs(bvx);
       bvy=D_Util::abs(bvy);
    }
  mball->setvx(bvx);
  mball->setvy(bvy);
    }

void my_scena::collinsWhitLine1(){

 int bvx=mball->getvx();
 int bvy=mball->getvy();
 if(bvx<0 && bvy<0){
     bvx=D_Util::abs(bvx);
     bvy=-D_Util::abs(bvy);

 }
 else if(bvx<0 && bvy>0){
     bvx=D_Util::abs(bvx);
     bvy=D_Util::abs(bvy);
 }

 mball->setvx(bvx);
 mball->setvy(bvy);


}

void my_scena::collinsWhitLine2()
{

    int bvx=mball->getvx();
    int bvy=mball->getvy();
    if(bvx>0 && bvy<0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);

    }
    else if(bvx>0 && bvy>0){
        bvx=-D_Util::abs(bvx);
        bvy=D_Util::abs(bvy);
    }

    mball->setvx(bvx);
    mball->setvy(bvy);

}

bool my_scena::choqueBloque()
{   choque=true;
    bool choq=choque;
    choque=false;
    return  choq;

}


