#ifndef CSERVER_H
#define CSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#define SERVER_TCP_PORT 15

class CServer: public QTcpServer
{
    Q_OBJECT
public:
    CServer();

    bool tryStartServer();
    void sendData(QByteArray data);

private:
    std::vector<QTcpSocket*> sockets;

public slots:
    void incomingConnection(qintptr socketDesc);
    void onSocketDisc();

};

#endif // CSERVER_H
