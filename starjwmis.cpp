#include "starjwmis.h"

starJwmis::starJwmis(QWidget *parent) :
    QWidget(parent)
{
    url=new QLineEdit(this);
    url->setText("http://jwmis.school.edu.cn/jwweb");
    uis[0]=new login(this);
    setGeometry(this->x(),this->y(),200,600);
    reset_ui();
}

void starJwmis::reset_ui(){
    for(int i=0;i<1;i++){
        uis[i]->setGeometry(0,20,this->width(),this->height());
        //uis[i]->setContentsMargins(0,20,0,0);
    }
}

starJwmis::~starJwmis()
{
}
