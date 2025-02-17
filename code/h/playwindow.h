#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include <QSoundEffect>
#include <QWidget>
#include <QVector>
#include <QPixmap>
#include <QMouseEvent>
#include <QPalette>
#include <QPen>
#include <QPainter>
#include "enemy.h"
#include "fellow.h"
#include "region.h"
#include "unit.h"
#include "longthrower.h"
#include "tower.h"
#include<affix.h>
#include<damo.h>
#include<lixin.h>
#include<houyi.h>
#include<luban.h>
#include<bigfat.h>
#include<normal.h>
#include<smallquick.h>
#include<QTimer>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QFileDialog>
#include<pausehandler.h>
#include<QPushButton>
#include<QCloseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayWindow; }
QT_END_NAMESPACE

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr,int x=1,QString name="",bool isnew=true);
    ~PlayWindow();
    QString user_name;

    int number_guanqia;
    void initialize();
    int generate_time;
    QTimer *game;
    QTimer *forcenum;
    QVector<Fellow*> all_soldier;
    QVector<Unit*> all_enemy;
    QVector<Tower*> all_tower;
    QVector<std::pair<int, int>> all_way;
    void load_routine_from_file(const std::string &filename);
    void make_damo(int x, int y);
    void make_lixin(int x, int y);
    void make_houyi(int x, int y);
    void make_luban(int x, int y);
    void make_tower(int x, int y);
    void play_game();
    void paintEvent(QPaintEvent *event) override;
    void set_force_label();
    void win_or_lose(bool win);
    QLabel *force[5];
    QLabel *text[5];
    QLabel *show_level;
    QPushButton *pauseButton; // 暂停按钮
    bool isPaused;
    bool win;
    bool over;
    PauseHandler *pauseHandler; // 自定义事件过滤器

    void pauseGame();
    void resumeGame();
    void togglePause();
    void closeEvent(QCloseEvent *event) override;
    void savedata();
    void loaddata();
    void skill1(int x,int y);
    QString getClassName(Unit *unit);
    QMediaPlayer *player;
    QMediaPlayer *skill1player;

public slots:
    void handleTowerUpdate();
    void build_defense(int type, int x, int y);
signals:
    void open_choose();

private:
    Ui::PlayWindow *ui;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PLAYWINDOW_H
