#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>

#include "Server.h"

static QString ethernet_connection_types[] = {"Server", "Client"};
static const int uart_baudrates[] = {1200,4800,9600,19200,38400,57600,115200};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ethernetComboBoxInit();
    uartComboBoxInit();

    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::connectSlots(void){
// TODO: Сделать чтобы если нажиалось connect server, то создавался обьект сервер в отдельном потоке
    connect(ui->connectButtonEthernet, &QPushButton::clicked, this, &MainWindow::onEthernetConnectButtonClicked);
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
}

void MainWindow::onEthernetConnectButtonClicked(void){
    QString text = ui->comboBoxEthernetConnectionTypes->currentText();
    if (is_ethernet_connection == false){
        is_ethernet_connection = true;
        if (text == "Server"){
            Server *server = new Server();
            tcp_socket_thread = new QThread();
            server->moveToThread(tcp_socket_thread);

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

}
