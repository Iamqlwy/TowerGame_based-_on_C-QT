#include "affix.h"
#include<fellow.h>
extern int time_group_att;
extern int time_fury;
extern int time_freeze;
extern int time_con_att ;
extern int money;
Affix::Affix(QWidget *parent,QPoint pos): QLabel(parent)
{

    type= QRandomGenerator::global()->bounded(0,4);
    time= QRandomGenerator::global()->bounded(3,11)*400;
    get=QRandomGenerator::global()->bounded(5,16);
    move(pos);
    disappear=new QTimer(this);
    disappear->setSingleShot(true);
    connect(disappear,&QTimer::timeout,this,[this]{this->deleteLater();});
    disappear->start(5000);
    QPixmap a;
    if(type==0)
    {
        a=QPixmap(":/new/prefix3/group_att.png");
    }
    else if(type==1)
        a=QPixmap(":/new/prefix3/fury.png");
    else if(type==2)
        a=QPixmap(":/new/prefix3/freeze.png");
    else if(type==3)
        a=QPixmap(":/new/prefix3/con_att.png");
    setPixmap(a);

}
void Affix::mousePressEvent(QMouseEvent *ev)
{
    if(type==0)
    {
        time_group_att+=time;
    }
    else if(type==1)
    {
        time_fury+=time;
    }
    else if(type==2)
    {
        time_freeze+=time;
    }
    else if(type==3)
    {
        time_con_att+=time;
    }
    money+=get;
    this->deleteLater();
}
