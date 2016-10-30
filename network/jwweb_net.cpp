#include "jwweb_net.h"
#include <starjwmis.h>

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
}
jwweb_net::~jwweb_net(){
    //
}

void jwweb_net::login(){
    sender=new http(starJwmis::get()->url());
    QObject::connect(sender,SIGNAL(onresponse(http_response*)),this,SLOT(on_yzimg_get(http_response*)));
    sender->exec("sys/ValidateCode.aspx","yz-img");
}

void jwweb_net::get_info(){
    //yzm_ui->show();
    login();
}

void jwweb_net::on_yzimg_get(http_response* res){
    if(res->info()!="yz-img") return;
    if(res->http_state==200)
        yzm_ui->Show(res->content);
    else
        qDebug("can't get yanzhengma");
}

