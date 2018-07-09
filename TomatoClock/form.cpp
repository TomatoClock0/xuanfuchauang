#include "form.h"
#include "ui_form.h"
#include "tomatoclock.h"
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QRect>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QBitmap>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QPixmap pix("7.png");
    ui->label->setPixmap(pix);

    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(pix));
    this->setPalette(palette);
    this->setMask(pix.mask());
    this->setAutoFillBackground(true);

    this->setAttribute(Qt::WA_TranslucentBackground, true);

    QDesktopWidget *deskWgt = QApplication::desktop();
    deskWidth = deskWgt->width();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mouseClick()));

    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::FramelessWindowHint);
}

Form::~Form()
{
    delete ui;
}

void Form::mouseClick()
{


    timer->stop();

}

void Form::mousePressEvent(QMouseEvent *event)
{


    if(event->button()==Qt::LeftButton)
    {
        relativePos = this->pos() - event->globalPos();
        timer->start(800);
    }
    if (event->button()==Qt::RightButton)
    {
        this->hide();
        this->close();
    }
}

void Form::mouseMoveEvent(QMouseEvent *event)
{

    timer->stop();
    this->move(event->globalPos()+relativePos);

}

void Form::mouseDoubleClickEvent(QMouseEvent *event)
{
    timer->stop();
    this->close();
    TomatoClock *window = new TomatoClock;
    window->show();
}

int Form::isAutoHide()
{
    if(this->pos().y() <= 5){
        return 1;
    }
    if(this->pos().x() <= 5){
        return 2;
    }
    if (this->pos().x()+this->size().width() >= deskWidth-5){
        return 3;
    }

    return 0;
}

int Form::isHide()
{
    if(this->pos().y() <= -15){
        return 1;
    }
    if(this->pos().x() <= -15){
        return 2;
    }
    if (this->pos().x()+this->size().width() >= deskWidth+15){
        return 3;
    }

    return 0;
}

void Form::hideWidge(int direction)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->pos(), this->size()));
    QRect rcEnd;
    if (direction == 1){
        rcEnd = QRect(this->x(), -this->height()/2, this->rect().width(), this->rect().height());
    }
    if (direction == 2){
        rcEnd = QRect(-this->width()/2, this->y(), this->size().width(), this->rect().height());
    }
    if(direction == 3){
        rcEnd = QRect(deskWidth - 40, this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();

}

void Form::showWidge(int direction)
{
    QPoint pos = this->pos();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(pos, this->size()));
    QRect rcEnd;
    if (direction == 1){
        rcEnd = QRect(this->x(), 0, this->size().width(), this->rect().height());
    }
    if (direction == 2){
        rcEnd = QRect(0, this->y(), this->size().width(), this->rect().height());
    }
    if (direction == 3){
        rcEnd = QRect(deskWidth - this->width(), this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void Form::leaveEvent(QEvent *event)
{

    int direction = isAutoHide();
    if(direction != 0){
        hideWidge(direction);
    }



}

void Form::enterEvent(QEvent *event)
{
    int direction = isHide();
    if (direction != 0){
        showWidge(direction);
    }

}
