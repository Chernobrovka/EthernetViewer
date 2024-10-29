#include "Uart.h"

Uart::Uart(QSerialPort *serialPort)
    : serialPort(serialPort)
{
    connect(serialPort, &QSerialPort::readyRead, this, &Uart::readData);
}

void Uart::writeData(const QByteArray &data) {
    serialPort->write(data);
    serialPort->waitForBytesWritten(-1);
}

void Uart::readData() {
    QByteArray data = serialPort->readAll();
    emit dataReceived(data);
}
