#include "starjwmis.h"

starJwmis::starJwmis(QWidget *parent) :
    QWidget(parent)
{
    top_layout=new QHBoxLayout();
    login_info_button=new QPushButton(this);
    login_info_button->setText("登陆信息");
    my_info_button=new QPushButton(this);
    my_info_button->setText("我的信息");
    //top_layout->sets
    top_layout->addWidget(login_info_button);
    top_layout->addWidget(my_info_button);

    uis[0]=new login(this);
    setWindowTitle("教务管理系统辅助客户端-");
    main_layout=new QHBoxLayout();
    main_layout->addWidget(uis[0]);

    root_layout=new QVBoxLayout(this);
    root_layout->addLayout(top_layout);
    root_layout->addLayout(main_layout);
}

starJwmis::~starJwmis()
{
}
