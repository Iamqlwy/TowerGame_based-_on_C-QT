#include "lixin.h"
extern int lixincost;
LiXin::LiXin(QWidget *parent, int x,int y):Fellow(parent,x,y)
{
    cost=lixincost;
    att_power=300;
    resistance=100;
    att_interval=1000;
    init_blood=6000;
    blood=6000;
    att_act[0]=QPixmap(":/new/prefix2/hero_07_attack_01.png");
    att_act[1]=QPixmap(":/new/prefix2/hero_07_attack_02.png");
    att_act[2]=QPixmap(":/new/prefix2/hero_07_attack_03.png");
    att_act[3]=QPixmap(":/new/prefix2/hero_07_attack_04.png");
    att_act[4]=QPixmap(":/new/prefix2/hero_07_damage_01.png");
    showpixmap[0]=QPixmap(":/new/prefix2/hero_07_attack_01.png");
        showpixmap[1]=QPixmap(":/new/prefix2/hero_07_attack_02.png");
        showpixmap[2]=QPixmap(":/new/prefix2/hero_07_attack_03.png");
        showpixmap[3]=QPixmap(":/new/prefix2/hero_07_attack_04.png");
        showpixmap[4]=QPixmap(":/new/prefix2/hero_07_damage_01.png");

    setPixmap(att_act[0]);
}
