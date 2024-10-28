#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cstdbool>

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

private:
    Ui::MainWindow *ui;


    void connectSlots(void);

    void ethernetComboBoxInit(void);
    void uartComboBoxInit(void);


    QThread *tcp_socket_thread;

    bool is_ethernet_connection = false;
private slots:
    void onEthernetConnectButtonClicked();
    void onUartConnectButtonClicked();
};
#endif // MAINWINDOW_H
