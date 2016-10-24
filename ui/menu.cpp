#include "menu.h"

menu::menu(QWidget *parent) : QWidget(parent)
{
    main_layout=new QVBoxLayout(this);

    login_button=new QPushButton(this);
    login_button->setText("登陆信息");
    QObject::connect(login_button,SIGNAL(clicked(bool)),this,SLOT(_on_login_click()));

    my_info_button=new QPushButton(this);
    my_info_button->setText("我的信息");

    main_layout->addStretch(9);
    main_layout->addWidget(login_button);
    main_layout->addStretch(1);
    main_layout->addWidget(my_info_button);
    main_layout->addStretch(11);

}
void menu::_on_login_click(){
    on_login_click();
}

