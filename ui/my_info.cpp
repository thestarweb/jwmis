#include "my_info.h"
#include <QDebug>

my_info::my_info(QWidget *parent) : QWidget(parent)
{
    root=new QVBoxLayout(this);

    root->addStretch();

    return_button=new QPushButton();
    return_button->setText("返回主菜单");
    QObject::connect(return_button,SIGNAL(clicked(bool)),this,SLOT(_on_return()));
    root->addWidget(return_button);

    root->addStretch();
}
void my_info::set_info(QString html){
    qDebug(qUtf8Printable(html));
    qDebug(qUtf8Printable(t));
}
void my_info::showEvent(QShowEvent *){
    jwweb_net::get()->get_info();
    t="'s'";
}
void my_info::_on_return(){
    on_return();
}
