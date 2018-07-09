#include "tomatoclock.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QMessageBox>


void connectTask()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");//mysql的地址
    db.setPort(3306);
    db.setDatabaseName("todolist");//连接的数据库名称
    db.setUserName("root");//mysql登录名
    db.setPassword("");//mysql密码
    if(db.open())
     {
         qDebug()<<"success!";
         qDebug()<<db.driverName();
     }
    else
    {
         qDebug()<<"failed";
    }
}

int main(int argc, char *argv[])
{

    connectTask();

    QApplication a(argc, argv);
    TomatoClock w;
    w.show();

    return a.exec();
}
