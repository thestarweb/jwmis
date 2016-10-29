#include "yzm.h"

yzm::yzm(QWidget *parent) : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("验证码");
}
void yzm::closeEvent(QCloseEvent *event){
    event->ignore();
    hide();
}

void yzm::Show(QByteArray data){
    show();
}
