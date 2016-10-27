#include "http.h"
#include "qdebug.h"

http::http(QString _url)
{
    info(_url);
    socket=NULL;
    last_info=NULL;
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
    }else{
        port=80;
    }
    page_base="/"+url.section("/",1);
    if(!page_base.endsWith('/')) page_base+="/";
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

void http::connect(){
    if(socket==NULL){
        socket=new QTcpSocket(this);
        QObject::connect(socket,SIGNAL(disconnected()),this,SLOT(connect_error()));
        QObject::connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(net_errror()));
        QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    }
    if(!socket->isOpen()){
        socket->connectToHost(host,port);
        qDebug()<<"connect";
        socket->waitForConnected();
    }
}

QString http::exec(QString url, callback cb){
    this->exec(url,cb,NULL);
    return "";
}

QString http::exec(QString url, QMap<QString,QString> *post, callback cb){
    if(post!=NULL){
        QString data="";
        foreach(const QString &key, post->keys()){
            data+=key+"="+post->value(key);
        }
        return this->exec(url,cb,data);
    }
    return "";
}

QString http::exec(QString url, callback cb, const QString post){
    callbacks.push(cb);
    QString httpHead=post==NULL?"GET":"POST";
    httpHead+=" "+page_base+url+" HTTP/1.1\nhost: "+host+"\n";
    foreach(QString key,head.keys()){
        httpHead+=key+": "+head.value(key)+"\n";
    }

    if(post!=NULL){
        httpHead+="Content-Length: "+QString::number(post.length())+" \n\n"+post;
    }else{
        httpHead+="\n";
    }
    qDebug("%s",qPrintable(httpHead));
    connect();
    socket->write(httpHead.toUtf8());
    return "";
}

void http::connect_error(){
    socket->close();
    qDebug()<<"connect error";
}

void http::net_errror(){
    qDebug()<<"net error:"<<socket->errorString();
    socket->close();
}

void http::read(){
    QByteArray l=NULL;
    QString s;
    do{
        if(last_info==NULL){
            last_info=new http_response();
        }
        l=socket->readLine(1024);
        //qDebug()<<l<<"--";
        if(last_info->read_state==0){
            s=l;
            last_info->http_state=s.section(" ",1,1).toInt();
            last_info->read_state++;
        }else if(last_info->read_state==1){//读取响应头
            if(l=="\n"||l=="\r\n") last_info->read_state++;//读到一个空行说明响应头读取完毕进入下一个环节
            else{
                s=l;
                last_info->head.insert(s.section(": ",0,0),s.section(": ",1));
                //qDebug()<<s.section(": ",0,0)<<"--"<<s.section(": ",1).trimmed();
            }
        }else if(last_info->read_state==2){
            last_info->content_lenth=last_info->head.value("Content-Length").toInt();
            last_info->read_state++;
        }if(last_info->read_state==3){//读取内容
            last_info->content+=l;
        }
        if(last_info->read_state==3){
            if(last_info->content.length()==last_info->content_lenth)
            {
                last_info->read_state++;
                callbacks.pop()(last_info);
                last_info=NULL;
            }
        }
    }while(l.length()!=0);
}

http::~http()
{
    socket->close();
}
