#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cstdbool>

#include <QtSerialPort/QtSerialPort>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort *serialPort = new QSerialPort;

private:
    Ui::MainWindow *ui;


    void connectSlots(void);

    void ethernetComboBoxInit(void);
    void uartComboBoxInit(void);
    void interfaceStateInit(void);

    QThread *tcp_socket_thread;


    bool is_ethernet_connection = false;
    bool is_uart_connected      = false;
private slots:
    void onEthernetConnectButtonClicked();
    void onUartConnectButtonClicked();
    void uartPortUpdate(void);
};
#endif // MAINWINDOW_H
