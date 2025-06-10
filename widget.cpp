#include "widget.h"
#include "./ui_widget.h"

#include <QDebug>

#include "custombutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    CustomButton* btn = new CustomButton(this);
    btn->setText("Button");
    btn->resize(100, 50);
    connect(btn, &CustomButton::clicked, [](){
      qDebug() << "Button clicked";
    });
}

Widget::~Widget(){
    delete ui;
}

