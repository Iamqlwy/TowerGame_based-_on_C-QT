#ifndef LIXIN_H
#define LIXIN_H

#include <QObject>
#include<fellow.h>
class LiXin : public Fellow
{
    Q_OBJECT
public:
    explicit LiXin(QWidget *parent, int x,int y);
};

#endif // LIXIN_H
