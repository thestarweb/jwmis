#include "yzm.h"

yzm::yzm(QWidget *parent) : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("验证码");
    yztp=new QImage();
    yzm_box=new QLabel(this);
}
void yzm::closeEvent(QCloseEvent *event){
    event->ignore();
    hide();
}

void yzm::Show(QByteArray data){
    yztp->loadFromData(data);
    yzm_box->setPixmap(QPixmap::fromImage(*yztp));
    show();
}
