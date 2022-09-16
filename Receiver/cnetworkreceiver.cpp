#include "cnetworkreceiver.h"
#include "cstringhelper.h"

#include <QLineSeries>

CNetworkReceiver::CNetworkReceiver(QObject *parent)
    : QObject{parent}
{

}

CNetworkReceiver::~CNetworkReceiver()
{
    if(socket)
        delete socket;
}

void CNetworkReceiver::connectToServer(QString serverIp)
{
    socket = new QTcpSocket();
    socket->connectToHost(serverIp, SERVER_TCP_PORT);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

}

void CNetworkReceiver::setGraphDrawer(CGraphDrawer *newGraphDrawer)
{
    graphDrawer = newGraphDrawer;
}

void CNetworkReceiver::onReadyRead()
{
    QByteArray data;
    data.clear();
    data = socket->readAll();
    QString dataStr(data);

    std::vector<double> dataAsNumbers = CStringHelper::parseQStringToDoubleVec(dataStr, '|');

    //Чётные числа - значения по оси Х, нечётные - по оси У
    for(size_t i = 0; i < dataAsNumbers.size(); i+=2)
    {
        if(i + 1 > dataAsNumbers.size())
            break;

        graphDrawer->addPointToChart(dataAsNumbers[i], dataAsNumbers[i+1]);
    }
}

void CNetworkReceiver::onDisconnect()
{
    socket->deleteLater();
}
