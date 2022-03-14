#ifndef MESSENGERSOCKET_H
#define MESSENGERSOCKET_H

#include <QTcpSocket>


namespace AslihanAkbiyik
{

class MessengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MessengerSocket(qintptr handle, QObject *parent = nullptr);
signals:
    void ReadyRead(MessengerSocket *);
    void StateChanged(MessengerSocket *, int);
};
} //end namespace AslihanAkbiyik
#endif // MESSENGERSOCKET_H
