#include "MessengerSocket.h"

MessengerSocket::MessengerSocket(qintptr handle, QObject *parent) : QTcpSocket(parent)
{
    setSocketDescriptor(handle);

    connect(this, &MessengerSocket::readyRead, [&]() {
        emit ReadyRead(this);
    });


    connect(this, &MessengerSocket::stateChanged, [&](int S) {
        emit StateChanged(this, S);

    });
}

