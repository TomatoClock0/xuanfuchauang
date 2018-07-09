#ifndef MANAGETASKS_H
#define MANAGETASKS_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class managetasks;
}

class managetasks : public QDialog
{
    Q_OBJECT

public:
    explicit managetasks(QWidget *parent = 0);
    QString worktimeStr;
    QString relaxtimeStr;
    ~managetasks();
    void myShow();

signals:
    //! 自定义的信号，只需要有函数声明不需要编写函数实现
    //! const QString& inputData
    void manage_delete_com();
    void manage_clear_com();

private slots:
    //void on_pushButton_clicked();

    void on_m_Cancel_clicked();

    void on_m_delete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_m_clear_clicked();

    void on_m_OK_clicked();

private:
    Ui::managetasks *ui;
    QStandardItemModel *model;
    QString the_task_name;
};

#endif // MANAGETASKS_H
