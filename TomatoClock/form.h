#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPoint>
#include <QTimer>
#include <QMouseEvent>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    void mouseDoubleClickEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);

    QPoint relativePos;

public slots:
    void mouseClick();

private:
    Ui::Form *ui;

    QTimer *timer;
    int isAutoHide();
    int isHide();
    void hideWidge(int);
    void showWidge(int);
    int deskWidth;
};

#endif // FORM_H
