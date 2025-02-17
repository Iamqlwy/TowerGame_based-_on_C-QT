#include "enemy.h"

bool Enemy ::reach=false;
extern Region *map[12][12];
#include<playwindow.h>
Enemy::Enemy(QWidget *parent,PlayWindow *game,int x,int y,int way,int nowplace):Unit(parent),parentWindow(game)
{
    init_interval=1000;
    move_pic_num=0;
    available[0]=0;
    available[1]=0;
    att_power=1;
    interval=init_interval;
    blood=1000;
    flash=false;
    continue_damaged_left_time=-1;
    int waychosse;
    if(way==0)
        if(game->number_guanqia!=3)
            waychosse = QRandomGenerator::global()->bounded(1,3+game->number_guanqia);
        else  waychosse = QRandomGenerator::global()->bounded(1,3);
    else
        waychosse=way;
    theway=waychosse;
    cur_place=nowplace;
    //qDebug()<<random_way;
    std::string road="ways"+std::to_string(game->number_guanqia)+".txt";
    load_routine_from_file(road,waychosse);
    move_timer=new QTimer(this);
    att_timer=new QTimer(this);
    slow_timer=new QTimer(this);
    con_timer=new QTimer(this);
    accelerate_timer=new QTimer(this);
    comrade=false;
    if(x==-1 && y==-1)

        place=map[routine[cur_place].first][routine[cur_place].second];


    else
    {
        place=map[x][y];
    }
    place->possess_enemy.append(this);
    game->all_enemy.append(this);
    //qDebug()<<place->name;
    place_next= map[routine[cur_place+1].first][routine[cur_place+1].second];
    connect(att_timer,&QTimer::timeout,this,&Enemy::attack);
    connect(move_timer,&QTimer::timeout,this,&Enemy::enemy_move);
    connect(move_timer,&QTimer::timeout,this,&Enemy::move_act);
    slow_timer->setSingleShot(true);
    accelerate_timer->setSingleShot(true);
    connect(slow_timer,&QTimer::timeout,this,[this]{interval=init_interval;move_timer->stop();move_timer->start(interval);});
    connect(con_timer,&QTimer::timeout,this,&Enemy::continue_damaged);
    connect(accelerate_timer,&QTimer::timeout,this,[this]{interval=init_interval;if(available[0]==2)affix[0]->clear();if(available[1]==2)affix[1]->clear();});
    this->move(place->pos());
    move_timer->start(interval);
    show();
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

}

void Enemy::load_routine_from_file(const std::string &filename, int way) {
    std::ifstream infile(filename);
    if (!infile) {
        //qDebug() << "无法打开文件。";
        return;
    }

    std::string line;
    std::string target_way = "way" + std::to_string(way);
    bool found_way = false;

    while (std::getline(infile, line)) {
        if (line == target_way) {
            found_way = true;
            break;
        }
    }

    if (!found_way) {
        //qDebug() << "在文件中没有找到路径。";
        return;
    }

    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string coord;
        while (iss >> coord) {
            coord = coord.substr(1, coord.size() - 2);  // 去掉括号
            size_t comma_pos = coord.find(',');
            int x = std::stoi(coord.substr(0, comma_pos));
            int y = std::stoi(coord.substr(comma_pos + 1));
            //qDebug()<<x<<y;
            routine.append(std::make_pair(x, y));
        }
    }

    if (routine.isEmpty()) {
        //qDebug() << "路径向量为空。";
    } else {
        //qDebug() << "路径加载完成，步数：" << routine.size();
    }
}



