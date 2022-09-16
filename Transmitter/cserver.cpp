#include "cserver.h"

CServer::CServer()
{

}

bool CServer::tryStartServer()
{
    return this->listen(QHostAddress::Any, SERVER_TCP_PORT);
}

void CServer::sendData(QByteArray data)
{
    for(const auto& socket: sockets)
    {
        socket->write(data);
    }

}

void CServer::incomingConnection(qintptr socketDesc)
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDesc);

    connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisc()));

    sockets.push_back(socket);
}

void CServer::onSocketDisc()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    if(!socket)
        return;

    auto sockForErase = std::find(sockets.begin(), sockets.end(), socket);
    if(sockForErase != sockets.end())
    {
        sockets.erase(sockForErase);
    }
    socket->deleteLater();
}

