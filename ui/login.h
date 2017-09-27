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
    bool is_update(bool reset=true);
private:
    QVBoxLayout* main_layout;
    QHBoxLayout* url_layout;
    QLabel* url_text;
    QLineEdit* url_box;
    QString url_cache;
    QHBoxLayout* username_layout;
    QLabel* username_text;
    QLineEdit* username_box;
    QString username_cache;
    QHBoxLayout* password_layout;
    QLabel* password_text;
    QLineEdit* password_box;
    QString password_cache;
    QHBoxLayout* info_layout;
    QLabel* info;
    QPushButton* return_button;
    bool _is_update;
signals:
    void on_return();
public slots:
    void _on_return();
};
#endif
