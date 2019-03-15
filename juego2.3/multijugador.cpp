#include "multijugador.h"
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
#define MILISECONDS 10



multijugador::multijugador(QObject *parent)
    :QGraphicsScene (0.0,0.0,XSIZE,YSIZE,parent)
{
    createObjects();
    confingureObjects();
    conectObjects();


}

void multijugador::startScene()
{
    mtimer->start();
}

void multijugador::stopScene()
{
    mtimer->terminate();
}

void multijugador::keyPressEvent(QKeyEvent *event)
{
    mplataform->move(event->key());
}

void multijugador::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
}



void multijugador::createObjects()
{
    mtimer=new Timer(MILISECONDS, this);
    QString amarillo(":/amarilloq.png");
    QString amarilloq(":/amarillo.png");
    QString morado(":/moradoq.png");
    QString moradoq(":/morado.png");
    QString azul(":/azul.png");
    QString azulq(":/azulq.png");
    mtimer=new Timer(MILISECONDS, this);
    mball=new Ball_Item(XBALL,YBALL,WBALL,HBALL,VXBALL,VYBALL);
    mplataform=new Platafor_Item(XPLATAFORM,575,WPLATAFORM,HPLATAFORM, VXPLATAFORM,VYPLATAFORM);
    l1=new QGraphicsLineItem(0,614,1000,614);
    vida1=new vidas(20,615,30,40,0,0);
    vida2=new vidas(75,615,30,40,0,0);
    vida3=new vidas(130,615,30,40,0,0);
    int xb=200,yb=50,wb=50,hb=20;

    for(int i=0;i<=21;i++){



         if(i<=1){
            bloques.append(new bloque(xb,yb,wb,hb,0,0,amarilloq,amarillo));

            xb=xb+450;
            if(i==1){
                yb=yb+hb;
                xb=200;
            }



         }
         else if(i>1&&i<=5){

             if(i>1&&i<4){
                    bloques.append(new bloque(xb,yb,wb,hb,0,0,moradoq,morado));
                 xb=xb+wb;}
             if(i==3){
                 xb=650;
             }
             else if(i>3){
                    bloques.append( new bloque(xb,yb,wb,hb,0,0,moradoq,morado));
                 xb=xb-wb;}
             if(i==5){
                 xb=200;
                 yb=yb+hb;
             }




         }
         else if(i>5&&i<=11){
             if(i>5&&i<9){
                  bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azulq));
                  xb=xb+wb;


             }
             if(i==8){
                 xb=650;
             }
             else if(i>8){
                 bloques.append(new bloque(xb,yb,wb,hb,0,0,azul,azulq));
                 xb=xb-wb;

             }
             if(i==11){
                 xb=200;
                 yb=yb+hb;
             }




         }
         else if(i>11){

                 bloques.append(new bloque(xb,yb,wb,hb,0,0,amarilloq,amarillo));
                  xb=xb+wb;


         }


    }








}

void multijugador::confingureObjects()
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

void multijugador::conectObjects()
{
    connect(mtimer,&Timer::timeOut,this,&multijugador::updateScene);
}

void multijugador::updateScene()
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

void multijugador::checkoCollisions()
{
    int bvx=mball->getvx();
    int bvy=mball->getvy();
   const int pvx=mplataform->getvx();
  const  int pvy=mplataform->getvy();

    if(bvx>0&&bvy>0&&pvx>0&&pvy==0){
       bvx=D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy);
    }

    else if(bvx<0&&bvy>0&&pvx>0&&pvy==0){
        bvx=-D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy);

    }
    else if (bvx>0&&bvy>0&&pvx<0&&pvy==0) {
        bvx=D_Util::abs(bvx);
        bvy=-D_Util::abs(bvy)-0.5;

    }
    else if(bvx<0&&bvy>0&&pvx<0&&pvy==0){

       bvx=-D_Util::abs(bvx);
       bvy=-D_Util::abs(bvy)-0.5;
    }

    mball->setvx(bvx);
    mball->setvy(bvy);
}

void multijugador::collisionsWhitbloque()
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

void multijugador::collinsWhitLine1(){

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

void multijugador::collinsWhitLine2()
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

bool multijugador::choqueBloque()
{   choque=true;
    bool choq=choque;
    choque=false;
    return  choq;

}

