#include "managetasks.h"
#include "ui_managetasks.h"
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

managetasks::managetasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managetasks)
{
    ui->setupUi(this);
    ui->m_delete->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->m_clear->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    model =new QStandardItemModel();
    model->setColumnCount(1);
    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("UNIFINISHED TASKS"));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->setColumnWidth(0,800);
    myShow();
}

void managetasks::myShow()
{
    QSqlQuery query;
    if(model->rowCount()!=0)
    {
        model->removeRows(0,model->rowCount());
    }
    bool success = query.exec("select *from information");
    if (success)
    {
        int i=0;
        while(query.next())
        {
            if(query.value(3).toString() == '1')//unfinished job
            {
               model->setItem(i,new QStandardItem(query.value(1).toString()));
               i++;
            }
        }
    }
}

managetasks::~managetasks()
{
    delete ui;
}

void managetasks::on_m_Cancel_clicked()
{
    this->close();
}

void managetasks::on_m_OK_clicked()
{
    this->close();
}


void managetasks::on_m_delete_clicked()
{
    QSqlQuery query;
    QString str2 = the_task_name;
    query.exec(QString("update information set conditions = 0 where line = '%1'")
               .arg(str2)
               );
    emit manage_delete_com();
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Delete!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    myShow();
}

void managetasks::on_tableView_clicked(const QModelIndex &index)
{
    the_task_name = index.data().toString();
}

void managetasks::on_m_clear_clicked()
{
    if(model->rowCount()!=0)
    {
        model->removeRows(0,model->rowCount());
    }
    QSqlQuery query;
    emit manage_clear_com();
    query.exec(QString("delete from information where conditions = 1 or conditions = 0"));
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Cleared!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    myShow();
}



