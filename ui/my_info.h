#ifndef MY_INFO_H
#define MY_INFO_H

#include <QWidget>
#include <QShowEvent>
#include <network/jwweb_net.h>
#include <QPushButton>
#include <QLayout>

class my_info : public QWidget
{
    Q_OBJECT
public:
    explicit my_info(QWidget *parent = 0);
private:
    void showEvent(QShowEvent *);
    QString t;
    QVBoxLayout* root;
    QPushButton* return_button;
signals:
    void on_return();
public slots:
    void set_info(QString html);
    void _on_return();
};

#endif // MY_INFO_H
