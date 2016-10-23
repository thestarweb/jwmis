#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <starjwmis.h>
#include <QLayout>
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
    QVBoxLayout* main_layout;
    QHBoxLayout* url_layout;
    QLabel* url_text;
    QLineEdit* url_box;
    QHBoxLayout* username_layout;
    QLabel* username_text;
    QLineEdit* username_box;
    QHBoxLayout* password_layout;
    QLabel* password_text;
    QLineEdit* password_box;
    QHBoxLayout* info_layout;
    QLabel* info;
};
#endif
