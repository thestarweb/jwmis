#include <QString>
#include <QtNetwork/QTcpSocket>
#include <network/httpinfo.h>
namespace network {
class http;
}

class http:QObject
{
    Q_OBJECT

public:
    explicit http(QString urlbase);
    ~http();
    http* set_head(QString name,QString value);
    QString exec(QString url);
    QString exec(QString url,QMap<QString,QString> *postdata);
    QString exec(QString url, const QString postdata);

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
    httpinfo* last_info;
public slots:
    void connect_error();
    void net_errror();
    void read();
};
