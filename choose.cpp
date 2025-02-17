#include "choose.h"
#include "ui_choose.h"

Choose::Choose(QWidget *parent,int state,QString name) :
    QWidget(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
    setFixedSize(400,400);

    if(state==1)
    {ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);}
    else if(state==2)
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
    }
    setWindowTitle(name);
    connect(ui->pushButton,&QPushButton::clicked,this,[this]{emit level1();close();});
    connect(ui->pushButton_2,&QPushButton::clicked,this,[this]{emit level2();close();});
    connect(ui->pushButton_3,&QPushButton::clicked,this,[this]{emit level3();close();});

}

Choose::~Choose()
{
    delete ui;
}
void Choose::set_state(int x)
{
    if(x==1)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
    else if(x==2)
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }

}
void Choose::set_name(QString name)
{
    setWindowTitle(name);
}


