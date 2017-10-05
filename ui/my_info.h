#ifndef MY_INFO_H
#define MY_INFO_H

#include <QWidget>
#include <QShowEvent>
#include <network/jwweb_net.h>
#include <QPushButton>
#include <QLayout>

class my_info : public QWidget
{
    Q_OBJECT
public:
    explicit my_info(QWidget *parent = 0);
private:
    void showEvent(QShowEvent *);
    QString t;
    QVBoxLayout* root;
    QPushButton* return_button;

    //姓名
    QHBoxLayout* name_box;
    QLabel* name_text;
    QLabel* name;
    //身份证号码
    QHBoxLayout* IDcard_box;
    QLabel* IDcard_text;
    QLabel* IDcard;
    //性别
    QHBoxLayout* sex_box;
    QLabel* sex_text;
    QLabel* sex;
    //民族
    QHBoxLayout* nation_box;
    QLabel* nation_text;
    QLabel* nation;
    //地址
    QHBoxLayout* address_box;
    QLabel* address_text;
    QLabel* address;
    //电话
    QHBoxLayout* phone_box;
    QLabel* phone_text;
    QLabel* phone;
    //考生类别
    QHBoxLayout* stype_box;
    QLabel* stype_text;
    QLabel* stype;
signals:
    void on_return();
public slots:
    void set_info(QString html);
    void _on_return();
    void got_info(QString task, QByteArray bytes);
};

#endif // MY_INFO_H
