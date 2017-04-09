#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QtNetwork/QTcpSocket>
#include <network/http_response.h>
#include <QStack>
namespace network {
class http;
}


class http:public QObject
{
    Q_OBJECT

public:
    QString UA;
    explicit http(QString urlbase);
    ~http();
    http* set_head(QString name,QString value);
    QString exec(QString url,QString type_name);
    QString exec(QString url,QMap<QString,QByteArray> *postdata,QString type_name);
    QString exec(QString url, QString type_name, const QByteArray postdata);

private:
    QString host;
    int port;
    QString page_base;
    void info(QString url);
    void add_deflate_head();
    QTcpSocket* socket;
    void connect();
    QByteArray _mo(QByteArray in);
    QMap<QString,QString> cookie;
    QMap<QString,QString> head;

    //下面的数据用于记录响应
    http_response* last_info;

    //下面的队列用于返回数据队列
    QStack<http_response*> response_info;

signals:
    void onresponse(http_response* res);
public slots:
    void connect_error();
    void net_errror();
    void read();
};

#endif
