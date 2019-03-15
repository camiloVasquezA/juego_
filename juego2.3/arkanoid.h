#ifndef ARKANOID_H
#define ARKANOID_H
#include "my_scena.h"
#include "multijugador.h"
#include <QObject>

class my_scena;
class multijugador;
class QGraphicsView;

class Arkanoid: public QObject
{
public:
    Arkanoid(int nivel,QGraphicsView *graphicsV, QObject *parent=nullptr);
    void starGame();
    void stopGame();
    bool getperdio(){return perdio;}

  my_scena* getscena(){

      return  mScene;
}

  multijugador* getmulti(){
      return multi;
  }

  void setnivel(int niv){
      nivel=niv;
  }


private:
//    my_scena *mScene;
    int vidas=3;
    int nivel;
    bool perdio=false;
    my_scena *mScene;
    multijugador *multi;



};

#endif // ARKANOID_H
