#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include <QObject>
#include "fellow.h"

#include<bullet.h>

class LongThrower : public Fellow
{
    Q_OBJECT
public:
    explicit LongThrower(QWidget *parent = nullptr,int x=0,int y=0);
    void attack() override;
    int style;//0->houyi,1->luban

};

#endif // LONGTHROWER_H
