#include <QString>
#include <QtNetwork/QTcpSocket>
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
    QString exec(QMap<QString,QString> *postdata,QString url);
    QString exec(QString url, const QString postdata);

private:
    QString host;
    int port;
    QString page_base;
    void info(QString url);
    void add_deflate_head();
    static QTcpSocket* socket;
    static void connect();
    QMap<QString,QString> cookie;
    QMap<QString,QString> head;
};
