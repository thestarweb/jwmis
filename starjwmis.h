#ifndef STARJWMIS_H
#define STARJWMIS_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include <ui/login.h>
#include <ui/menu.h>

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
    menu* menu_ui;
    login* login_ui;
    QWidget* now_ui;
public slots:
    void to_menu_ui();
    void to_login_ui();
};

#endif // STARJWMIS_H
