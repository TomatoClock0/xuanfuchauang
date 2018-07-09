#ifndef TOMATOCLOCK_H
#define TOMATOCLOCK_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>
#include "addtasks.h"
#include "managetasks.h"
#include <QMainWindow>
#include <QTabWidget>
#include <QTabBar>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOption>
#include <QtGui>

class CustomTabStyle : public QProxyStyle
{
public:
QSize sizeFromContents(ContentsType type, const QStyleOption *option,
const QSize &size, const QWidget *widget) const
{
QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
if (type == QStyle::CT_TabBarTab)
{
s.transpose();
   s.rwidth()=100;
   s.rheight()=100;
}
return s;
}


void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
if (element == CE_TabBarTabLabel)
{
if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
{
QStyleOptionTab opt(*tab);
opt.shape = QTabBar::RoundedNorth;
//opt.text = tr("Hello");
//QIcon icon(":/Resources/icon2.ico");
//opt.icon = icon;
opt.palette.setCurrentColorGroup(QPalette::Disabled);
opt.state |= QStyle::State_Sunken;
QProxyStyle::drawControl(element, &opt, painter, widget);
return;
}
}


QProxyStyle::drawControl(element, option, painter, widget);
}
};

namespace Ui {
class TomatoClock;
}

class TomatoClock : public QMainWindow
{
    Q_OBJECT

public:
    void new_Table();
    void tasks_Show();
    void search();
    QString worktimeStr;
    QString relaxtimeStr;
    int workTime;
    int relaxTime;

    explicit TomatoClock(QWidget *parent = 0);
    ~TomatoClock();

    int restofTime=0;

    int clock_status = 0;//0--not working
    //1--working
    //2--relaxing
    //3--stopping
    //4--prepared

private slots:

    void on_Add_clicked();
    void on_Manage_clicked();
    void on_Done_clicked();
    void lcdnumberDisplay();

    void myslot1();
    void myslot2();
    void showslot();
    void readData();
    void writeData();

    void on_Start_clicked();
    void on_Stop_clicked();
    void on_Finish_clicked();


    void on_addlabel_clicked(const QModelIndex &);


    void on_completed_Clear_clicked();
    void on_completed_Delete_clicked();

    void on_completedlabel_clicked(const QModelIndex &index);

    void on_relax_time_editingFinished();

    void on_work_time_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::TomatoClock *ui;

    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;

    QStandardItemModel *model1;
    QStandardItemModel *model2;

    AddTasks *add_tasks;
    managetasks *manage_tasks;

    QString completed_tasks_name;

};

#endif // TOMATOCLOCK_H
