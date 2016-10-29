#ifndef YZM_H
#define YZM_H

#include <QWidget>
#include <QCloseEvent>

class yzm : public QWidget
{
    Q_OBJECT
public:
    explicit yzm(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
    void Show(QByteArray data);
};

#endif // YZM_H
