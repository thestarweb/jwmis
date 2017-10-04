#include "cjfb.h"

cjfb::cjfb(QWidget *parent) : QWidget(parent)
{
    top=new QVBoxLayout(this);

    sel_layout=new QHBoxLayout();
    sel=new QComboBox(this);
    submit=new QPushButton(this);
    submit->setText("检索");
    QObject::connect(submit,SIGNAL(clicked(bool)),this,SLOT(on_submit()));
    sel_layout->addWidget(sel);
    sel_layout->addWidget(submit);

    return_button=new QPushButton(this);
    return_button->setText("返回");
    QObject::connect(return_button,SIGNAL(clicked(bool)),this,SLOT(_on_return()));

    top->addStretch(10);
    top->addLayout(sel_layout);
    top->addStretch(1);
    top->addWidget(return_button);
    top->addStretch(10);
}
void cjfb::showEvent(QShowEvent *){
    jwweb_net::get()->add_task("cjfb_pre");
}
void cjfb::_on_return(){
    on_return();
}
void cjfb::on_submit(){
    //
}
