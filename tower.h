#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include "region.h"
#include "unit.h"

extern Region* map[12][12];

class Tower : public QLabel
{
    Q_OBJECT
public:
    explicit Tower(QWidget *parent = nullptr, int x = 0, int y = 0);
    bool mode;
    int cost;
    QTimer *att_timer;
    float att_power;
    QVector<Region *> att_place;
    Region *place;
    QTimer *draw_timer;
    void attack();
signals:
    void request_update();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint towerPosition() const;
    QPoint targetPosition(Unit *target) const;
};

#endif // TOWER_H