void Enemy::enemy_move() {
    if (place_next == nullptr) {
        move_timer->stop();
        return;
    }

    if (place_next->have_comrade) {
        if (flash) {
            flash = false;

            if(available[0]==1)affix[0]->clear();if(available[1]==1)affix[1]->clear();
            if (cur_place + 3 >= routine.size()) {
                move(map[routine.back().first][routine.back().second]->pos());
                Enemy::reach = true;
                move_timer->stop();
                return;
            } else {
                cur_place += 2;
                place = map[routine[cur_place].first][routine[cur_place].second];
                place_next = map[routine[cur_place + 1].first][routine[cur_place + 1].second];
            }
        }
        if (!att_act_timer->isActive())
            att_act_timer->start(interval / 4);
        if (!att_timer->isActive())
            att_timer->start(interval / 2);
    } else {
        att_timer->stop();
        att_act_timer->stop();
        QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
        animation->setDuration(interval);
        animation->setStartValue(this->pos());
        animation->setEndValue(place_next->pos());
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        setPixmap(showpixmap[5]);


        QTimer::singleShot(interval / 2, this, [this]() {
            cur_place++;
            place->possess_enemy.removeOne(this);
            place = place_next;

            if (cur_place + 1 < routine.size()) {
                place_next = map[routine[cur_place + 1].first][routine[cur_place + 1].second];
            } else {
                Enemy::reach = true;
                place_next = nullptr;
                move_timer->stop();
                return;
            }
            if (place != nullptr)
                place->possess_enemy.append(this);
        });


        if (cur_place + 1 >= routine.size()) {
            move_timer->stop();
        }
    }
}

void Enemy::die()
{
    this->hide();
    this->blood_show->hide();
    this->place->possess_enemy.removeOne(this);
    parentWindow->all_enemy.removeOne(this);
    Affix *a=new Affix(static_cast<QWidget *>(this->parent()), this->pos());
    a->show();
    this->place=nullptr;
    this->deleteLater();
}

void Enemy::attack()
{
    Region *att_place = place_next;

    if(att_place && att_place->have_comrade && att_place->soilder && att_place->soilder->blood > 0)
    {
        att_place->soilder->blood -= att_power * (att_place->soilder->base / (att_place->soilder->resistance + att_place->soilder->base));
        att_place->soilder->display_blood();
        att_place->soilder->act_damage();
        if(att_place->soilder->blood <= 0)
        {
            stren();
            att_place->soilder->die();
            att_timer->stop();
        }
    }
    else
    {
        att_timer->stop();
    }
}


void Enemy::accept_slow()
{
    if(interval==init_interval)
    {
        interval=3*init_interval;
        move_timer->start(interval);
    }
    slow_timer->start(5000);


}

void Enemy::start_continue_damaged()
{
    if(!con_timer->isActive())
        con_timer->start(1000);


}

void Enemy::continue_damaged()
{
    if(blood<=0)return;
    if(continue_damaged_left_time==0)
    {
        con_timer->stop();
        continue_damaged_left_time=5;
        return;
    }
    blood-=blood/20;
    continue_damaged_left_time--;
    if(blood<=0)
    {
        con_timer->stop();
        die();
    }
}

void Enemy::accelerate()
{
    if(interval>=init_interval){
        interval=init_interval*0.33;
        move_timer->start(interval);
        accelerate_timer->start(5000);
        QPixmap pixmap(":/new/prefix3/accelerate.png");
        QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if(available[0]==0)
                {
                affix[0]->setPixmap(scaledPixmap);
                available[0]=2;
        }
        else{

            affix[1]->setPixmap(scaledPixmap);
            available[1]=2;
        }
    }
}

void Enemy::stren()
{

    int x=QRandomGenerator::global()->bounded(1,3);
    if(x==1)
    {
        flash=true;
        QPixmap pixmap(":/new/prefix3/flash.png");
        QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if(available[0]==0)
                {
                affix[0]->setPixmap(scaledPixmap);
                available[0]=1;
        }
        else{

            affix[1]->setPixmap(scaledPixmap);
            available[1]=1;
        }
    }
    else if(x==2)
    {
        accelerate();
    }
}
void Enemy::move_act()
{
    if(move_pic_num==0)
        setPixmap(showpixmap[5]);
    else
        setPixmap(showpixmap[6]);
    move_pic_num=1-move_pic_num;

}
