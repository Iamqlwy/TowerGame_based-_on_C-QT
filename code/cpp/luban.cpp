#include "luban.h"
extern int lubancost;
LuBan::LuBan(QWidget *parent,int x,int y):LongThrower(parent,x,y)
{
    cost=lubancost;
    style=1;
    att_power=700;
    resistance=20;
    att_interval=400;
    init_blood=1600;
    blood=1600;
    att_act[0]=QPixmap(":/new/prefix2/hero_04_attack_01.png");
    att_act[1]=QPixmap(":/new/prefix2/hero_04_attack_02.png");
    att_act[2]=QPixmap(":/new/prefix2/hero_04_attack_03.png");
    att_act[3]=QPixmap(":/new/prefix2/hero_04_attack_04.png");
    att_act[4]=QPixmap(":/new/prefix2/hero_04_damage_01.png");
    showpixmap[0]=QPixmap(":/new/prefix2/hero_04_attack_01.png");
    showpixmap[1]=QPixmap(":/new/prefix2/hero_04_attack_02.png");
    showpixmap[2]=QPixmap(":/new/prefix2/hero_04_attack_03.png");
    showpixmap[3]=QPixmap(":/new/prefix2/hero_04_attack_04.png");
    showpixmap[4]=QPixmap(":/new/prefix2/hero_04_damage_01.png");

    setPixmap(att_act[0]);
}
