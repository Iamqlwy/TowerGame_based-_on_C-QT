#ifndef LUBAN_H
#define LUBAN_H

#include <QObject>
#include<longthrower.h>
class LuBan : public LongThrower
{
    Q_OBJECT
public:
    explicit LuBan(QWidget *parent,int x,int y);
};

#endif // LUBAN_H
