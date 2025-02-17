#include "smallquick.h"

SmallQuick::SmallQuick(QWidget *parent,PlayWindow*game,int x,int y,int way,int nowplace) :Enemy(parent,game,x,y,way,nowplace)
{
    init_interval=500;
    interval=init_interval;
    init_blood=1500;
    blood=1500;
    att_power=80;
    resistance=0;

    showpixmap[0]=QPixmap(":/new/prefix1/enemy_04_attack_01.png");
    showpixmap[1]=QPixmap(":/new/prefix1/enemy_04_attack_02.png");
    showpixmap[2]=QPixmap(":/new/prefix1/enemy_04_attack_03.png");
    showpixmap[3]=QPixmap(":/new/prefix1/enemy_04_attack_04.png");
    showpixmap[4]=QPixmap(":/new/prefix1/enemy_04_damage_01.png");
    showpixmap[5]=QPixmap(":/new/prefix1/enemy_04_move_01.png");
    showpixmap[6]=QPixmap(":/new/prefix1/enemy_04_move_02.png");

    setPixmap(showpixmap[5]);
    move_timer->start(interval);
}
