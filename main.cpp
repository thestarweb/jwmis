#include "starjwmis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //starJwmis w;
    //w.show();
    //w.resize(360,640);
    starJwmis* w=starJwmis::get();
    w->show();
    w->resize(360,640);

    return a.exec();
}
