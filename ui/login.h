#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
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
    QString url();
    QString username();
    QString password();

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
    QPushButton* return_button;
signals:
    void on_return();
public slots:
    void _on_return();
};
#endif
