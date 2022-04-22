#ifndef MESSENGERSERVER_H
#define MESSENGERSERVER_H

#include <QTcpServer>



class MessengerSocket;

class MessengerServer : public QTcpServer
{
public:
    MessengerServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private:
    QList<MessengerSocket *> mSockets;
};

#endif // MESSENGERSERVER_H
