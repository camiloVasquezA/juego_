#include "arkanoid.h"
#include "my_scena.h"
#include <QGraphicsView>
#include <QMessageBox>

Arkanoid::Arkanoid(int niv,QGraphicsView *graphicsV, QObject *parent)
    :QObject (parent)
{
    mScene=new my_scena(this);
    multi=new multijugador(this);
    nivel=niv;


    if(nivel==1)

        graphicsV->setScene(mScene);
    else
         graphicsV->setScene(multi);



}

void Arkanoid::starGame()
{
   mScene->startScene( );
}

void Arkanoid::stopGame()
{
    mScene->stopScene();
}
