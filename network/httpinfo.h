#ifndef HTTPINFO_H
#define HTTPINFO_H

#include <QString>
#include <Qmap>

class httpinfo
{
public:
    httpinfo();
    QString content;
    QMap<QString,QString> head;
    int http_state;
    int read_state;
    int content_lenth;
};

#endif // HTTPINFO_H
