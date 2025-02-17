#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<playwindow.h>
#include<form.h>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QFileDialog>
#include<choose.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    PlayWindow *game;
    QString name;
    int state;
    bool read;
    Form *check;
    Choose *select;
    void go_in();
    void recieve_data(QString infor);
    void open_file();
    void select_level1();
    void select_level2();
    void select_level3();
    void start_game(int x);
    void update_state();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
