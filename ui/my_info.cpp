#include "my_info.h"
void set_info_test(QString h){
    //
}

my_info::my_info(QWidget *parent) : QWidget(parent)
{
    jwweb_net *j=jwweb_net::get();
    j->get_info(&set_info_test);
}
void my_info::set_info(QString html){
    //
}
