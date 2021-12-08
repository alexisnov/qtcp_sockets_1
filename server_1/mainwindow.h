#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void newMessage(const QString& str);

private slots:
    void newConnection();//Новое соединение
    void appendToSocketList(QTcpSocket* socket);//добавление в список соединений
    void readSocket();//Получение данных
    void discardSocket();//Разрыв соединения
    void displayMessage(const QString& str); //Отображение сообщения
    void sendMessage(QTcpSocket* socket); //Отправка сообщения

private:
    Ui::MainWindow *ui;
    QTcpServer* m_server;//TCP-сервер
    QSet<QTcpSocket*> connection_set;//Клиенты - список соединений
};
#endif // MAINWINDOW_H
