#include "jwweb_net.h"
#include <starjwmis.h>
#include <QRegExp>
#include <QDebug>
#include <QCryptographicHash>

jwweb_net* jwweb_net::selfobj=NULL;
jwweb_net* jwweb_net::get(){
    if(selfobj==NULL)selfobj=new jwweb_net();
    return selfobj;
}

jwweb_net::jwweb_net()
{
    is_login=false;
    yzm_ui=new yzm();
    yzm_ui->hide();
    QObject::connect(yzm_ui,SIGNAL(yzm_ok(QString)),this,SLOT(_login(QString)));
    sender=NULL;
    login_data=new QMap<QString,QString>;
    login_data->insert("Sel_Type","STU");
}
jwweb_net::~jwweb_net(){
    //
}

void jwweb_net::login(){
    if(sender==NULL)sender=new http(starJwmis::get()->url());
    QObject::connect(sender,SIGNAL(onresponse(http_response*)),this,SLOT(net_cb(http_response*)));
    sender->exec("_data/index_LOGIN.aspx","login_pre");
}
void jwweb_net::_login(QString yzm){
    qDebug()<<yzm;
    login_data->insert("typeName","学生");//用户名
    login_data->insert("txt_asmcdefsddsd",starJwmis::get()->username());//用户名
    login_data->insert("dsdsdsdsdxcxdfgfg", QString::fromLocal8Bit(
                           QCryptographicHash::hash (//密码
                               starJwmis::get()->username().toLocal8Bit()
                               +QString::fromLocal8Bit(QCryptographicHash::hash(starJwmis::get()->password().toLocal8Bit(),QCryptographicHash::Md5).toHex()).mid(0,30).toUpper().toLocal8Bit()
                               +"11342"
                               ,QCryptographicHash::Md5
                           ).toHex()
                         ).mid(0,30).toUpper());
    login_data->insert("fgfggfdgtyuuyyuuckjg",
                       QString::fromLocal8Bit(
                           QCryptographicHash::hash (//验证码
                               QString::fromLocal8Bit(QCryptographicHash::hash(yzm.toUpper().toLocal8Bit(),QCryptographicHash::Md5).toHex()).mid(0,30).toUpper().toLocal8Bit()
                               +"11342"
                           , QCryptographicHash::Md5 ).toHex()
                       ).mid(0,30).toUpper());
    foreach(const QString &key, login_data->keys()){
        qDebug()<<key+"="+login_data->value(key);
    }
    sender->exec("_data/index_LOGIN.aspx",login_data,"login_cb");
}

void jwweb_net::get_info(){
    //yzm_ui->show();
    login();
    //sender->exec("_data/index_LOGIN.aspx","get_info");
}

void jwweb_net::net_cb(http_response* res){//网络回掉函数
    QString type=res->info();
    if(type=="login_pre"){
        if(res->http_state==200){
            QRegExp* reg=new QRegExp("input [^>]*name=\"([^\"]+)\" value=\"([^\"]+)\"");
            for(int i=0;(i=reg->indexIn(QString::fromLocal8Bit(res->content),i)+1)!=0;){
                qDebug()<<reg->capturedTexts();
                login_data->insert(reg->capturedTexts().value(1),reg->capturedTexts().last());
            }
            sender->exec("sys/ValidateCode.aspx","yz-img");
        }
    }else if(type=="yz-img"){
        if(res->http_state==200)
            yzm_ui->Show(res->content);
        else
            qDebug("can't get yanzhengma");
    }else if(type=="get_info"){
        qDebug()<<res->http_state;
    }
}

