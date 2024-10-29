#ifndef UART_H
#define UART_H


#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>

class Uart : public QObject
{
    Q_OBJECT
public:
    Uart(QSerialPort *serialPort);

public slots:
    void writeData(const QByteArray &data);
    void readData();

signals:
    void dataReceived(const QByteArray &data);

private:
    QSerialPort *serialPort;
};

#endif // UART_H
