#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>

namespace uis {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = 0);
private:
    QVBoxLayout* main_layout;
    QPushButton* login_button;
    QPushButton* my_info_button;
signals:
    void on_login_click();
    void on_info_click();
public slots:
    void _on_login_click();
    void _on_info_click();
};

#endif // MENU_H
