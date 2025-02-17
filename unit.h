#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include<QLabel>
#include<QProgressBar>
#include<region.h>
#include<QTimer>
#include<QPalette>
#include<QPixmap>
#include<QDebug>
class Unit : public QLabel
{
    Q_OBJECT
public:
    explicit Unit(QWidget *parent=nullptr);
    float init_blood;
    float blood;
    float att_power;
    float resistance;
    float base=20;
    int att_interval;
    bool comrade;
    QTimer *att_timer;
    QTimer *att_act_timer;
    QTimer *count_damage_timer;
    Region *place;
    QProgressBar *blood_show;
    QLabel *affix[2];
    int affixnum;
    int stren_force[2];

    int dir;// 0-右，1-下，2-上，3左
    void display_blood();
    virtual void attack();
    void damage(float num);
    void act_damage();
    virtual void die();
    virtual void move(const QPoint &pos) ;
    QPixmap att_act[7];
    QPixmap showpixmap[7];
    void set_blood(float num);
};

#endif // UNIT_H
