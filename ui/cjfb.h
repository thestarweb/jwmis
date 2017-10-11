#ifndef CJFB_H
#define CJFB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <network/jwweb_net.h>

class cjfb : public QWidget
{
    Q_OBJECT
public:
    explicit cjfb(QWidget *parent = 0);
    void showEvent(QShowEvent *);
private:
    QVBoxLayout* top;
    QHBoxLayout* sel_layout;
    QComboBox* sel;
    QPushButton* submit;
    QTableWidget* table;
    QPushButton* return_button;
    bool _is_update;
    void add_fb(QString name,bool i90,bool i80,bool i70,bool i60,bool i0);
signals:
    void on_return();
public slots:
    void on_submit();
    void _on_return();
    void net_cb(QString task,QByteArray bytes);
};

#endif // CJFB_H
