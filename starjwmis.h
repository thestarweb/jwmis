#ifndef STARJWMIS_H
#define STARJWMIS_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include <ui/login.h>

namespace Ui {
class starJwmis;
}

class starJwmis : public QWidget
{
    Q_OBJECT

public:
    explicit starJwmis(QWidget *parent = 0);
    ~starJwmis();

private:
    QVBoxLayout* root_layout;
    QHBoxLayout* top_layout;
    QPushButton* login_info_button;
    QPushButton* my_info_button;
    QHBoxLayout* main_layout;
    /*
     * 存放ui。。
     * 0 登陆ui
     * 1 选项ui
     */
    QWidget* uis[1];
};

#endif // STARJWMIS_H
