#include "jwweb_net.h"
#include <starjwmis.h>
#include <QRegExp>
#include <QDebug>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QThread>

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
    login_data=new QMap<QString,QByteArray>;
    login_data->insert("Sel_Type","STU");
}
jwweb_net::~jwweb_net(){
}

void jwweb_net::do_task(){
    if(task_list.isEmpty()) return;
    qDebug()<<"task\n";
    QString task_name=task_list.dequeue();
    if(task_name=="info"){
        log("正在获取信息");
        sender->exec("xsxj/Stu_MyInfo_RPT.aspx","get_info");
    }else if(task_name=="cjfb_pre"){
        log("正在获取学期信息");
        sender->exec("xscj/Stu_cjfb.aspx","cjfb_pre");
    }else if(task_name.indexOf("cjfb")==0){
        QStringList c=task_name.split(".");
        QMap<QString,QByteArray>* post=new QMap<QString,QByteArray>;
        post->insert("SelXNXQ",QString::number(c.length()-1).toLocal8Bit());
        if(c.length()>1){
            post->insert("sel_xn",c.at(1).toLocal8Bit());
            if(c.length()>2) post->insert("sel_xq",c.at(2).toLocal8Bit());
        }
        post->insert("submit",QString::fromUtf8("检索").toLocal8Bit());
        sender->set_head("Referer",starJwmis::get()->url()+"/xscj/Stu_cjfb.aspx");
        log("获取成绩分布");
        sender->exec("xscj/Stu_cjfb_rpt.aspx",post,task_name);
    }
    else
        qDebug()<<"unknow task : "<<task_name<<endl;
}
void jwweb_net::add_task(QString task){
    task_list.enqueue(task);
    login();
}

void jwweb_net::login(){
    if(starJwmis::get()->is_logininfo_update()||sender==NULL){
        sender=new http(starJwmis::get()->url());
        QObject::connect(sender,SIGNAL(onresponse(http_response*)),this,SLOT(net_cb(http_response*)));
        log("请求登陆页面");
        sender->exec("_data/index_LOGIN.aspx","login_pre");
    }else{
        do_task();
    }
}
void jwweb_net::_login(QString yzm){
    log("组织登陆信息");
    login_data->insert("typeName",QString::fromUtf8("学生").toLocal8Bit());//用户名
    login_data->insert("pcInfo",sender->UA.toLocal8Bit());
    login_data->insert("txt_pewerwedsdfsdff","");
    login_data->insert("txt_sdertfgsadscxcadsads","");
    login_data->insert("sbtState","");
    login_data->insert("txt_asmcdefsddsd",starJwmis::get()->username().toLocal8Bit());//用户名
    login_data->insert("dsdsdsdsdxcxdfgfg", QString::fromLocal8Bit(
                           QCryptographicHash::hash (//密码
                               starJwmis::get()->username().toLocal8Bit()
                               +QString::fromLocal8Bit(QCryptographicHash::hash(starJwmis::get()->password().toLocal8Bit(),QCryptographicHash::Md5).toHex()).mid(0,30).toUpper().toLocal8Bit()
                               +"11342"
                               ,QCryptographicHash::Md5
                           ).toHex()
                         ).mid(0,30).toUpper().toLocal8Bit());
    login_data->insert("fgfggfdgtyuuyyuuckjg",
                       QString::fromLocal8Bit(
                           QCryptographicHash::hash (//验证码
                               QString::fromLocal8Bit(QCryptographicHash::hash(yzm.toUpper().toLocal8Bit(),QCryptographicHash::Md5).toHex()).mid(0,30).toUpper().toLocal8Bit()
                               +"11342"
                           , QCryptographicHash::Md5 ).toHex()
                       ).mid(0,30).toUpper().toLocal8Bit());
    foreach(const QString &key, login_data->keys()){
        qDebug()<<key+"="+login_data->value(key);
    }
    log("等候服务器验证登陆信息");
    sender->set_head("Referer",starJwmis::get()->url()+"/_data/index_LOGIN.aspx");
    sender->exec("_data/index_LOGIN.aspx",login_data,"login_cb");
}

void jwweb_net::get_info(){
    //yzm_ui->show();
    task_list.enqueue("info");
    login();
    //sender->exec("XSXJ/KingosLove.aspx","info");
}

void jwweb_net::net_cb(http_response* res){//网络回掉函数
    QString type=res->info();
    if(type=="login_pre"){
        if(res->http_state==200){
            QRegExp* reg=new QRegExp("input [^>]*name=\"([^\"]+)\" value=\"([^\"]+)\"");
            for(int i=0;(i=reg->indexIn(QString::fromLocal8Bit(res->content),i)+1)!=0;){
                login_data->insert(reg->capturedTexts().value(1),reg->capturedTexts().last().toLocal8Bit());
            }
            log("请求验证码");
            sender->set_head("Referer",starJwmis::get()->url()+"/_data/index_LOGIN.aspx");
            sender->exec("sys/ValidateCode.aspx","yz-img");
        }
    }else if(type=="yz-img"){
        if(res->http_state==200)
            yzm_ui->Show(res->content);
        else
            qDebug("can't get yanzhengma");
    }else if(type=="login_cb"){
        if(res->http_state==200){
            QRegExp* reg=new QRegExp("<span id=\"divLogNote\"><font color=\"Red\">([^<]+)<");
            reg->indexIn(QString::fromLocal8Bit(res->content));
            QString info=reg->cap(1);
            if(info.indexOf("正在加载")==0){
                log("登陆成功");
                do_task();
            }else if(info.indexOf("验证码")>=0){
                log("验证码错误");
                sender->set_head("Referer",starJwmis::get()->url()+"/_data/index_LOGIN.aspx");
                sender->exec("sys/ValidateCode.aspx","yz-img");
            }
            else QMessageBox::about(0,"登陆失败",info);
        }else if(res->http_state>=500){
            sender->set_head("Referer",starJwmis::get()->url()+"/jwweb/_data/index_LOGIN.aspx");
            sender->exec("_data/index_LOGIN.aspx",login_data,"login_cb");
        }
    }else if(type=="get_info"){
        log("请求信息成功！");
        down_task("got_info",res->content);
    }else if(type=="cjfb_pre"){
        log("成功获取信息表");
        down_task("got_cjfb_pre",res->content);
    }else if(type.indexOf("cjfb")==0){
        log("获取成绩分布成功");
        down_task("cjfb",res->content);
    }
}

