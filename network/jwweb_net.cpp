#include "jwweb_net.h"
#include <starjwmis.h>
#include <QRegExp>
#include <QDebug>

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
    sender=NULL;
}
jwweb_net::~jwweb_net(){
    //
}

void jwweb_net::login(){
    if(sender==NULL)sender=new http(starJwmis::get()->url());
    QObject::connect(sender,SIGNAL(onresponse(http_response*)),this,SLOT(net_cb(http_response*)));
    sender->exec("_data/index_LOGIN.aspx","login_pre");
}

void jwweb_net::get_info(){
    //yzm_ui->show();
    login();
    //sender->exec("_data/index_LOGIN.aspx","get_info");
}

void jwweb_net::net_cb(http_response* res){
    QString type=res->info();
    qDebug()<<type;
    if(type=="login_pre"){
        qDebug()<<res->http_state;
        if(res->http_state==200){
            QRegExp* reg=new QRegExp("/<input type=\"hidden\" name=\"__VIEWSTATE\" value=\"(.*?)\" />/");
            if(reg->exactMatch(QString::fromLocal8Bit(res->content))){
                qDebug()<<reg->capturedTexts();
            }else{
                qDebug()<<qUtf8Printable(res->content);
            }
            sender->exec("sys/ValidateCode.aspx","yz-img");
        }
    }else if(type=="yz-img"){
        if(res->http_state==200)
            yzm_ui->Show(res->content);
        else
            qDebug("can't get yanzhengma");
    }
}

