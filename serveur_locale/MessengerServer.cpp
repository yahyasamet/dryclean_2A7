#include "MessengerServer.h"
#include "MessengerSocket.h"
#include <QTextStream>
#include <QDebug>


namespace AslihanAkbiyik
{


MessengerServer::MessengerServer(QObject *parent) : QTcpServer(parent)
{

}

bool MessengerServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);

}

void MessengerServer::incomingConnection(qintptr handle)
{
    qDebug() << "Client connected with handle:" << handle;
    auto socket = new MessengerSocket(handle, this);
    mSockets << socket;

    for(auto i : mSockets) {
        QTextStream T(i);
        T << "Server: It has connected" << handle;
        i->flush();
    }


    connect(socket, &MessengerSocket::ReadyRead, [&](MessengerSocket *S)
    {
        qDebug() << "ReadyRead";
        QTextStream T(S);
        auto text = T.readAll();

        for(auto i : mSockets)
        {
            QTextStream K(i);
            K << text;
            i->flush();
        }
    });

    connect(socket, &MessengerSocket::StateChanged, [&] (MessengerSocket *S, int ST) {
                 qDebug() << "StateChanged with handle:" << S->socketDescriptor();
                 if(ST == QTcpSocket::UnconnectedState) {
                    qDebug() << "Unconnected state with handle:" << S->socketDescriptor();
                    mSockets.removeOne(S);
                    for(auto i : mSockets) {
                        QTextStream K(i);
                        K << "Server: Client"
                          << S->socketDescriptor()
                          << "It has disconnected";
                        i->flush();
                }
              }
            });
}
} // end of namespace
