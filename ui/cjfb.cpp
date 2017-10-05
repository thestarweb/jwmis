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

    QObject::connect(jwweb_net::get(),SIGNAL(down_task(QString,QByteArray)),this,SLOT(net_cb(QString,QByteArray)));
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
void cjfb::net_cb(QString task,QByteArray bytes){
    if(task=="got_cjfb_pre"){
        sel->clear();
        sel->addItem("入学以来","");
        QRegExp* reg=new QRegExp("Col1.([0-9]+).='([0-9]+)';Col2.([0-9]+).='([0-9]+)';Col3.([0-9]+).='([^']+)';");
        QString l="";
        for(int i=0;(i=reg->indexIn(QString::fromLocal8Bit(bytes),i)+1)!=0;){
            if(reg->cap(2)!=l){
                sel->addItem(" "+reg->cap(2)+"学年",reg->cap(2));
                l=reg->cap(2);
            }
            sel->addItem("  "+reg->cap(6),reg->cap(2)+"."+reg->cap(4));
        }
    //
    }
}
