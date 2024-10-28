#include "Client.h"
#include <QTcpSocket>
#include <QDataStream>

Client::Client(){
    socket = new QTcpSocket();
    next_block_size = 0;
}

void Client::connectButtonCallback(void){
    socket->connectToHost("127.0.0.1", 2323);
}

void Client::slotReadyRead(void){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok){
        //QString str;
        //in >> str;
        //ui->textBrowser->append(str);
        for (;;){
            if (next_block_size == 0){
                if (socket->bytesAvailable() < 2){
                    break;
                }
                in >> next_block_size;
            }
            if (socket->bytesAvailable() < next_block_size){
                break;
            }
            QString str;
            in >> str;
            next_block_size = 0;
            //ui->textBrowser->append(str);
        }
    }
    else {

    }
}

void Client::sendToServer(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << qint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}
