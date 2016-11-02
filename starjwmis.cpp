#include "starjwmis.h"
#include <QDebug>

//单例模式
starJwmis* starJwmis::selfobj=NULL;
starJwmis* starJwmis::get(){
    if(selfobj==NULL) selfobj=new starJwmis();
    return selfobj;
}

starJwmis::starJwmis(QWidget *parent) :
    QWidget(parent)
{


    setWindowTitle("教务管理系统辅助客户端-");
    menu_ui=new menu(this);
    QObject::connect(menu_ui,SIGNAL(on_login_click()),this,SLOT(to_login_ui()));
    QObject::connect(menu_ui,SIGNAL(on_info_click()),this,SLOT(to_info_ui()));
    now_ui=menu_ui;

    login_ui=new login(this);
    QObject::connect(login_ui,SIGNAL(on_return()),this,SLOT(to_menu_ui()));
    login_ui->hide();

    my_info_ui=new my_info(this);
    QObject::connect(my_info_ui,SIGNAL(on_return()),this,SLOT(to_menu_ui()));
    my_info_ui->hide();

    root_layout=new QVBoxLayout(this);
    //root_layout->addLayout(top_layout);
    root_layout->addWidget(menu_ui);
    root_layout->addWidget(login_ui);

}

QString starJwmis::url(){
    return login_ui->url();
}
QString starJwmis::username(){
    return login_ui->username();
}
QString starJwmis::password(){
    return login_ui->password();
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
void starJwmis::to_info_ui(){
    now_ui->hide();
    my_info_ui->show();
    now_ui=my_info_ui;
}

starJwmis::~starJwmis()
{
}
