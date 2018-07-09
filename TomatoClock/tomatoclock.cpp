#include "tomatoclock.h"
#include "ui_tomatoclock.h"
#include "addtasks.h"
#include "managetasks.h"
#include "qstring.h"
#include "form.h"

#include <QTimer>
#include <QMessageBox>
#include <QtCore>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <vector>
#include <string>
#include <fstream>
#include <QTextStream>
#include <iostream>
#include <QFile>
using namespace std;

void TomatoClock::readData()
{
std::ifstream fin;
fin.open("works.txt",ifstream::in);
int work[2];
if(fin.fail())
{
    std::cout<<"File  open  error!";
}
else{
    int i=0;
    while(fin>>work[i]){
       cout<<work[i];
       i++;
    }
}
fin.close();
workTime=work[0];
relaxTime=work[1];
worktimeStr = QString("%1").arg(work[0]);
relaxtimeStr = QString("%1").arg(work[1]);
 ui->work_time->setText(worktimeStr);
 ui->relax_time->setText(relaxtimeStr);
}

void TomatoClock::writeData()
{
    qDebug()<<worktimeStr;
    qDebug()<<relaxtimeStr;
    int changetime[2];
     changetime[1]=relaxtimeStr.toInt();
     changetime[0] = worktimeStr.toInt();
    ofstream fout;
    fout.open("works.txt",ofstream::out);
    int i=0;
    while(i<2){
        fout<<changetime[i]<<endl;
        i++;
    }

    fout.close();
}


TomatoClock::TomatoClock(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::TomatoClock)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
    ui->tabWidget->setCurrentWidget(ui->Todolist);

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(myslot1()));
    timer2 = timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(myslot2()));
    timer3=new QTimer(this);
    connect(timer3,SIGNAL(timeout()), this, SLOT(lcdnumberDisplay()));
    add_tasks=new AddTasks;
    connect(add_tasks,SIGNAL(inputCompleted()),this,SLOT(showslot()));
    manage_tasks=new managetasks;
    connect(manage_tasks,SIGNAL(manage_delete_com()),this,SLOT(showslot()));
    connect(manage_tasks,SIGNAL(manage_clear_com()),this,SLOT(showslot()));


    ui->Start->setStyleSheet(tr("background-image: url(images/plays.jpg);"));
    ui->Stop->setStyleSheet(tr("background-image: url(images/stops.jpg);"));
    ui->Finish->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->completed_Delete->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->completed_Clear->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    ui->Add->setStyleSheet(tr("background-image: url(images/add.jpg);"));
    ui->Done->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->Manage->setStyleSheet(tr("background-image: url(images/manages.jpg);"));
    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);
    ui->label_2->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);
    ui->label_2->setPalette(pa);
    QPalette palette;
    palette.setBrush(QPalette::Text,Qt::red);
    ui->addlabel->setPalette(palette);
    ui->tasksdetail->setFont(QFont("Timers",20,QFont::Bold));
    new_Table();
    tasks_Show();
    readData();

}

TomatoClock::~TomatoClock()
{
    delete ui;
}


//add tasks
void TomatoClock::on_Add_clicked()
{
    add_tasks->show();
}

//manage tasks
void TomatoClock::on_Manage_clicked()
{
    manage_tasks->show();
    manage_tasks->myShow();
}

//the work/relax time has been setted already
void TomatoClock::on_Done_clicked()
{
    const int w = ui->work_time->text().toInt();
    const int r=ui->relax_time->text().toInt();
    workTime = w ;
    relaxTime = r ;
     writeData();
}


//**************clock**************
//show the warning
void TomatoClock::myslot1()
{
    lcdnumberDisplay();
    timer1->stop();
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Time's up!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    timer2->start(relaxTime*60000);
}
void TomatoClock::myslot2()
{
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Work!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    timer2->stop();
    timer1->start(workTime*60000);
}
void TomatoClock::showslot()
{
    tasks_Show();
}


//start to time
void TomatoClock::on_Start_clicked()
{
    if(clock_status==4)
    {
        clock_status = 1;
        restofTime=workTime*60;//单位为s
        timer1->start(workTime*60000);
        timer3->start(1000);
    }
    else if(clock_status==0)
    {
        QMessageBox message(QMessageBox::NoIcon,"TomatoClock","NO TASKS");
        message.setIconPixmap(QPixmap("iccccon.PNG"));
        message.exec();
    }
    else {}
}

