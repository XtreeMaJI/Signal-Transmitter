#ifndef CSIGNALGENERATOR_H
#define CSIGNALGENERATOR_H

#include "cserver.h"

#include <QObject>
#include <QTimer>

#define TIMER_INTERVAL 50 //Интервал между срабатываниями таймера в миллисекундах
#define MILLISECONDS_IN_SECOND 1000
#define POINTS_INTERVAL 10 //Интервал по оси Х между точками на графике

class CSignalGenerator : public QObject
{
    Q_OBJECT
public:
    CSignalGenerator();
    ~CSignalGenerator();

    double  getSignalAtTime(double t);
    void    startGenerateSignal();
    void    setFrequency(double newFrequency);
    void    setAmplitude(double newAmplitude);
    void    setServer(CServer *newServer);

    bool    isGenerating;

public slots:
    void    onTimerUpdate();

private:
    QTimer*     timer;
    double      frequency;
    double      amplitude;
    double      timePassed;
    CServer*    server;

};

#endif // CSIGNALGENERATOR_H
