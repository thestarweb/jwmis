#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <QString>
#include <Qmap>

class http_response
{
public:
    explicit http_response(QString info);
    QString info();
    QByteArray content;
    QMap<QString,QString> head;
    int http_state;
    int read_state;
    int content_lenth;
private:
    QString _info;
};

#endif // HTTPINFO_H
