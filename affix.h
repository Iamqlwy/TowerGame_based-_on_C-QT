#ifndef AFFIX_H
#define AFFIX_H

#include <QObject>
#include<QLabel>
#include<QTimer>
#include<QMouseEvent>
#include<QRandomGenerator>
class Affix : public QLabel
{
    Q_OBJECT
public:
    explicit Affix(QWidget *parent,QPoint pos);
    int get;
    int type;
    int time;
    QTimer *disappear;
protected:
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // AFFIX_H
