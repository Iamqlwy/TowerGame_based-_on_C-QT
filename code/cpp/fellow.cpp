#include "fellow.h"

extern Region *map[12][12];

extern int time_group_att;
extern int time_fury;
extern int time_freeze;
extern int time_con_att;

Fellow::Fellow(QWidget *parent, int x, int y) : Unit(parent)
{
    stren_force[0] = -1;
    stren_force[1] = -1;
    att_interval = 100;
    base_time = 5000;
    att_power = 2;
    blood = 1000;
    dir = 0;
    comrade = true;
    group_att = false;
    fury = false;
    freeze = false;
    con_att = false;
    group_att_timer = new QTimer(this);
    fury_timer = new QTimer(this);
    freeze_timer = new QTimer(this);
    con_att_timer = new QTimer(this);
    group_att_timer->setSingleShot(true);
    fury_timer->setSingleShot(true);
    freeze_timer->setSingleShot(true);
    con_att_timer->setSingleShot(true);
    place = map[x][y];
    place->soilder = this;
    place->have_comrade = true;
    this->move(place->pos());
    connect(att_timer, &QTimer::timeout, this, &Fellow::attack);
    connect(group_att_timer, &QTimer::timeout, this, [this] {
        group_att = false;
        for (int i = 0; i < 2; ++i) {
            if (stren_force[i] == 0) {
                stren_force[i] = -1;
                affix[i]->clear();
                break;
            }
        }
        updateOptions();
    });
    connect(fury_timer, &QTimer::timeout, this, [this] {
        fury = false;
        att_power *= 0.5;
        for (int i = 0; i < 2; ++i) {
            if (stren_force[i] == 1) {
                stren_force[i] = -1;
                affix[i]->clear();
                break;
            }
        }
        updateOptions();
    });
    connect(freeze_timer, &QTimer::timeout, this, [this] {
        freeze = false;
        for (int i = 0; i < 2; ++i) {
            if (stren_force[i] == 2) {
                stren_force[i] = -1;
                affix[i]->clear();
                break;
            }
        }
        updateOptions();
    });
    connect(con_att_timer, &QTimer::timeout, this, [this] {
        con_att = false;
        for (int i = 0; i < 2; ++i) {
            if (stren_force[i] == 3) {
                stren_force[i] = -1;
                affix[i]->clear();
                break;
            }
        }
        updateOptions();
    });
    att_timer->start(att_interval);

    contextMenu = new QMenu(this);
    option[0] = new QAction("群伤", this);
    option[1] = new QAction("狂暴", this);
    option[2] = new QAction("冰冷", this);
    option[3] = new QAction("流血", this);
    option[4] = new QAction("删除", this);
    contextMenu->addAction(option[0]);
    contextMenu->addAction(option[1]);
    contextMenu->addAction(option[2]);
    contextMenu->addAction(option[3]);
    contextMenu->addAction(option[4]);
    connect(option[0], &QAction::triggered, this, &Fellow::stren_group_att);
    connect(option[1], &QAction::triggered, this, &Fellow::stren_fury);
    connect(option[2], &QAction::triggered, this, &Fellow::stren_freeze);
    connect(option[3], &QAction::triggered, this, &Fellow::stren_con_att);
    connect(option[4], &QAction::triggered, this, [this] { this->die(); });
}

void Fellow::attack()
{
    Region *att_place;
    switch (dir)
    {
    case 0:
        att_place = place->right;
        break;
    case 1:
        att_place = place->down;
        break;
    case 2:
        att_place = place->up;
        break;
    case 3:
        att_place = place->left;
        break;
    default:
        att_place = nullptr;
    }
    if (att_place == nullptr)
        return;

    att_timer->start(fury ? att_interval / 2 : att_interval);

    bool foundEnemy = false;
    for (int i = 0; i < att_place->possess_enemy.size(); ++i)
    {
        Enemy *temp = static_cast<Enemy *>(att_place->possess_enemy[i]);
        if (temp->blood <= 0)
            continue;

        foundEnemy = true;
        att_act_timer->start(att_interval / 4);
        temp->blood -= att_power * (temp->base / (temp->resistance + temp->base));
        temp->display_blood();
        temp->act_damage();

        if (temp->blood <= 0)
        {
            temp->die();
        }

        if (freeze)
        {
            temp->accept_slow();
        }

        if (con_att)
        {
            temp->continue_damaged();
        }

        if (!group_att)
        {
            return;
        }
    }

    if (!foundEnemy)
    {
        att_act_timer->stop();
        setPixmap(showpixmap[0]);
    }
}

