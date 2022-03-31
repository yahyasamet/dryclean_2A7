#ifndef MESSENGERSOCKET_H
#define MESSENGERSOCKET_H

#include <QTcpSocket>




class MessengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MessengerSocket(qintptr handle, QObject *parent = nullptr);
signals:
    void ReadyRead(MessengerSocket *);
    void StateChanged(MessengerSocket *, int);
};

#endif // MESSENGERSOCKET_H
