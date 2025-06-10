#include "widget.h"

#include <QDebug>

#include "custombutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    CustomButton* btn = new CustomButton(this);
    btn->setText("Button");
    btn->resize(100, 50);
    connect(btn, &CustomButton::clicked, [](){
      qDebug() << "Button clicked";
    });
     setWindowTitle("OtusButton");
}

Widget::~Widget(){
}

