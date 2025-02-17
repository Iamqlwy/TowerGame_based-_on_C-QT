#include "mainwindow.h"

#include <QApplication>
class Region;
Region *map[12][12];
int time_group_att=1500;
int time_fury=1500;
int time_freeze=1500;
int time_con_att=1500;
int money=100;
int damocost=10;
int lixincost=10;
int houyicost=20;
int lubancost=25;
int towercost=50;
int basenum=1500;
int skill1_cost=100;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
