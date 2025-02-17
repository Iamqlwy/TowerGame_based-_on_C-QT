#include "bigfat.h"

BigFat::BigFat(QWidget *parent,PlayWindow *game,int x,int y,int way,int nowplace) :Enemy(parent,game,x,y,way,nowplace)
{
    init_interval=2000;
    interval=init_interval;
    init_blood=5000;
    blood=5000;
    att_power=200;
    resistance=500;

    showpixmap[0]=QPixmap(":/new/prefix1/enemy_08_attack_01.png");
    showpixmap[1]=QPixmap(":/new/prefix1/enemy_08_attack_02.png");
    showpixmap[2]=QPixmap(":/new/prefix1/enemy_08_attack_03.png");
    showpixmap[3]=QPixmap(":/new/prefix1/enemy_08_attack_04.png");
    showpixmap[4]=QPixmap(":/new/prefix1/enemy_08_damage_01.png");
    showpixmap[5]=QPixmap(":/new/prefix1/enemy_08_move_01.png");
    showpixmap[6]=QPixmap(":/new/prefix1/enemy_08_move_02.png");

    setPixmap(showpixmap[5]);

    move_timer->start(interval);

}
