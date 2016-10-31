#include "yzm.h"

yzm::yzm(QWidget *parent) : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("验证码");
    root=new QHBoxLayout(this);
    yzm_text=new QLabel();
    yzm_text->setText("验证码");
    root->addWidget(yzm_text);
    yztp=new QImage();
    yzm_box=new QLabel();
    root->addWidget(yzm_box);
    yzm_input=new QLineEdit();
    root->addWidget(yzm_input);
    ok_button=new QPushButton();
    ok_button->setText("确定");
    root->addWidget(ok_button);
    //setFixedSize(this->width(),this->height());
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
