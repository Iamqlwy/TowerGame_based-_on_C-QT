#ifndef FELLOW_H
#define FELLOW_H

#include <QObject>
#include<enemy.h>
#include<unit.h>
#include<QAction>
#include<QMenu>
#include <QContextMenuEvent>
#include <QCursor>
class Fellow : public Unit
{
    Q_OBJECT
public:
    explicit Fellow(QWidget *parent=nullptr,int x=0,int y=0);


    int base_time;
    int cost;
    bool group_att;
    bool fury;
    bool freeze;
    bool con_att;
    QTimer *group_att_timer,*fury_timer,*freeze_timer,*con_att_timer;
    void attack()override;
    void die()override;
    void change_dir();
    void stop_current_timer(int index);
    void move(const QPoint &pos) override;
    void replace_weaker_timer(int new_stren_force);
    void updateAffixImage(int new_stren_force, int index);

    void updateOptions();
    QMenu *contextMenu;
    QAction *option[5];



protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
public slots:
    void stren_group_att();
    void stren_fury();
    void stren_freeze();
    void stren_con_att();

};

#endif // FELLOW_H
