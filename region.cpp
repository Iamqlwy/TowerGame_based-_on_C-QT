#include "region.h"
#include "unit.h"
extern int money;
extern int damocost;
extern int lixincost;
extern int houyicost;
extern int lubancost;
extern int towercost;
extern int skill1_cost;
Region::Region(QWidget *parent, int x, int y) : QLabel(parent)
{
    name.first = x;

    name.second = y;
    tower=nullptr;
    soilder=nullptr;
    tower_enable=false;
    this->setGeometry(x_initial + 60 * y, y_initial + 60 * x, 60, 60);
    on_the_way = false;
    have_comrade = false;
    contextMenu = new QMenu(this);
    for (int i = 0; i < 6; i++) {
        option[i] = new QAction(this);
        contextMenu->addAction(option[i]);
    }
    skill_num=0;
    skill_timer=new QTimer(this);
    skill_timer->setSingleShot(true);
    option[0]->setText("达摩");
    option[1]->setText("李信");
    option[2]->setText("后羿");
    option[3]->setText("鲁班");
    option[4]->setText("防御塔");
    option[5]->setText("雷霆万钧");
    connect(option[0], &QAction::triggered, this, [this] { emit build(0, name.first, name.second); });
    connect(option[1], &QAction::triggered, this, [this] { emit build(1, name.first, name.second); });
    connect(option[2], &QAction::triggered, this, [this] { emit build(2, name.first, name.second); });
    connect(option[3], &QAction::triggered, this, [this] { emit build(3, name.first, name.second); });
    connect(option[4],&QAction::triggered,this,[this]{emit build(4, name.first, name.second);});
    connect(option[5],&QAction::triggered,this,[this]{emit build(5, name.first, name.second);show_skill1();});
    connect(skill_timer,&QTimer::timeout,this,[this]{this->clear();});


}

void Region::contextMenuEvent(QContextMenuEvent *event)
{
    for(int i=0;i<5;i++)
    {
        option[i]->setEnabled(true);
    }
    if(on_the_way)
    {
        option[4]->setEnabled(false);
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            option[i]->setEnabled(false);
        }
    }
    if(money<damocost)
    {
        option[0]->setEnabled(false);
    }
    if(money<lixincost)
    {
        option[1]->setEnabled(false);
    }
    if(money<houyicost)
    {
        option[2]->setEnabled(false);
    }
    if(money<lubancost)
    {
        option[3]->setEnabled(false);
    }
    if(money<towercost)
    {
        option[4]->setEnabled(false);
    }
    if(money<skill1_cost)
    {
        option[5]->setEnabled(false);
    }
    contextMenu->exec(event->globalPos());
}

void Region::enterEvent(QEvent *event)
{
    setCursor(Qt::CrossCursor);
    setStyleSheet("QLabel { border: 2px solid black; }");
    QWidget::enterEvent(event);
}

void Region::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
    setStyleSheet("");
    QWidget::leaveEvent(event);
}
void Region::show_skill1()
{

        QPixmap pixmap(":/new/prefix3/skill1.png");
        setPixmap(pixmap);
        skill_timer->start(500);

}
