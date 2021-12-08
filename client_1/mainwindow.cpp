#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::LocalHost,8080);
    if(socket->waitForConnected()){
        ui->statusbar->showMessage("Соединён с сервером");

    }
    else{
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    socket->close();
    socket->deleteLater();
    delete ui;
}

