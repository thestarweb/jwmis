#include "starjwmis.h"
#include <QApplication>
#include <network/http.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    http* h=new http("http://jwmis.school.edu.cn/jwweb");
    h->set_head("t","123");
    h->exec("","sid=123&aa=q");
    starJwmis w;
    w.show();
    w.resize(360,640);

    return a.exec();
}
