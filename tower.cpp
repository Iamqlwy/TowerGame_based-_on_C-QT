#include "tower.h"
#include <QPainter>
#include <QDebug>
extern const int towercost;
Tower::Tower(QWidget *parent, int x, int y)
    : QLabel(parent), mode(false), att_power(20)
{
    cost=towercost;
    att_timer = new QTimer(this);
    draw_timer=new QTimer(this);
    place = map[x][y];
    place->tower=this;
    move(place->pos());
    att_place.append(place->right);
    if(place->right!=nullptr)
    {
        att_place.append(place->right->up);
        att_place.append(place->right->down);
    }

    att_place.append(place->up);
    att_place.append(place->down);

    att_place.append(place->left);
    if(place->left!=nullptr){
        att_place.append(place->left->down);
        att_place.append(place->left->up);
    }
    att_place.removeAll(nullptr);

    connect(att_timer, &QTimer::timeout, this, &Tower::attack);
    connect(draw_timer,&QTimer::timeout,this,[this]{emit request_update();});
    att_timer->start(300);
    draw_timer->start(16);
    QPixmap pixmap(":/new/prefix3/tower.png");
    setPixmap(pixmap);
}

void Tower::attack()
{
    for (int i = 0; i < att_place.size(); i++)
    {
        for (int j = 0; j < att_place[i]->possess_enemy.size(); j++)
        {
            if(att_place[i]->possess_enemy[j]==nullptr || att_place[i]->possess_enemy[j]->blood<=0) continue;
            att_place[i]->possess_enemy[j]->damage(0.1*att_place[i]->possess_enemy[j]->init_blood);
            qDebug()<<123123;
        }
    }

}

void Tower::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen(Qt::red, 2);
    painter.setPen(pen);

    for (int i = 0; i < att_place.size(); i++)
    {
        for (int j = 0; j < att_place[i]->possess_enemy.size(); j++)
        {
            painter.drawLine(this->pos(), att_place[i]->possess_enemy[j]->pos());
        }
    }
}

QPoint Tower::towerPosition() const
{
    return mapToGlobal(rect().center());
}

QPoint Tower::targetPosition(Unit *target) const
{
    return mapFromParent(target->mapToGlobal(target->rect().center()));
}
