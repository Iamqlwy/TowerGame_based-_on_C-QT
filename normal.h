#ifndef NORMAL_H
#define NORMAL_H

#include <QObject>
#include<enemy.h>
class PlayWindow;
class Normal : public Enemy
{
    Q_OBJECT
public:
    explicit Normal(QWidget *parent,PlayWindow *game,int x=-1,int y=-1,int way=0,int nowplace=0);
};

#endif // NORMAL_H
