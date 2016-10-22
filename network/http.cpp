#include "http.h"
#include "qdebug.h"

http::http(QString _url)
{
    info(_url);
}

void http::info(QString url){
    QString type="http:";
    QStringList l = url.split("//");
    if(l.length()>2) return;
    if(l.length()==2){
        url=l[1];
        if(l[0]!="")type=l[0];
    }
    if(type!="http:") return;
    QString server=url.section("/",0,0);
    host=server.section(":",0,0);
    QString p=server.section(":",1,1);
    if(p!=""){
        port=p.toInt();
    }
    page_base="/"+url.section("/",1);
    add_deflate_head();
}

http* http::set_head(QString name,QString value){
    head.insert(name,value);
    return this;
}

void http::add_deflate_head(){
    set_head("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    set_head("Accept-Encoding","deflate");
    set_head("Connection","keep-alive");
    set_head("User-Agent","star QT jwmis");
}

QString http::exec(QString url){
    return exec(url,NULL);
}

QString http::exec(QMap<QString,QString> *post, QString url){
    if(post!=NULL){
        QString data="";
        foreach(const QString &key, post->keys()){
            data+=key+"="+post->value(key);
        }
        return exec(url,data);
    }
    return "";
}

QString http::exec(QString url,const QString post){
    QString httpHead=post==NULL?"GET":"POST";
    httpHead+=" "+page_base+url+" HTTP/1.1\nhost: "+host+"\n";
    foreach(QString key,head.keys()){
        httpHead+=key+": "+head.value(key)+"\n";
    }

    if(post!=NULL){
        httpHead+="Content-Length: "+QString::number(post.length())+" \n\n"+post;
    }
    qDebug("%s",qPrintable(httpHead));
    return "";
}

http::~http()
{
}
