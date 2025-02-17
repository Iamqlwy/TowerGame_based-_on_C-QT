#ifndef REGION_H
#define REGION_H

#include <QWidget>
#include<QVector>
#include<QMenu>
#include<QContextMenuEvent>
#include<QMouseEvent>
#include<QLabel>
class Unit;
class Tower;
class Region : public QLabel
{
    Q_OBJECT
public:
    explicit Region(QWidget *parent = nullptr, int x = 0, int y = 0);
    std::pair<int, int> name;
    Region *up, *down, *right, *left;
    QTimer *skill_timer;
    bool on_the_way;
    bool tower_enable;
    bool have_comrade;
    const int x_initial = 80;
    const int y_initial = 80;
    Unit *soilder;
    Tower* tower;
    QVector<Unit*> possess_enemy;
    QMenu *contextMenu;
    QAction *option[6];
    void show_skill1();
    int skill_num;
signals:
    void build(int type, int x, int y);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // REGION_H