void Fellow::stop_current_timer(int index)
{
    if (stren_force[index] == 0)
    {
        time_group_att += group_att_timer->remainingTime();
        group_att_timer->stop();
    }
    else if (stren_force[index] == 1)
    {
        time_fury += fury_timer->remainingTime();
        fury_timer->stop();
    }
    else if (stren_force[index] == 2)
    {
        time_freeze += freeze_timer->remainingTime();
        freeze_timer->stop();
    }
    else if (stren_force[index] == 3)
    {
        time_con_att += con_att_timer->remainingTime();
        con_att_timer->stop();
    }

    stren_force[index] = -1;
    affix[index]->clear();
    updateOptions();
}

void Fellow::replace_weaker_timer(int new_stren_force)
{
    int remaining_time_0 = 0;
    int remaining_time_1 = 0;

    if (stren_force[0] == 0)
        remaining_time_0 = group_att_timer->remainingTime();
    else if (stren_force[0] == 1)
        remaining_time_0 = fury_timer->remainingTime();
    else if (stren_force[0] == 2)
        remaining_time_0 = freeze_timer->remainingTime();
    else if (stren_force[0] == 3)
        remaining_time_0 = con_att_timer->remainingTime();

    if (stren_force[1] == 0)
        remaining_time_1 = group_att_timer->remainingTime();
    else if (stren_force[1] == 1)
        remaining_time_1 = fury_timer->remainingTime();
    else if (stren_force[1] == 2)
        remaining_time_1 = freeze_timer->remainingTime();
    else if (stren_force[1] == 3)
        remaining_time_1 = con_att_timer->remainingTime();

    int replaced_index = (remaining_time_0 <= remaining_time_1) ? 0 : 1;

    stop_current_timer(replaced_index);

    if (stren_force[0] == -1)
        stren_force[0] = new_stren_force;
    else
        stren_force[1] = new_stren_force;

    updateAffixImage(new_stren_force, replaced_index);
    updateOptions();
}

void Fellow::updateOptions()
{
    if (stren_force[0] == -1 && stren_force[1] == -1)
    {
        option[0]->setText("群伤");
        option[1]->setText("狂暴");
        option[2]->setText("冰冷");
        option[3]->setText("流血");
    }
    else
    {
        option[0]->setText("群伤替换");
        option[1]->setText("狂暴替换");
        option[2]->setText("冰冷替换");
        option[3]->setText("流血替换");
        if (stren_force[0] == -1 || stren_force[1] == -1)
        {
            if (stren_force[0] == 0 || stren_force[1] == 0)
                option[0]->setText("群伤卸载");
            if (stren_force[0] == 1 || stren_force[1] == 1)
                option[1]->setText("狂暴卸载");
            if (stren_force[0] == 2 || stren_force[1] == 2)
                option[2]->setText("冰冷卸载");
            if (stren_force[0] == 3 || stren_force[1] == 3)
                option[3]->setText("流血卸载");
        }
    }
}

void Fellow::updateAffixImage(int new_stren_force, int index)
{
    QPixmap pixmap;
    switch (new_stren_force)
    {
    case 0:
        pixmap = QPixmap(":/new/prefix3/group_att.png");
        group_att_timer->start(base_time);
        group_att = true;
        time_group_att -= base_time;
        break;
    case 1:
        pixmap = QPixmap(":/new/prefix3/fury.png");
        fury_timer->start(base_time);
        fury = true;
        time_fury -= base_time;
        att_power *= 2;
        break;
    case 2:
        pixmap = QPixmap(":/new/prefix3/freeze.png");
        freeze_timer->start(base_time);
        freeze = true;
        time_freeze -= base_time;
        break;
    case 3:
        pixmap = QPixmap(":/new/prefix3/con_att.png");
        con_att_timer->start(base_time);
        con_att = true;
        time_con_att -= base_time;
        break;
    }

    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    affix[index]->setPixmap(scaledPixmap);
}

void Fellow::stren_group_att()
{
    if (stren_force[0] == 0 || stren_force[1] == 0)
    {
        if (stren_force[0] == 0)
            stop_current_timer(0);
        else
            stop_current_timer(1);
        return;
    }

    if (stren_force[0] == -1 || stren_force[1] == -1)
    {
        if (stren_force[0] == -1)
            stren_force[0] = 0;
        else
            stren_force[1] = 0;

        option[0]->setText("群伤卸载");

        if (time_group_att >= base_time)
        {
            QPixmap pixmap(":/new/prefix3/group_att.png");
            QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (stren_force[0] == 0)
                affix[0]->setPixmap(scaledPixmap);
            else
                affix[1]->setPixmap(scaledPixmap);

            group_att_timer->start(base_time);
            group_att = true;
            time_group_att -= base_time;
        }
    }
    else
    {
        replace_weaker_timer(0);
    }

    updateOptions();
}

