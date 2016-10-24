#include "starjwmis.h"

starJwmis::starJwmis(QWidget *parent) :
    QWidget(parent)
{


    setWindowTitle("教务管理系统辅助客户端-");
    menu_ui=new menu(this);
    QObject::connect(menu_ui,SIGNAL(on_login_click()),this,SLOT(to_login_ui()));
    now_ui=menu_ui;
    //main_layout=new QHBoxLayout();
    //main_layout->addWidget(uis[0]);
    login_ui=new login(this);
    QObject::connect(login_ui,SIGNAL(on_return()),this,SLOT(to_menu_ui()));
    login_ui->hide();

    root_layout=new QVBoxLayout(this);
    //root_layout->addLayout(top_layout);
    root_layout->addWidget(menu_ui);
    root_layout->addWidget(login_ui);
}

void starJwmis::to_menu_ui(){
    now_ui->hide();
    menu_ui->show();
    now_ui=menu_ui;
}
void starJwmis::to_login_ui(){
    now_ui->hide();
    login_ui->show();
    now_ui=login_ui;
}

starJwmis::~starJwmis()
{
}
