#ifndef CNETWORKRECEIVER_H
#define CNETWORKRECEIVER_H

#include <QObject>
#include <QTcpSocket>

#include "cgraphdrawer.h"

#define SERVER_TCP_PORT 15
#define CONNETION_WAIT_TIME 2000

class CNetworkReceiver : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkReceiver(QObject *parent = nullptr);
    ~CNetworkReceiver();
    bool tryConnectToServer(QString Ip);
    void setGraphDrawer(CGraphDrawer* newGraphDrawer);

    void disconnectFromServer();

private:
    QTcpSocket* socket;
    CGraphDrawer* graphDrawer;

public slots:
    void onReadyRead();
    void onDisconnect();

signals:

};

#endif // CNETWORKRECEIVER_H
