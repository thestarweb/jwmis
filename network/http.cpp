#include "http.h"
#include "qdebug.h"

http::http(QString _url)
{
    UA="Mozilla/5.0 (Windows NT 10.0; WOW64; rv:50.0) Gecko/20100101 Firefox/50.0Windows NT 10.0; WOW645.0 (Windows) SN:NULL";
    fp=new QFile("D:\\http.log.txt");
    fp->open(QIODevice::WriteOnly | QIODevice::Text);
    info(_url);
    log_stream=new QTextStream(fp);
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
    set_head("User-Agent",UA);
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

QString http::exec(QString url,QString type_name){
    this->exec(url,type_name,NULL);
    return "";
}

QString http::exec(QString url, QMap<QString, QByteArray> *post, QString type_name){
    if(post!=NULL){
        QByteArray data="",value;
        foreach(const QString &key, post->keys()){
            value=post->value(key);
            data+=key+"="+value.replace("=","%3D").replace(" ","+").replace("/","%2F").replace("(","%28").replace(")","%29").replace(";","%3B").replace(":","%3A")+"&";
        }
        return this->exec(url,type_name,data);
    }
    return "";
}

QString http::exec(QString url, QString type_name, const QByteArray post){
    response_info.push(new http_response(type_name));
    QString httpHead=post==NULL?"GET":"POST";
    httpHead+=" "+page_base+url+" HTTP/1.1\nhost: "+host+"\n";
    foreach(QString key,head.keys()){
        httpHead+=key+": "+head.value(key)+"\n";
    }
    if(!cookie.isEmpty()){
        httpHead+="cookie: ";
        bool f=false;
        foreach(QString key,cookie.keys()){
            httpHead+=(f?"; ":"")+key+"="+cookie.value(key);
            f=true;
        }
        httpHead+="\n";
    }

    if(post!=NULL){
        httpHead+="Content-Type: application/x-www-form-urlencoded\nContent-Length: "+QString::number(post.length())+" \n\n"+post+"\n\n";
    }else{
        httpHead+="\n";
    }
    *log_stream<<"send:"<<endl<<httpHead<<endl;
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
    http_response* last_info=response_info.first();
    do{
        if(last_info==NULL){
            return;
        }
        l=socket->readLine(1024);
        if(l.length()==0) return;
        qDebug()<<QString::fromLocal8Bit(l)<<"--";
        *log_stream<<QString::fromLocal8Bit(l);
        if(last_info->read_state==0){
            s=l;
            last_info->http_state=s.section(" ",1,1).toInt();
            last_info->read_state++;
        }else if(last_info->read_state==1){//读取响应头
            if(l=="\n"||l=="\r\n") last_info->read_state++;//读到一个空行说明响应头读取完毕进入下一个环节
            else{
                s=l;
                last_info->head.insert(s.section(": ",0,0),s.section(": ",1));
                if(s.section(": ",0,0)=="Set-Cookie"){
                    //qDebug()<<l<<"-"<<cookie.isEmpty();
                    QString c=s.section(": ",1).section(";",0,0);
                    cookie.insert(c.section("=",0,0),c.section("=",1));
                    //qDebug()<<cookie.isEmpty();
                }
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
                onresponse(response_info.pop());
                last_info=NULL;
            }
        }
    }while(l.length()!=0);
}

http::~http()
{
    socket->close();
    fp->close();
}
