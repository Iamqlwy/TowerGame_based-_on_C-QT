#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("小小塔防");
    state=1;
    read=0;
    setFixedSize(820,820);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::go_in);
    check=new Form();
    check->hide();
    select=new Choose(nullptr);
    select->hide();
    connect(check,&Form::data_ready,this,&MainWindow::recieve_data);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::open_file);
    connect(select,&Choose::level1,this,&MainWindow::select_level1);
    connect(select,&Choose::level2,this,&MainWindow::select_level2);
    connect(select,&Choose::level3,this,&MainWindow::select_level3);
    connect(ui->pushButton_3,&QPushButton::clicked,this,[this]{read=0;ui->textEdit->clear();});
    //game=new PlayWindow(this,1,"sdfsdf");
    //game->win_or_lose(true);


}

void MainWindow::recieve_data(QString infor)
{
    QString fileName = infor+".json";
    name=infor;
        // 创建 QFile 对象
        QFile file(fileName);
        QJsonObject data;
        state=1;
        data["state"]=1;
        data["name"]=infor;

        QJsonDocument doc(data);
           QByteArray jsonData = doc.toJson();

           if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                   qDebug() << "Cannot open file for writing: " << file.errorString();

               }

               file.write(jsonData);
               file.close();

        ui->textEdit->clear();
        ui->textEdit->setText("当前玩家：" +name);
        select->set_state(state);
        select->set_name(name);
        select->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::go_in()
{
    if(read)
    {
        select->set_state(state);
        select->set_name(name);
        select->show();
    }
    else
    {
        check->show();
    }

}
void MainWindow::open_file()
{

    QString filePath = QFileDialog::getOpenFileName(this, "选择存档", QDir::currentPath(), "Text Files (*.json);;All Files (*)");
    qDebug() << "Selected file path:" << filePath;
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        name = fileInfo.completeBaseName(); // 获取文件名，不包含后缀
    }

    if (!filePath.isEmpty())
    {
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Cannot open file for reading:" << file.errorString();
            return;
        }
        QByteArray data = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject newdata = doc.object();
        name=newdata["name"].toString();
        state=newdata["state"].toInt();
        ui->textEdit->setText("当前玩家: "+name);
        read=true;

    }
}
void MainWindow::update_state()
{

    QString filepath=name+".json";
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file for reading: " << file.errorString();

        }


        QByteArray data = file.readAll();
        file.close();
     QJsonDocument doc = QJsonDocument::fromJson(data);
      QJsonObject newdata = doc.object();
      state=newdata["state"].toInt();
}
void MainWindow::select_level1()
{

    start_game(1);
}
void MainWindow::select_level2()
{

    start_game(2);
}
void MainWindow::select_level3()
{
    start_game(3);
}
void MainWindow::start_game(int x)
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "确认", "Yes:新游戏 || No: 旧存档",
                                      QMessageBox::Yes | QMessageBox::No);
        bool whethernew;
    if(reply==QMessageBox::Yes) whethernew=true;
    else whethernew=false;

        game = new PlayWindow(nullptr, x, name,whethernew);
        game->show();
        connect(game, &PlayWindow::open_choose, this, [this] {
            update_state();

            game->deleteLater();

            select->set_state(state);
            select->set_name(name);
            select->show();
        });
}




