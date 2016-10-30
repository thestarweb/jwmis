#ifndef MY_INFO_H
#define MY_INFO_H

#include <QWidget>
#include <QShowEvent>
#include <network/jwweb_net.h>

class my_info : public QWidget
{
    Q_OBJECT
public:
    explicit my_info(QWidget *parent = 0);
private:
    void showEvent(QShowEvent *);
    QString t;
signals:

public slots:
    void set_info(QString html);
};

#endif // MY_INFO_H
