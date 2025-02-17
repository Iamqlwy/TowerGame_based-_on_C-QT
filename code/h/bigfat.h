#ifndef BIGFAT_H
#define BIGFAT_H

#include <QObject>
#include<enemy.h>
class PlayWindow;
class BigFat : public Enemy
{
    Q_OBJECT
public:
    explicit BigFat(QWidget *parent,PlayWindow *game,int x=-1,int y=-1,int way=0,int nowplace=0);
};

#endif // BIGFAT_H
