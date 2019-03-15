#ifndef TIMER_H
#define TIMER_H
#include <QThread>

class Timer: public QThread
{
    Q_OBJECT
public:
    Timer(int miliseconds,QObject *parent=nullptr);
signals:
    void timeOut();
protected:
    void run() override;
private:
    int mMiliseconds;


};

#endif // TIMER_H
