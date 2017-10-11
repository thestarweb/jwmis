#include "cjfb.h"
#include <QHeaderView>

cjfb::cjfb(QWidget *parent) : QWidget(parent)
{
    top=new QVBoxLayout(this);

    sel_layout=new QHBoxLayout();
    sel=new QComboBox(this);
    submit=new QPushButton(this);
    submit->setText("检索");
    QObject::connect(submit,SIGNAL(clicked(bool)),this,SLOT(on_submit()));
    sel_layout->addWidget(sel);
    sel_layout->addWidget(submit);

    table=new QTableWidget();
    table->horizontalHeader()->setDefaultSectionSize(150);
    table->setColumnCount(6);//设置列数
    QStringList list;
    list<<"科目/学分/类型"<<"90+"<<"80+"<<"70+"<<"60+"<<"<60";
    table->setHorizontalHeaderLabels(list);//设置表头
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    for(int i=1;i<6;i++)
        table->setColumnWidth(i,29);

    return_button=new QPushButton(this);
    return_button->setText("返回");
    QObject::connect(return_button,SIGNAL(clicked(bool)),this,SLOT(_on_return()));

    top->addStretch(10);
    top->addLayout(sel_layout);
    top->addStretch(1);
    top->addWidget(table);
    top->addSpacing(1);
    top->addWidget(return_button);
    top->addStretch(10);

    QObject::connect(jwweb_net::get(),SIGNAL(down_task(QString,QByteArray)),this,SLOT(net_cb(QString,QByteArray)));
}
void cjfb::showEvent(QShowEvent *){
    sel->setEditable(false);
    submit->setEnabled(false);
    jwweb_net::get()->add_task("cjfb_pre");
}
void cjfb::_on_return(){
    on_return();
}
void cjfb::on_submit(){
    QString name="cjfb";
    if(sel->currentData()!="") name+="."+sel->currentData().toString();
    jwweb_net::get()->add_task(name);
}
void cjfb::add_fb(QString name,bool i90,bool i80,bool i70,bool i60,bool i0){
    int i=table->rowCount();
    table->setRowCount(i+1);
    table->setItem(i,0,new QTableWidgetItem(name));
    if(i90) table->setItem(i,1, new QTableWidgetItem("√"));
    else if(i80) table->setItem(i,2, new QTableWidgetItem("√"));
    else if(i70) table->setItem(i,3, new QTableWidgetItem("√"));
    else if(i60) table->setItem(i,4, new QTableWidgetItem("√"));
    else if(i0) table->setItem(i,5, new QTableWidgetItem("√"));
    table->setRowHeight(i,100);
}

void cjfb::net_cb(QString task,QByteArray bytes){
    if(task=="got_cjfb_pre"){
        sel->clear();
        sel->addItem("入学以来","");
        QRegExp* reg=new QRegExp("Col1.([0-9]+).='([0-9]+)';Col2.([0-9]+).='([0-9]+)';Col3.([0-9]+).='([^']+)';");
        QString l="";
        for(int i=0;(i=reg->indexIn(QString::fromLocal8Bit(bytes),i)+1)!=0;){
            if(reg->cap(2)!=l){
                sel->addItem(" "+reg->cap(2)+"学年",reg->cap(2));
                l=reg->cap(2);
            }
            sel->addItem("  "+reg->cap(6),reg->cap(2)+"."+reg->cap(4));
        }
        sel->setEditable(true);
        submit->setEnabled(true);
    //
    }else if(task=="cjfb"){
        table->setRowCount(0);
        QRegExp* reg=new QRegExp("<tr class=(?:B|H)><td [^>]+>([^<]*)<br></td><td [^>]*>([^<]+)<br></td><td [^>]*>([^<]+)<br></td><td [^>]*>([^ ]+) *<br></td><td [^>]*>([^ ]+) *<br></td><td [^>]*>(.*)</td><td [^>]*>(.*)</td><td [^>]*>(.*)</td><td [^>]*>(.*)</td><td [^>]*>(.*)</td><td [^>]*>(.*)</td></tr>");
        reg->setMinimal(true);
        for(int i=0;(i=reg->indexIn(QString::fromLocal8Bit(bytes),i)+1)!=0;){
            //qDebug()<<reg->cap(1)<<reg->cap(2)<<reg->cap(3)<<reg->cap(4)<<"|"<<reg->cap(5)<<"|"<<reg->cap(6)<<"|"<<reg->cap(7)<<"|"<<reg->cap(8)<<"|"<<reg->cap(9)<<"|"<<reg->cap(10)<<"|";
            add_fb(reg->cap(2)+"\n"+reg->cap(4)+"\n"+reg->cap(3)+"|"+reg->cap(5)+"|"+reg->cap(6),reg->cap(7)=="√",reg->cap(8)=="√",reg->cap(9)=="√",reg->cap(10)=="√",reg->cap(11)=="√");
        }
        table->setRowCount(table->rowCount()+1);
    }
}
