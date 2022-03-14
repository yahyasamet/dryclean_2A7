#ifndef MESSENGERSERVER_H
#define MESSENGERSERVER_H

#include <QTcpServer>

namespace AslihanAkbiyik
{

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
} //end of namespace AslihanAkbiyik

#endif // MESSENGERSERVER_H
