#include "my_info.h"
#include <QDebug>

my_info::my_info(QWidget *parent) : QWidget(parent)
{
    root=new QVBoxLayout(this);

    root->addStretch();

    name_box=new QHBoxLayout(this);
    name_text=new QLabel(this);
    name_text->setText("姓名:");
    name_box->addWidget(name_text);
    name_box->addStretch();
    name=new QLabel(this);
    name_box->addWidget(name);
    root->addLayout(name_box);

    IDcard_box=new QHBoxLayout(this);
    IDcard_text=new QLabel(this);
    IDcard_text->setText("身份证号码:");
    IDcard_box->addWidget(IDcard_text);
    IDcard_box->addStretch();
    IDcard=new QLabel(this);
    IDcard_box->addWidget(IDcard);
    root->addLayout(IDcard_box);

    sex_box=new QHBoxLayout(this);
    sex_text=new QLabel(this);
    sex_text->setText("性别:");
    sex_box->addWidget(sex_text);
    sex_box->addStretch();
    sex=new QLabel(this);
    sex_box->addWidget(sex);
    root->addLayout(sex_box);

    nation_box=new QHBoxLayout(this);
    nation_text=new QLabel(this);
    nation_text->setText("民族:");
    nation_box->addWidget(nation_text);
    nation_box->addStretch();
    nation=new QLabel(this);
    nation_box->addWidget(nation);
    root->addLayout(nation_box);

    address_box=new QHBoxLayout(this);
    address_text=new QLabel(this);
    address_text->setText("地址:");
    address_box->addWidget(address_text);
    address_box->addStretch();
    address=new QLabel(this);
    address_box->addWidget(address);
    root->addLayout(address_box);

    phone_box=new QHBoxLayout(this);
    phone_text=new QLabel(this);
    phone_text->setText("联系电话:");
    phone_box->addWidget(phone_text);
    phone_box->addStretch();
    phone=new QLabel(this);
    phone_box->addWidget(phone);
    root->addLayout(phone_box);


    stype_box=new QHBoxLayout(this);
    stype_text=new QLabel(this);
    stype_text->setText("考生类别:");
    stype_box->addWidget(stype_text);
    stype_box->addStretch();
    stype=new QLabel(this);
    stype_box->addWidget(stype);
    root->addLayout(stype_box);

    return_button=new QPushButton();
    return_button->setText("返回主菜单");
    QObject::connect(return_button,SIGNAL(clicked(bool)),this,SLOT(_on_return()));
    root->addWidget(return_button);

    root->addStretch();

    QObject::connect(jwweb_net::get(),SIGNAL(got_info(QString)),this,SLOT(got_info(QString)));
}
void my_info::set_info(QString html){
    qDebug(qUtf8Printable(html));
    qDebug(qUtf8Printable(t));
}
void my_info::showEvent(QShowEvent *){
    jwweb_net::get()->get_info();
    t="'s'";
}
void my_info::_on_return(){
    on_return();
}
void my_info::got_info(QString text){
    QRegExp* reg=new QRegExp("姓&ensp;&ensp;&ensp;&ensp;名</td><td colspan='2'>([^<]+)<br>");
    reg->indexIn(text);
    name->setText(reg->cap(1));

    reg=new QRegExp("身份证号</td><td colspan='2' >(\\d+)<br>");
    reg->indexIn(text);
    IDcard->setText(reg->cap(1));

    reg=new QRegExp("性&ensp;&ensp;&ensp;&ensp;别</td><td>([^<]+)<br>");
    reg->indexIn(text);
    sex->setText(reg->cap(1));

    reg=new QRegExp("民&ensp;&ensp;&ensp;&ensp;族</td><td colspan= 2 >([^<]+)<br>");
    reg->indexIn(text);
    nation->setText(reg->cap(1));

    reg=new QRegExp("联系地址</td><td colspan='3'>([^<]+)<br>");
    reg->indexIn(text);
    address->setText(reg->cap(1));

    reg=new QRegExp("联系电话</td><td>(\\d+)<br>");
    reg->indexIn(text);
    phone->setText(reg->cap(1));

    reg=new QRegExp("考生类别</td><td>([^<]+)<br>");
    reg->indexIn(text);
    stype->setText(reg->cap(1));
}
