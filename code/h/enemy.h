#ifndef ENEMY_H
#define ENEMY_H
class PlayWindow;
#include <QObject>
#include<unit.h>
#include<QRandomGenerator>
#include<fstream>
#include<sstream>
#include<QPropertyAnimation>
#include<affix.h>
#include<QMouseEvent>
class PlayWindow;
class Enemy : public Unit
{
    Q_OBJECT
public:
    static bool reach;
    explicit Enemy(QWidget *parent=nullptr,PlayWindow *game=nullptr,int x=-1,int y=-1,int way=0,int nowplace=0);
    float speed;
    int available[2];
    bool freezing;
    bool con_att_ing;
    bool flash;
    QVector<std::pair<int ,int>>routine;
    int cur_place=0;
    Region* place_next;
    QTimer *move_timer;
    QTimer *con_timer;
    QTimer *slow_timer;
    QTimer *accelerate_timer;
    int theway;
    int continue_damaged_left_time;
    int init_interval;
    int interval;
    int move_pic_num;
    PlayWindow *parentWindow;
    void enemy_move();
    void load_routine_from_file(const std::string &filename, int way);
    void attack() override;
    void die() override;
    void accept_slow();
    void start_continue_damaged();
    void continue_damaged();
    void accelerate();
    void stren();
    void move_act();

};

#endif // ENEMY_H
