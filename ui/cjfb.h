#ifndef CJFB_H
#define CJFB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>

class cjfb : public QWidget
{
    Q_OBJECT
public:
    explicit cjfb(QWidget *parent = 0);

private:
    QVBoxLayout* top;
    QHBoxLayout* sel_layout;
    QComboBox* sel;
    QPushButton* submit;
    QPushButton* return_button;
    bool _is_update;
signals:
    void on_return();
public slots:
    void on_submit();
    void _on_return();
};

#endif // CJFB_H
