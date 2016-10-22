#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <starjwmis.h>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace uis {
class login;
}

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = 0);
    ~login();

private:
    QLabel* username_text;
    QLineEdit* username_box;
    QLabel* password_text;
    QLineEdit* password_box;
    QPushButton* login_button;
};
#endif
