#ifndef SMALLQUICK_H
#define SMALLQUICK_H

#include <QObject>
#include<enemy.h>
class PlayWindow;
class SmallQuick : public Enemy
{
    Q_OBJECT
public:
    explicit SmallQuick(QWidget *parent,PlayWindow *game,int x=-1,int y=-1,int way=0,int nowplace=0);
};

#endif // SMALLQUICK_H
