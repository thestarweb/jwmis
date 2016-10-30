#ifndef YZM_H
#define YZM_H

#include <QWidget>
#include <QCloseEvent>
#include <QImage>
#include <QLabel>

class yzm : public QWidget
{
    Q_OBJECT
public:
    explicit yzm(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
private:
    QImage* yztp;
    QLabel* yzm_box;
signals:
    input_ok();
public slots:
    void Show(QByteArray data);
};

#endif // YZM_H
