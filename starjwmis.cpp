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
    //main_layout=new QHBoxLayout();
    //main_layout->addWidget(uis[0]);
    login_ui=new login(this);
    QObject::connect(login_ui,SIGNAL(on_return()),this,SLOT(to_menu_ui()));
    login_ui->hide();
    my_info_ui=new my_info(this);
    my_info_ui->hide();

    root_layout=new QVBoxLayout(this);
    //root_layout->addLayout(top_layout);
    root_layout->addWidget(menu_ui);
    root_layout->addWidget(login_ui);


    http* h=new http("http://www.thestarweb.cn/");
    h->set_head("t","123");
    h->exec("","test");
    QObject::connect(h,SIGNAL(onresponse(http_response*)),this,SLOT(test(http_response*)));
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

void starJwmis::test(http_response* r){
    qDebug("%s",qUtf8Printable(r->content));
}

starJwmis::~starJwmis()
{
}
