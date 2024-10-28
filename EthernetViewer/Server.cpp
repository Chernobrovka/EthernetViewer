#include "Server.h"
#include <QDataStream>

Server::Server(){
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "Start";
    }
    else {
        qDebug() << "Error";
    }
    next_block_size = 0;
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok){
        qDebug() << "read...";
        //QString str;
        //in >> str;
        //qDebug() << str;
        for (;;){
            if (next_block_size == 0){
                qDebug() << "nextBlockSize = 0";
                if (socket->bytesAvailable() < 2){
                    qDebug() << "Data < 2, break";
                    break;
                }
                in >> next_block_size;
            }
            if (socket->bytesAvailable() < next_block_size){
                qDebug() << "Data not full, break";
                break;
            }
            QString str;
            in >> str;
            next_block_size = 0;
            qDebug() << str;
            sendToClient(str);
            break;
        }
    }
    else {
        qDebug() << "DataStream error";
    }
}

void Server::sendToClient(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << qint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    //socket->write(Data);
    for (int i = 0; i < Sockets.size(); i++){
        Sockets[i]->write(Data);
    }
}