void TomatoClock::on_Stop_clicked()
{
    if(clock_status==1){
    timer3->stop();
    timer1->stop();
    clock_status=3;
    }
    else if(clock_status==2){
        timer3->stop();
        timer1->stop();
        clock_status=3;
        }
    else if(clock_status==3){
        timer3->start(1000);
        timer1->start(restofTime*1000);
        clock_status=1;
    }
}
void TomatoClock::on_Finish_clicked()
{
    clock_status = 0;
    timer1->stop();
    timer2->stop();
    timer3->stop();
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Congratulations");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    search();
    ui->tabWidget->setCurrentWidget(ui->Todolist);
}

void TomatoClock::search()
{
    QSqlQuery query;
    QString str1 = ui->clock_tasksname->text();
    query.exec(QString("update information set conditions = 0 where line = '%1' and conditions = 1")
               .arg(str1)
               );
    tasks_Show();
}

void TomatoClock:: lcdnumberDisplay()
{
    ui->minute_clock->display(restofTime/60);
    ui->second_clock->display(restofTime%60);
    restofTime--;
   if(clock_status==1&&restofTime==0){
        restofTime=relaxTime*60;
    }
   if(clock_status==2&&restofTime==0){
        restofTime=workTime*60;
    }
}


void TomatoClock::new_Table()
{
    model1=new QStandardItemModel();
    model2 =new QStandardItemModel();
    model1->setColumnCount(1);
    model1->setHeaderData(0,Qt::Horizontal,QStringLiteral("UNIFINISHED TASKS"));
    ui->addlabel->setModel(model1);
    ui->addlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->addlabel->setColumnWidth(0,800);

    model2->setColumnCount(1);
    model2->setHeaderData(0,Qt::Horizontal,QStringLiteral("FINISHED TASKS"));
    ui->completedlabel->setModel(model2);
    ui->completedlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->completedlabel->setColumnWidth(0,800);
}


void TomatoClock::tasks_Show()
{
    if(model1->rowCount()!=0)
    {
        model1->removeRows(0,model1->rowCount());
    }
    if(model2->rowCount()!=0)
    {
        model2->removeRows(0,model2->rowCount());
    }
    QSqlQuery query;
    bool success = query.exec("select *from information");
    if (success)
    {
        int i=0;
        int j=0;
        while(query.next())
        {
            if(query.value(3).toString() == '0')//completed job
            {
                model2->setItem(j,new QStandardItem(query.value(1).toString()));
                j++;
            }
            else if(query.value(3).toString() == '1')//unfinished job
            {
                model1->setItem(i,new QStandardItem(query.value(1).toString()));
                i++;
            }
        }
    }
}


void TomatoClock::on_addlabel_clicked(const QModelIndex &index)
{
    int row = ui-> addlabel ->currentIndex().row();
    qDebug()<<row;
    QString str = index.data().toString();
    qDebug()<<str;
    ui->tabWidget->setCurrentWidget(ui->Clock);
    ui->clock_tasksname->setText(str);
    ui->clock_tasksid->setText(QString::number(row+1));
    clock_status=4;
}


void TomatoClock::on_completed_Clear_clicked()
{
    QSqlQuery query;
    query.exec(QString("delete from information where conditions = 0"));
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Cleared");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    tasks_Show();
}

void TomatoClock::on_completed_Delete_clicked()
{
    QSqlQuery query;
    query.exec(QString("delete from information where line = '%1' and conditions = 0")
               .arg(completed_tasks_name)
               );
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Deleted");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    tasks_Show();
}

void TomatoClock::on_completedlabel_clicked(const QModelIndex &index)
{
    completed_tasks_name=index.data().toString();
}

void TomatoClock::on_relax_time_editingFinished()
{
    QTextStream cout(stdout,QIODevice::WriteOnly);
    relaxtimeStr=ui->relax_time->text();
}

void TomatoClock::on_work_time_editingFinished()
{
    QTextStream cout(stdout,QIODevice::WriteOnly);
    worktimeStr=ui->work_time->text();
}

void TomatoClock::on_pushButton_clicked()
{
    Form *form = new Form;

    form->move(1000,800);
    form->show();
    this->hide();
    this->close();
}
