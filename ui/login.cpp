#include "login.h"

login::login(QWidget* parent) :
    QWidget(parent)
{
    url_layout=new QHBoxLayout();
    url_text=new QLabel(this);
    url_text->setText("网　址");
    url_box=new QLineEdit(this);
    url_box->setText("http://jwmis.school.edu.cn/jwweb");
    url_text->setBuddy(url_box);
    url_layout->addWidget(url_text);
    url_layout->addWidget(url_box);

    //this->setwid
    username_layout=new QHBoxLayout();
    username_text=new QLabel(this);
    username_text->setText("用户名");
    username_box=new QLineEdit(this);
    username_text->setBuddy(username_box);
    username_layout->addWidget(username_text);
    username_layout->addWidget(username_box);

    password_layout=new QHBoxLayout();
    password_text=new QLabel(this);
    password_text->setText("密　码");
    password_box=new QLineEdit(this);
    password_box->setEchoMode(QLineEdit::Password);//设置显示样式为密码
    password_text->setBuddy(password_box);
    password_layout->addWidget(password_text);
    password_layout->addWidget(password_box);

    //info_layout=new QHBoxLayout();
    info=new QLabel(this);
    info->setText("请在这里设置好信息，在需要时会弹出验证码窗口以完成登陆,设置完毕后返回主菜单去选择你要的功能吧、注意网址最后请不要加斜杠否则可能出现问题");
    //info_layout->addWidget(info);

    return_button=new QPushButton(this);
    return_button->setText("返回主菜单");
    QObject::connect(return_button,SIGNAL(clicked(bool)),this,SLOT(_on_return()));

    main_layout=new QVBoxLayout(this);
    main_layout->addStretch(10);
    main_layout->addLayout(url_layout);
    main_layout->addStretch(1);
    main_layout->addLayout(username_layout);
    main_layout->addStretch(1);
    main_layout->addLayout(password_layout);
    main_layout->addStretch(1);
    main_layout->addWidget(info);
    info->setWordWrap(true);
    main_layout->addStretch(1);
    main_layout->addWidget(return_button);
    main_layout->addStretch(10);

    url_cache="";
    username_cache="";
    password_cache="";
    _is_update=false;

    /*username_text->setGeometry(2,2,50,20);
    username_box->setGeometry(54,2,this->width()-56,20);
    password_text->setGeometry(2,24,50,20);
    password_box->setGeometry(54,24,this->width()-56,20);
    login_button->setGeometry(4,46,this->width()-8,40);*/
}

QString login::url(){
    return this->url_box->text();
}
QString login::username(){
    return this->username_box->text();
}
QString login::password(){
    return this->password_box->text();
}

void login::_on_return(){
    if(url_box->text()!=url_cache||username_box->text()!=username_cache||password_box->text()!=password_cache){
        _is_update=true;
        url_cache=url_box->text();
        username_cache=username_box->text();
        password_cache=password_box->text();
    }
    on_return();
}

login::~login()
{
}
bool login::is_update(bool reset/*=true*/){
    if(_is_update){
        if(reset){
            _is_update=false;
        }
        return true;
    }else{
        return false;
    }
}
