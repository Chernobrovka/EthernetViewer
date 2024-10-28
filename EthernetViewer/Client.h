#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client
{
public:
    Client();
    void connectButtonCallback(void);

private:
    void sendToServer(QString str);

    QTcpSocket *socket;
    QByteArray Data;
    quint16 next_block_size;

public slots:
    void slotReadyRead();
};

#endif // CLIENT_H
