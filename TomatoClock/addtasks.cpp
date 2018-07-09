#include "addtasks.h"
#include "ui_addtasks.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>


AddTasks::AddTasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTasks)
{
    ui->setupUi(this);
}

AddTasks::~AddTasks()
{
    delete ui;
}

void AddTasks::append()
{
    QSqlQuery query;
    query.exec("select *from information");
    QString savesql = QString("insert into information");
    savesql += QString(" values(null,'%1','%2',1)").arg(ui->tasksname->text())
                .arg(ui->tasksdetail->toPlainText());
    bool ok = query.exec(savesql);
    if(ok){
        QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Success!");
        message.setIconPixmap(QPixmap("iccccon.PNG"));
        message.exec();
          }
    else{
        QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Failed....");
        message.setIconPixmap(QPixmap("iccccon.PNG"));
        message.exec();
        }
}

void AddTasks::on_OK_clicked()
{
    qDebug()<<"tasks_show";
    append();
    emit inputCompleted();
    ui->tasksdetail->setText(" ");
    ui->tasksname->setText(" ");
    close();
}

void AddTasks::on_Cancel_clicked()
{
    this->close();
}
