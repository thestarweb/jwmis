#include "starjwmis.h"
#include <QApplication>
#include <network/http.h>
#include <QDebug>

void test(http_response* r){
    qDebug("%s",qUtf8Printable(r->content));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    http* h=new http("http://www.thestarweb.cn/");
    h->set_head("t","123");
    h->exec("",&test);
    starJwmis w;
    w.show();
    w.resize(360,640);

    return a.exec();
}
