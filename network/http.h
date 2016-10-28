#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QtNetwork/QTcpSocket>
#include <network/http_response.h>
#include <QStack>
namespace network {
class http;
}

typedef void(*callback)(http_response*);

class http:QObject
{
    Q_OBJECT

public:
    explicit http(QString urlbase);
    ~http();
    http* set_head(QString name,QString value);
    QString exec(QString url,callback cb);
    QString exec(QString url,QMap<QString,QString> *postdata,callback cb);
    QString exec(QString url,callback cb, const QString postdata);

private:
    QString host;
    int port;
    QString page_base;
    void info(QString url);
    void add_deflate_head();
    QTcpSocket* socket;
    void connect();
    QMap<QString,QString> cookie;
    QMap<QString,QString> head;

    //下面的数据用于记录响应
    http_response* last_info;

    //下面的函数用于记录回调函数
    QStack<callback> callbacks;
public slots:
    void connect_error();
    void net_errror();
    void read();
};

#endif
