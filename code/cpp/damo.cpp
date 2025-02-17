#include "damo.h"
extern int damocost;

DaMo::DaMo(QWidget *parent,int x,int y):Fellow(parent,x,y)
{

    cost=damocost;
    att_power=50;
    resistance=600;
    att_interval=1000;
    init_blood=10000000;
    blood=10000000;
    att_act[0]=QPixmap(":/new/prefix2/hero_05_attack_01.png");
    att_act[1]=QPixmap(":/new/prefix2/hero_05_attack_02.png");
    att_act[2]=QPixmap(":/new/prefix2/hero_05_attack_03.png");
    att_act[3]=QPixmap(":/new/prefix2/hero_05_attack_04.png");
    att_act[4]=QPixmap(":/new/prefix2/hero_05_damage_01.png");
    showpixmap[0]=QPixmap(":/new/prefix2/hero_05_attack_01.png");
    showpixmap[1]=QPixmap(":/new/prefix2/hero_05_attack_02.png");
    showpixmap[2]=QPixmap(":/new/prefix2/hero_05_attack_03.png");
    showpixmap[3]=QPixmap(":/new/prefix2/hero_05_attack_04.png");
    showpixmap[4]=QPixmap(":/new/prefix2/hero_05_damage_01.png");

    setPixmap(att_act[0]);
}
