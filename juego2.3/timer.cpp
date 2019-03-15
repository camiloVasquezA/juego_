#include "timer.h"



Timer::Timer(int miliseconds, QObject *parent)
    :QThread (parent)
{
    mMiliseconds=miliseconds;
}

void Timer::run()
{
    while(true){
        emit timeOut();
        QThread::msleep(mMiliseconds);
    }
}
