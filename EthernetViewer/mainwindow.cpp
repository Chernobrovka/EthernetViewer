#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QtSerialPort/QSerialPort>

#include "Server.h"
#include "Client.h"

static QString ethernet_connection_types[] = {"Server", "Client"};
static const int uart_baudrates[] = {1200,4800,9600,19200,38400,57600,115200};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ethernetComboBoxInit();
    uartComboBoxInit();
    interfaceStateInit();

    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlots(void){
// TODO: Сделать чтобы если нажиалось connect server, то создавался обьект сервер в отдельном потоке
    connect(ui->connectButtonEthernet, &QPushButton::clicked, this, &MainWindow::onEthernetConnectButtonClicked);
    connect(ui->comboBoxUartPort, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::uartPortUpdate);
}

void MainWindow::ethernetComboBoxInit(void){
    ui->comboBoxEthernetConnectionTypes->addItem(ethernet_connection_types[0]);
    ui->comboBoxEthernetConnectionTypes->addItem(ethernet_connection_types[1]);
}

void MainWindow::uartComboBoxInit(void){
    int num_elements = sizeof(uart_baudrates) / sizeof(uart_baudrates[0]);
    for (int i = 0; i < num_elements; i++)
        ui->comboBoxUartBaudrate->addItem(QString::number(uart_baudrates[i]));
    ui->comboBoxUartBaudrate->setCurrentText(QString::number(115200));
    uartPortUpdate();
}

void MainWindow::uartPortUpdate(void){
    qDebug() << "Uart Com port update:\n";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxUartPort->addItem(info.portName());
    }
}

void MainWindow::interfaceStateInit(void){
    ui->textBrowserEthernet->setEnabled(false);
    ui->ethernetSendButton->setEnabled(false);
    ui->textBrowserUart->setEnabled(false);
}

void MainWindow::onEthernetConnectButtonClicked(void){
    QString text = ui->comboBoxEthernetConnectionTypes->currentText();
    if (!is_ethernet_connection){
        is_ethernet_connection = true;
        if (text == "Server"){
            Server *server = new Server();
            tcp_socket_thread = new QThread();
            server->moveToThread(tcp_socket_thread);

            // TODO: fix
            ui->lineEdit->setEnabled(false);
            ui->textBrowserEthernet->setEnabled(false);
            ui->ethernetSendButton->setEnabled(false);
            ui->connectButtonEthernet->setText("Stop");
        }
        else if (text == "Client"){

        }
    }
    else{
        is_ethernet_connection = false;
        if (text == "Server"){
            // Вызвать деструктор

            ui->lineEdit->setEnabled(true);
            ui->textBrowserEthernet->setEnabled(true);
            ui->ethernetSendButton->setEnabled(true);
            ui->connectButtonEthernet->setText("Start");
        }
        else if (text == "Client"){

        }
    }

}

void MainWindow::onUartConnectButtonClicked(void){
    if (!is_uart_connected){
        serialPort->setPortName(ui->comboBoxUartPort->currentText());
        serialPort->setBaudRate(ui->comboBoxUartBaudrate->currentText().toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        if(serialPort->open(QIODevice::ReadWrite)) {
            is_uart_connected = true;
            ui->textBrowserUart->setEnabled(true);
            ui->connectButtonUart->setText("Disconnect");
        }
    }
    else {
        serialPort->clear();
        serialPort->close();
        is_uart_connected = false;
        ui->connectButtonUart->setText("Connect");
    }
}
