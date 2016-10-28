#include "yzm.h"

yzm::yzm(QWidget *parent) : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("验证码");
}
void yzm::show_a(QByteArray data){
    show();
}
