#ifndef NETWORKRECEIVER_H
#define NETWORKRECEIVER_H

#include <QObject>

class NetworkReceiver : public QObject
{
    Q_OBJECT
public:
    explicit NetworkReceiver(QObject *parent = nullptr);

private:
    void connectToServer();


signals:

};

#endif // NETWORKRECEIVER_H
