#include "bullet.h"
#include<playwindow.h>
#include <cmath>  // 包含 cmath 头文件以使用 std::sqrt

Bullet::Bullet(QWidget *parent, Unit *target, bool group_att, bool fury, bool freeze, bool con_att, float att_power, QPoint posi,int style)
    : QLabel(parent), target(target), att_power(att_power),
      group_att(group_att), fury(fury), freeze(freeze), con_att(con_att)
{
    this->move(posi); // 设置子弹的初始位置
    resize(20,20);
    this->show();
    QPixmap pixmap1(":/new/prefix3/projectile_03_01.png");
    QPixmap pixmap2(":/new/prefix3/projectile_19_03.png");
    if(style)setPixmap(pixmap1);
    else setPixmap(pixmap2);
    speed=10;
    fly_timer = new QTimer(this);
    connect(fly_timer, &QTimer::timeout, this, &Bullet::bullet_move);
    fly_timer->start(10);
}

void Bullet::bullet_move()
{
    if (target == nullptr || target->blood <= 0) {
        this->deleteLater();
        return;
    }

    int x = target->pos().x() - this->pos().x();
    int y = target->pos().y() - this->pos().y();
    if (speed >= std::sqrt(x * x + y * y)) {
        this->move(target->pos());
        crash();
    } else {
        this->move(this->pos().x() + speed * x / std::sqrt(x * x + y * y), this->pos().y() + speed * y / std::sqrt(x * x + y * y));
    }
}

void Bullet::crash()
{
    if(target == nullptr || target->blood <= 0)
    {
        this->deleteLater();
        return;
    }

    if(!group_att)
    {
        target->blood -= att_power * (target->base / (target->resistance + target->base));
        target->act_damage();
        target->display_blood();
        if(freeze)
            static_cast<Enemy*>(target)->accept_slow();
        if(con_att)
            static_cast<Enemy*>(target)->continue_damaged();
        qDebug() << "enemy" << target->blood;
        if (target->blood <= 0) {
            target->die();
        }
    }
    else
    {
        QVector<Unit*> store_temp = target->place->possess_enemy;
        for(int i = 0; i < store_temp.size(); i++)
        {
            Enemy *temp = static_cast<Enemy*>(store_temp[i]);
            if (temp != nullptr)
            {
                temp->blood -= att_power * (temp->base / (temp->resistance + temp->base));
                temp->display_blood();
                temp->act_damage();
                if(freeze)
                    temp->accept_slow();
                if(con_att)
                    temp->continue_damaged();

                if (temp->blood <= 0) {
                    temp->die();
                }
            }
        }
    }
    this->deleteLater();
}

