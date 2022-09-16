#include "csignalgenerator.h"

#include <QByteArray>

CSignalGenerator::CSignalGenerator() :
    isGenerating(false),
    timer(nullptr),
    frequency(1),
    amplitude(1),
    timePassed(0),
    server(nullptr)
{

}

CSignalGenerator::~CSignalGenerator()
{
    delete timer;
}

double CSignalGenerator::getSignalAtTime(double t)
{
    return amplitude*sin(t * frequency * 2 * M_PI / MILLISECONDS_IN_SECOND);
}

void CSignalGenerator::startGenerateSignal()
{
    timePassed = 0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
    timer->start(TIMER_INTERVAL);

    isGenerating = true;
}

void CSignalGenerator::setFrequency(double newFrequency)
{
    frequency = newFrequency;
}

void CSignalGenerator::setAmplitude(double newAmplitude)
{
    amplitude = newAmplitude;
}

void CSignalGenerator::setServer(CServer *newServer)
{
    server = newServer;
}

void CSignalGenerator::onTimerUpdate()
{
    double signalVal;

    QByteArray signalData;
    signalData.clear();

    for(int i = 0; i < TIMER_INTERVAL; i+=5)
    {
        signalVal = getSignalAtTime(timePassed + i);
        signalData.append(QByteArray::number(timePassed + i));
        signalData.append("|");
        signalData.append(QByteArray::number(signalVal));
        signalData.append("|");
    }

    server->sendData(signalData);

    timePassed += TIMER_INTERVAL;
}
