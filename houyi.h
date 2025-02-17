#ifndef HOUYI_H
#define HOUYI_H

#include <QObject>
#include<longthrower.h>
class HouYi : public LongThrower
{
    Q_OBJECT
public:
    explicit HouYi(QWidget *parent,int x,int y);
};

#endif // HOUYI_H
