#include "my_info.h"
#include <QDebug>

my_info::my_info(QWidget *parent) : QWidget(parent)
{
    //
}
void my_info::set_info(QString html){
    qDebug(qUtf8Printable(html));
    qDebug(qUtf8Printable(t));
}
void my_info::showEvent(QShowEvent *){
    jwweb_net::get()->get_info();
    t="'s'";
}
