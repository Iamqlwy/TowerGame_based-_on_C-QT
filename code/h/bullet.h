#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QPixmap>

#include<enemy.h>


class Bullet : public QLabel
{
    Q_OBJECT
public:
    explicit Bullet(QWidget *parent = nullptr, Unit *target = nullptr, bool group_att=0,bool fury=0,bool freeze=0,bool con_att=0,float att_power=0,
                    QPoint pos=QPoint(0,0),int style=0);
    int speed;
    Unit *target;
    QTimer *fly_timer;
    QPixmap photo1, photo2;
    float att_power;
    bool group_att;
    bool fury;
    bool freeze;
    bool con_att;
    void crash();
    void bullet_move();
};

#endif // BULLET_H