void Fellow::stren_fury()
{
    if (stren_force[0] == 1 || stren_force[1] == 1)
    {
        if (stren_force[0] == 1)
            stop_current_timer(0);
        else
            stop_current_timer(1);
        return;
    }

    if (stren_force[0] == -1 || stren_force[1] == -1)
    {
        if (stren_force[0] == -1)
            stren_force[0] = 1;
        else
            stren_force[1] = 1;

        option[1]->setText("狂暴卸载");

        if (time_fury >= base_time)
        {
            QPixmap pixmap(":/new/prefix3/fury.png");
            QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (stren_force[0] == 1)
                affix[0]->setPixmap(scaledPixmap);
            else
                affix[1]->setPixmap(scaledPixmap);

            fury_timer->start(base_time);
            fury = true;
            time_fury -= base_time;
            att_power *= 2;
        }
    }
    else
    {
        replace_weaker_timer(1);
    }

    updateOptions();
}

void Fellow::stren_freeze()
{
    if (stren_force[0] == 2 || stren_force[1] == 2)
    {
        if (stren_force[0] == 2)
            stop_current_timer(0);
        else
            stop_current_timer(1);
        return;
    }

    if (stren_force[0] == -1 || stren_force[1] == -1)
    {
        if (stren_force[0] == -1)
            stren_force[0] = 2;
        else
            stren_force[1] = 2;

        option[2]->setText("冰冷卸载");

        if (time_freeze >= base_time)
        {
            QPixmap pixmap(":/new/prefix3/freeze.png");
            QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (stren_force[0] == 2)
                affix[0]->setPixmap(scaledPixmap);
            else
                affix[1]->setPixmap(scaledPixmap);

            freeze_timer->start(base_time);
            freeze = true;
            time_freeze -= base_time;
        }
    }
    else
    {
        replace_weaker_timer(2);
    }

    updateOptions();
}

void Fellow::stren_con_att()
{
    if (stren_force[0] == 3 || stren_force[1] == 3)
    {
        if (stren_force[0] == 3)
            stop_current_timer(0);
        else
            stop_current_timer(1);
        return;
    }

    if (stren_force[0] == -1 || stren_force[1] == -1)
    {
        if (stren_force[0] == -1)
            stren_force[0] = 3;
        else
            stren_force[1] = 3;

        option[3]->setText("流血卸载");

        if (time_con_att >= base_time)
        {
            QPixmap pixmap(":/new/prefix3/con_att.png");
            QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (stren_force[0] == 3)
                affix[0]->setPixmap(scaledPixmap);
            else
                affix[1]->setPixmap(scaledPixmap);

            con_att_timer->start(base_time);
            con_att = true;
            time_con_att -= base_time;
        }
    }
    else
    {
        replace_weaker_timer(3);
    }

    updateOptions();
}

void Fellow::die()
{
    place->have_comrade = false;
    this->blood_show->hide();
    this->place->soilder = nullptr;
    this->place = nullptr;
    this->deleteLater();
}

void Fellow::change_dir()
{
    dir = (dir + 1) % 4;
    if (dir == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            showpixmap[i] = att_act[i];
        }
    }
    else if (dir == 1)
    {
        QTransform transform;
        transform.rotate(90);
        for (int i = 0; i < 5; i++)
        {
            showpixmap[i] = att_act[i].transformed(transform);
        }
    }
    else if (dir == 2)
    {
        QTransform transform;
        transform.rotate(270);
        for (int i = 0; i < 5; i++)
        {
            showpixmap[i] = att_act[i].transformed(transform);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            showpixmap[i] = att_act[i].transformed(QTransform().scale(-1, 1));
        }
    }
    setPixmap(showpixmap[0]);
}

void Fellow::contextMenuEvent(QContextMenuEvent *event)
{
    contextMenu->exec(event->globalPos());
}

void Fellow::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QLabel::enterEvent(event);
}

void Fellow::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QLabel::leaveEvent(event);
}

void Fellow::move(const QPoint &pos)
{
    Unit::move(pos);
}
