#include "unit.h"

Unit::Unit(QWidget *parent) :QLabel(parent)
{

    affixnum=0;
    init_blood=100;
    blood=init_blood;
    att_power = 10;
    resistance = 100;
    base=602;
    affix[0]=new QLabel(this);
    affix[0]->resize(20,20);
    affix[1]=new QLabel(this);
    affix[1]->resize(20,20);
    blood_show=new QProgressBar(this);
    blood_show->move(this->pos());
    blood_show->setRange(0,100);
    blood_show->setValue(100);
    blood_show->resize(60,3);
    blood_show->setTextVisible(false);
    blood_show->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid grey;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #05B8CC;"
        "    border-radius: 5px;"
        "}"
    );
    resize(60,60);
    att_timer=new QTimer(this);
    att_act_timer=new QTimer(this);
    count_damage_timer=new QTimer(this);
    count_damage_timer->setSingleShot(true);
    connect(att_act_timer, &QTimer::timeout, this, [this]() {
                static int index = 0;

                this->setPixmap(showpixmap[index]);
                index = (index + 1) % 4;
            });
    connect(count_damage_timer,&QTimer::timeout,this,[this]{att_act_timer->start();});


}
void Unit::attack()
{

}

void Unit::damage(float num)
{
    blood-=num*(resistance/(resistance+base));
    blood_show->setValue((blood/init_blood)*100);
    display_blood();
    if(blood<=0)
    {
        die();
    }

}
void Unit::die()
{
    this->hide();
    this->deleteLater();
}
void Unit::move(const QPoint &pos) {
    QLabel::move(pos);
    blood_show->move(0, 10);
    affix[0]->move(40,10);
    affix[1]->move(40,40);

}
void Unit::display_blood()
{
    blood_show->setValue(100*blood/init_blood);
}
void Unit::act_damage()
{
    if(!count_damage_timer->isActive()){
        setPixmap(showpixmap[4]);
        att_act_timer->stop();

        count_damage_timer->start(1000);
    }

}
void Unit::set_blood(float num)
{
    blood=num;
    blood_show->setValue(100*num/init_blood);
    qDebug()<<1212;
}
