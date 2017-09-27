#ifndef STARJWMIS_H
#define STARJWMIS_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

#include <ui/login.h>
#include <ui/menu.h>
#include <ui/my_info.h>

#include <network/jwweb_net.h>

namespace Ui {
class starJwmis;
}
class my_info;

class starJwmis : public QWidget
{
    Q_OBJECT

public:
    ~starJwmis();
    static starJwmis* get();
    QString url();
    QString username();
    QString password();
    bool is_logininfo_update(bool reset=true);
private:
    explicit starJwmis(QWidget *parent = 0);
    static starJwmis* selfobj;
    QVBoxLayout* root_layout;
    menu* menu_ui;
    login* login_ui;
    my_info* my_info_ui;
    QWidget* now_ui;
    QLabel* _info;
    QLabel* _info2;
public slots:
    void to_menu_ui();
    void to_login_ui();
    void to_info_ui();
    void log(QString info);
};

#endif // STARJWMIS_H
