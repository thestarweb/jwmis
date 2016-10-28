#ifndef YZM_H
#define YZM_H

#include <QWidget>

class yzm : public QWidget
{
    Q_OBJECT
public:
    explicit yzm(QWidget *parent = 0);
    void show_a(QByteArray data);

signals:

public slots:
};

#endif // YZM_H
