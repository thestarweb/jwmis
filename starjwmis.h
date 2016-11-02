#ifndef STARJWMIS_H
#define STARJWMIS_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include <ui/login.h>
#include <ui/menu.h>
#include <ui/my_info.h>

#include <network/http.h>

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
private:
    explicit starJwmis(QWidget *parent = 0);
    static starJwmis* selfobj;
    QVBoxLayout* root_layout;
    menu* menu_ui;
    login* login_ui;
    my_info* my_info_ui;
    QWidget* now_ui;
public slots:
    void to_menu_ui();
    void to_login_ui();
    void to_info_ui();
};

#endif // STARJWMIS_H
