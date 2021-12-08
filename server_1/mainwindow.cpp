#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = new QTcpServer();

    if(m_server->listen(QHostAddress::Any,8080)){
        //Успешный запуск
        connect(this,&MainWindow::newMessage,this,&MainWindow::displayMessage);
        connect(m_server,&QTcpServer::newConnection,this,&MainWindow::newConnection);
        qDebug() << "Сервер запущен";
    }else{
        //Ошибка запуска сервера
        qDebug() << "Не удалось запустить сервер: " << m_server->errorString();
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    //Закрыть все соединения
    foreach(QTcpSocket* socket,connection_set){
        socket->close();
        socket->deleteLater();
    }
    m_server->close();
    m_server->deleteLater();

    delete ui;
}

void MainWindow::newConnection(){
    while(m_server->hasPendingConnections()){
        appendToSocketList(m_server->nextPendingConnection());
    }
}

void MainWindow::appendToSocketList(QTcpSocket* socket){
    connection_set.insert(socket);
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::readSocket);
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::discardSocket);
    ui->comboBox_clients->addItem(QString::number(socket->socketDescriptor()));
    displayMessage(QString("Клиент #%1 подключился").arg(socket->socketDescriptor()));
}

void MainWindow::readSocket(){

}

void MainWindow::discardSocket(){
    displayMessage(QString("Клиент #%1 отключился").arg(""));
}

void MainWindow::displayMessage(const QString& str){
    ui->textBrowser_messages->append(str);
}

void MainWindow::sendMessage(QTcpSocket *socket)
{

}
