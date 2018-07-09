#ifndef ADDTASKS_H
#define ADDTASKS_H

#include <QDialog>

namespace Ui {
class AddTasks;
}

class AddTasks : public QDialog
{
    Q_OBJECT

public:

    explicit AddTasks(QWidget *parent = 0);
    ~AddTasks();
    QString lineStr;
    QString textStr;

signals:
    //! 自定义的信号，只需要有函数声明不需要编写函数实现
    //! const QString& inputData
    void inputCompleted();

private slots: 

    void on_OK_clicked();

    void on_Cancel_clicked();


private:
    Ui::AddTasks *ui;
    void append();

};

#endif // ADDTASKS_H
