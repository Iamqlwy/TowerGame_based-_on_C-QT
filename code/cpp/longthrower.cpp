#include "longthrower.h"

LongThrower::LongThrower(QWidget *parent,int x,int y) : Fellow(parent,x,y)
{

    dir = 0;

    att_power=500;
    att_interval=100;
    att_timer->start(att_interval);

}

void LongThrower::attack()
{
    att_timer->start(fury ? att_interval / 2 : att_interval);

    Region *target = place;
    bool foundTarget = false;
    while(target != nullptr)
    {
        if(!target->possess_enemy.empty())
        {
            foundTarget = true;
            if(!att_act_timer->isActive())
                att_act_timer->start(att_interval / 4);
            new Bullet(static_cast<QWidget*>(this->parent()), target->possess_enemy[0], group_att, fury, freeze, con_att, att_power, this->pos(), style);
            return;
        }
        if(dir == 0) target = target->right;
        else if(dir == 1) target = target->down;
        else if(dir == 2) target = target->up;
        else if(dir == 3) target = target->left;
    }
    if(!foundTarget) {
        att_act_timer->stop();
        setPixmap(showpixmap[0]);
    }
}

