#ifndef STARJWMIS_H
#define STARJWMIS_H

#include <QWidget>
#include <QLineEdit>

#include <ui/login.h>

namespace Ui {
class starJwmis;
}

class starJwmis : public QWidget
{
    Q_OBJECT

public:
    explicit starJwmis(QWidget *parent = 0);
    void reset_ui();
    ~starJwmis();

private:
    QLineEdit* url;
    /*
     * 存放ui。。
     * 0 登陆ui
     * 1 选项ui
     */
    QWidget* uis[1];
};

#endif // STARJWMIS_H
