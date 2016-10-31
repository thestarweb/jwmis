#ifndef YZM_H
#define YZM_H

#include <QWidget>
#include <QCloseEvent>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>


class yzm : public QWidget
{
    Q_OBJECT
public:
    explicit yzm(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
private:
    QImage* yztp;
    QHBoxLayout* root;
    QLabel* yzm_text;
    QLabel* yzm_box;
    QLineEdit* yzm_input;
    QPushButton* ok_button;
signals:
    input_ok();
public slots:
    void Show(QByteArray data);
};

#endif // YZM_H
