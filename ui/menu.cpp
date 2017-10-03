#include "menu.h"

menu::menu(QWidget *parent) : QWidget(parent)
{
    main_layout=new QVBoxLayout(this);

    login_button=new QPushButton(this);
    login_button->setText("登陆信息");
    QObject::connect(login_button,SIGNAL(clicked(bool)),this,SLOT(_on_login_click()));

    my_info_button=new QPushButton(this);
    my_info_button->setText("我的信息");
    QObject::connect(my_info_button,SIGNAL(clicked(bool)),this,SLOT(_on_info_click()));

    cjfb_button=new QPushButton(this);
    cjfb_button->setText("成绩分布");
    QObject::connect(cjfb_button,SIGNAL(clicked(bool)),this,SLOT(_on_cjfb_click()));

    main_layout->addStretch(9);
    main_layout->addWidget(login_button);
    main_layout->addStretch(1);
    main_layout->addWidget(my_info_button);
    main_layout->addStretch(1);
    main_layout->addWidget(cjfb_button);
    main_layout->addStretch(11);

}
void menu::_on_login_click(){
    on_login_click();
}
void menu::_on_info_click(){
    on_info_click();
}
void menu::_on_cjfb_click(){
    on_cjfb_click();
}

