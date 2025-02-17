#include "houyi.h"
extern int houyicost;
HouYi::HouYi(QWidget *parent,int x,int y):LongThrower(parent,x,y)
{
    cost=houyicost;
    style=0;
    att_power=600;
    resistance=20;
    att_interval=1000;
    init_blood=1200;
    blood=1200;
    att_act[0]=QPixmap(":/new/prefix2/hero_02_attack_01.png");
    att_act[1]=QPixmap(":/new/prefix2/hero_02_attack_02.png");
    att_act[2]=QPixmap(":/new/prefix2/hero_02_attack_03.png");
    att_act[3]=QPixmap(":/new/prefix2/hero_02_attack_04.png");
    att_act[4]=QPixmap(":/new/prefix2/hero_02_damage_01.png");
    showpixmap[0]=QPixmap(":/new/prefix2/hero_02_attack_01.png");
    showpixmap[1]=QPixmap(":/new/prefix2/hero_02_attack_02.png");
    showpixmap[2]=QPixmap(":/new/prefix2/hero_02_attack_03.png");
    showpixmap[3]=QPixmap(":/new/prefix2/hero_02_attack_04.png");
    showpixmap[4]=QPixmap(":/new/prefix2/hero_02_damage_01.png");

    setPixmap(att_act[0]);
}
