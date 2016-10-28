#ifndef MY_INFO_H
#define MY_INFO_H

#include <QWidget>
#include <network/jwweb_net.h>

class my_info : public QWidget
{
    Q_OBJECT
public:
    explicit my_info(QWidget *parent = 0);
    void set_info(QString html);
signals:

public slots:
};

#endif // MY_INFO_H
