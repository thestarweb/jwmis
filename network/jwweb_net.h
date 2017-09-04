#ifndef JWWEB_NET_H
#define JWWEB_NET_H

#include <QMap>
#include <QQueue>

#include <network/http.h>
#include <ui/yzm.h>

//typedef void(jwweb_net::*jw_callback)(QString);

class jwweb_net:public QObject
{
    Q_OBJECT

public:
    static jwweb_net* get();
    void get_info();
    void login();
private:
    bool is_login;
    static jwweb_net* selfobj;
    explicit jwweb_net();
    ~jwweb_net();
    yzm *yzm_ui;
    http* sender;
    QMap<QString,QByteArray> *login_data;
    QQueue<QString> task_list;
    void do_task();
signals:
    void log(QString info);
    void got_info(QString text);
public slots:
    void net_cb(http_response* res);
    void _login(QString yzm);
};

#endif // JWWEB_NET_H
