#include "login.h"

login::login(QWidget* parent) :
    QWidget(parent)
{
    //this->setwid
    username_text=new QLabel(this);
    username_text->setText("用户名");
    username_box=new QLineEdit(this);
    password_text=new QLabel(this);
    password_text->setText("密　码");
    password_box=new QLineEdit(this);
    password_box->setEchoMode(QLineEdit::Password);
    login_button=new QPushButton(this);
    login_button->setText("登陆");
    username_text->setGeometry(2,2,50,20);
    username_box->setGeometry(54,2,this->width()-56,20);
    password_text->setGeometry(2,24,50,20);
    password_box->setGeometry(54,24,this->width()-56,20);
    login_button->setGeometry(4,46,this->width()-8,40);
}

login::~login()
{
}
