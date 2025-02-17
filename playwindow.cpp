    #include "playwindow.h"
    #include "ui_playwindow.h" // 确保包含了这个文件
    #include<string.h>
    extern Region *map[12][12];
    extern int time_group_att;
    extern int time_fury;
    extern int time_freeze;
    extern int time_con_att ;
    extern int damocost;
    extern int lixincost;
    extern int houyicost;
    extern int lubancost;
    extern int towercost;
    extern int money;
    extern int basenum;
    extern int skill1_cost;

    PlayWindow::PlayWindow(QWidget *parent,int x,QString name,bool isnew)
        : QWidget(parent)
        , ui(new Ui::PlayWindow)
    {

        ui->setupUi(this);
        setWindowTitle("游戏界面");
        user_name=name;

        setFixedSize(800, 800);
        over=false;
        /*QLabel *bac=new QLabel(this);
        bac->lower();
        bac->resize(720,720);

        QPixmap background(":/new/prefix3/map1.png");
        bac->setPixmap(background);
    */

        win=false;
        number_guanqia=x;
        ui->level_label->setText("关卡"+QString::number(number_guanqia));
        ui->name_label->setText(name);
        ui->progressBar->setValue(0);
        generate_time=5*number_guanqia;
        initialize();
        if(!isnew)
            loaddata();
        game=new QTimer(this);
        forcenum=new QTimer(this);
        player=new QMediaPlayer(this);
        player->setMedia(QUrl("qrc:/new/prefix3/bgm.mp3"));
        player->setVolume(50);
        player->play();
        skill1player=new QMediaPlayer(this);
        skill1player->setMedia(QUrl("qrc:/new/prefix3/thunder.mp3"));
        skill1player->setVolume(50);
        connect(game,&QTimer::timeout,this,&PlayWindow::play_game);
        connect(forcenum,&QTimer::timeout,this,&PlayWindow::set_force_label);
        /*QPixmap background(":/new/prefix3/map1.png");
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, background);
        this->setPalette(palette);*/
        forcenum->start(100);
        if(number_guanqia==3)
            game->start(1500);
        else game->start(3000);
        //BigFat *a = new BigFat(this);
        //a->accelerate();
        //Normal *c = new Normal(this);
        //DaMo *temp=new DaMo(this,6,5);

    }

    PlayWindow::~PlayWindow()
    {


            delete ui;

    }
    void PlayWindow::closeEvent(QCloseEvent *event)
    {
        savedata();
        time_group_att=basenum;
        time_fury=basenum;
        time_freeze=basenum;
        time_con_att=basenum;
        money=100;
        Enemy::reach=false;
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<12;j++)
            {
                delete map[i][j];
                map[i][j]=nullptr;
            }
        }
        emit open_choose();
         event->accept();

    }
    void PlayWindow::togglePause()
    {
        if (player->state() == QMediaPlayer::PlayingState) {
                player->pause();
            }
        else
            player->play();
        if (isPaused) {
            resumeGame();
        } else {
            pauseGame();
        }
        isPaused = !isPaused;
        pauseButton->setText(isPaused ? "继续" : "暂停");
    }

    void PlayWindow::pauseGame()
    {
        pauseHandler->setPaused(true);
    }

    void PlayWindow::resumeGame()
    {
        pauseHandler->setPaused(false);
    }
    void PlayWindow::load_routine_from_file(const std::string &filename)
    {
        std::ifstream infile(filename);
        if (!infile) {
            return;
        }

        std::string line;
        while (std::getline(infile, line)) {
            if (line.find("way") != std::string::npos) {
                // Skip the way identifier line (e.g., "way1", "way2", "way3")
                continue;
            }

            std::istringstream iss(line);
            std::string coord;
            while (iss >> coord) {
                coord = coord.substr(1, coord.size() - 2);  // 去掉括号
                size_t comma_pos = coord.find(',');
                int x = std::stoi(coord.substr(0, comma_pos));
                int y = std::stoi(coord.substr(comma_pos + 1));
                all_way.append(std::make_pair(x, y));
            }
        }
        for(int i=0;i<all_way.size();i++)
        {
            qDebug()<<all_way[i];
        }
    }



    void PlayWindow::initialize()
    {
        std::string road="ways"+std::to_string(number_guanqia)+".txt";
        load_routine_from_file(road);
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                map[i][j] = new Region(this, i, j);
                connect(map[i][j], &Region::build, this, &PlayWindow::build_defense);
                std::pair<int, int> element_to_find = {i, j};
                auto it = std::find(all_way.begin(), all_way.end(), element_to_find);
                if (it != all_way.end()) {
                    map[i][j]->on_the_way = true;
                    map[i][j]->show();

                }
            }
        }

        for (int i = 0; i < 12; i++) {
            map[i][11]->right = nullptr;
            map[i][0]->left = nullptr;
            map[0][i]->up = nullptr;
            map[11][i]->down = nullptr;

        }

        // 设置相邻区域指针
        for (int i = 0; i < 11; i++) {
            map[11][i]->right=map[11][i+1];
            map[11][i+1]->left=map[11][i];
            map[i][11]->down=map[i+1][11];
            map[i+1][11]->up=map[i][11];
            for (int j = 0; j < 11; j++) {
                map[i][j]->right = map[i][j + 1];
                map[i][j]->down = map[i + 1][j];
                map[i][j + 1]->left = map[i][j];
                map[i + 1][j]->up = map[i][j];
            }
        }
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(8);
        font.setBold(true);
        font.setItalic(true);
        for(int i=0;i<5;i++)
        {

            force[i]=new QLabel(this);
            text[i]=new QLabel(this);
            force[i]->move(0,100+i*100);
            text[i]->move(50,i*100+100);


            // 将QFont对象应用到QLabel上
            text[i]->setFont(font);
        }
        QPixmap a0(":/new/prefix3/money.jpg");
        QPixmap a1(":/new/prefix3/group_att.png");
        QPixmap a2(":/new/prefix3/fury.png");
        QPixmap a3(":/new/prefix3/freeze.png");
        QPixmap a4(":/new/prefix3/con_att.png");
        force[0]->setPixmap(a0);
        force[1]->setPixmap(a1);
        force[2]->setPixmap(a2);
        force[3]->setPixmap(a3);
        force[4]->setPixmap(a4);
        set_force_label();
        pauseButton = new QPushButton("Pause", this);
            pauseButton->setGeometry(10, 10, 100, 30); // 设置按钮位置和大小
            connect(pauseButton, &QPushButton::clicked, this, &PlayWindow::togglePause);

            // 初始化自定义事件过滤器
            pauseHandler = new PauseHandler(this);
            qApp->installEventFilter(pauseHandler);




    }
    void PlayWindow::make_damo(int x, int y)
    {

        DaMo *a=new DaMo(this,x,y);
        all_soldier.append(a);
        a->show();

    }
    void PlayWindow::make_lixin(int x, int y)
    {
        LiXin * a=new LiXin(this,x,y);
        all_soldier.append(a);
        a->show();

    }

    void PlayWindow::make_tower(int x, int y)
    {
        Tower *a = new Tower(this, x, y);
        all_tower.append(a);
        connect(a, &Tower::request_update, this, &PlayWindow::handleTowerUpdate);
        a->show();

    }
    void PlayWindow::make_houyi(int x, int y)
    {
        HouYi *a=new HouYi(this,x,y);

        all_soldier.append(a);
        a->show();
    }
    void PlayWindow::make_luban(int x, int y)
    {
        LuBan *a=new LuBan(this,x,y);
        all_soldier.append(a);
        a->show();
    }

    void PlayWindow::handleTowerUpdate()
    {
        update();

    }

    void PlayWindow::skill1(int x, int y)
    {
        // 先收集要删除的敌人对象
        QVector<Unit*> enemiesToDie = map[x][y]->possess_enemy;
        skill1player->play();
        for (Unit* enemy : enemiesToDie)
        {
            if (enemy != nullptr)
            {
                enemy->die();
            }
        }

        // 清空位置的敌人列表
        map[x][y]->possess_enemy.clear();
    }


    void PlayWindow::play_game()
    {
        int progress = 100 * (1 - generate_time / (15.0 * number_guanqia));
            ui->progressBar->setValue(progress);
        generate_time--;
        if(generate_time<=0)
            game->stop();
        for(int i=0;i<3;i++)
        {
            int x=QRandomGenerator::global()->bounded(1,4);
            if(x==1)
            {
                BigFat *big=new BigFat(this,this);

                all_enemy.append(big);
            }
            else if (x==2)
            {
                Normal *nor=new Normal(this,this);

                all_enemy.append(nor);
            }

            else
            {
                SmallQuick *sma=new SmallQuick(this,this);

                all_enemy.append(sma);
            }
        }


    }
    void PlayWindow::mousePressEvent(QMouseEvent *event)
    {
        if(event->button()==Qt::LeftButton){
        if (Fellow *fellow = dynamic_cast<Fellow*>(childAt(event->pos())))
        {
            fellow->change_dir();
        }
        }

    }
    void PlayWindow::build_defense(int type, int x,int y)
    {
        if(type==0)
        {
            make_damo(x,y);
            money-=damocost;
        }
        else if(type==1)
        {
            make_lixin(x,y);
            money-=lixincost;
        }
        else if(type==2)
        {
            make_houyi(x,y);
            money-=houyicost;
        }
        else if(type==3)
        {
            make_luban(x,y);
            money-=lubancost;
        }
        else if(type==4)
        {
            make_tower(x,y);
            money-=towercost;
        }
        else if(type==5)
        {
            skill1(x,y);
            money-=skill1_cost;

        }
    }
    void PlayWindow::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        QString imageway = QString(":/new/prefix3/map%1.png").arg(number_guanqia);
        QPixmap background(imageway);
        painter.drawPixmap(80, 80, background);
        QPen pen(Qt::red, 2);
        painter.setPen(pen);
        for (int i = 0; i < all_tower.size(); i++) {
            for (int j = 0; j < all_tower[i]->att_place.size(); j++) {
                for (int k = 0; k < all_tower[i]->att_place[j]->possess_enemy.size(); k++) {
                    // 获取塔和敌人的相对位置
                    QPoint towerLocalPos = all_tower[i]->mapToParent(all_tower[i]->rect().center());
                    QPoint enemyLocalPos = all_tower[i]->att_place[j]->possess_enemy[k]->mapToParent(all_tower[i]->att_place[j]->possess_enemy[k]->rect().center());

                    // 在 PlayWindow 中绘制线条
                    painter.drawLine(towerLocalPos, enemyLocalPos);
                }
            }
        }
    }
    void PlayWindow::set_force_label()
    {

        if(Enemy::reach)
        {
            win_or_lose(false);


        }
        text[0]->setNum(money);
        text[1]->setNum(time_group_att);
        text[2]->setNum(time_fury);
        text[3]->setNum(time_freeze);
        text[4]->setNum(time_con_att);
        if(generate_time<=0)
        {
            for(int i=0;i<all_way.size();i++)
            {
                if(!map[all_way[i].first][all_way[i].second]->possess_enemy.empty())
                    return ;
            }
            win_or_lose(true);
            win=true;

        }

    }
    void PlayWindow::win_or_lose(bool win)
    {
        over = true;
        game->stop();
        forcenum->stop();

        QString filepath = user_name + ".json";
        QFile file(filepath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file for reading: " << file.errorString();
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject newdata = doc.object();


        if (win) {
            if(number_guanqia==newdata["state"].toInt())
                newdata["state"] = newdata["state"].toInt() + 1;  // 正确更新 state
            player->setMedia(QUrl("qrc:/new/prefix3/win.mp3"));
        }
        else
        {
            player->setMedia(QUrl("qrc:/new/prefix3/lose.mp3"));
        }
        player->play();

        qDebug() << "New state after update:" << newdata["state"];

        QJsonDocument newDoc(newdata);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file for writing: " << file.errorString();
            return;
        }

        file.write(newDoc.toJson());
        file.close();

        QLabel *label = new QLabel(this);
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);

        if (win) {
            label->setText("Win");
        } else {
            label->setText("Lose");
        }

        label->move(400, 400);
        label->show();
    }




    void PlayWindow::savedata()
    {
        QFile file(user_name + ".json");

        QJsonObject data;

        // 读取现有的 JSON 文件
        if (file.exists()) {
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Cannot open file for reading: " << file.errorString();
                return;
            }

            QByteArray jsonData = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if (!doc.isNull() && doc.isObject()) {
                data = doc.object();
            }
        }

        // 构建要保存的关卡数据
        QJsonObject level;
        level["money"] = money;
        level["time_group_att"] = time_group_att;
        level["time_fury"] = time_fury;
        level["time_freeze"] = time_freeze;
        level["time_con_att"] = time_con_att;
        level["generate_time"] = generate_time;

        QJsonArray soilders;
        QJsonArray towers;
        QJsonArray enemys;
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                if (map[i][j]->soilder != nullptr && map[i][j]->soilder->blood>0) {
                    QJsonObject soilder;
                    soilder["x"] = i;
                    soilder["y"] = j;
                    soilder["type"] = getClassName(map[i][j]->soilder);
                    soilder["blood"] = map[i][j]->soilder->blood;
                    soilders.append(soilder);
                }
                if (map[i][j]->tower != nullptr) {
                    QJsonObject tower;
                    tower["x"] = i;
                    tower["y"] = j;
                    towers.append(tower);
                }
                if (!map[i][j]->possess_enemy.empty()) {
                    for (int k = 0; k < map[i][j]->possess_enemy.size(); k++) {
                        if(map[i][j]->possess_enemy[k]!=nullptr && map[i][j]->possess_enemy[k]->blood>0){
                        Enemy *temp = static_cast<Enemy*>(map[i][j]->possess_enemy[k]);
                        QJsonObject enemy;
                        enemy["x"] = i;
                        enemy["y"] = j;
                        enemy["way"] = temp->theway;
                        enemy["cur_place"] = temp->cur_place;
                        enemy["type"] = getClassName(map[i][j]->possess_enemy[k]);
                        enemy["blood"] = map[i][j]->possess_enemy[k]->blood;
                        enemys.append(enemy);}
                    }
                }
            }
        }

        level["soilders"] = soilders;
        level["towers"] = towers;
        level["enemys"] = enemys;

        // 将关卡数据保存到对应的 key 中
        if (number_guanqia == 1) {
            data["1"] = level;
        } else if (number_guanqia == 2) {
            data["2"] = level;
        }
        else
        {
            data["3"]=level;
        }

        data["name"] = user_name;


        QJsonDocument newDoc(data);
        QByteArray newJsonData = newDoc.toJson();

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file for writing: " << file.errorString();
            return;
        }

        file.write(newJsonData);
        file.close();

        qDebug() << "JSON data has been modified and written to file.";
    }

    void PlayWindow::loaddata() {
        QString filename = user_name + ".json";
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "无法打开文件加载游戏状态";
            return;
        }

        QByteArray jsonData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        QJsonObject data = doc.object();


        QString levelKey = QString::number(number_guanqia);
        QJsonObject level = data[levelKey].toObject();


        money = level["money"].toInt();
        time_group_att = level["time_group_att"].toInt();
        time_fury = level["time_fury"].toInt();
        time_freeze = level["time_freeze"].toInt();
        time_con_att = level["time_con_att"].toInt();
        generate_time = level["generate_time"].toInt();
        int progress = 100 * (1 - generate_time / (15.0 * number_guanqia));
        ui->progressBar->setValue(progress);

        QJsonArray soilders = level["soilders"].toArray();
        for (int i = 0; i < soilders.size(); ++i) {
            QJsonObject soilder = soilders[i].toObject();
            int x = soilder["x"].toInt();
            int y = soilder["y"].toInt();
            QString type = soilder["type"].toString();
            float blood = soilder["blood"].toDouble();

            if (type == "DaMo") {
                make_damo(x, y);
                all_soldier.last()->set_blood(blood);
            } else if (type == "LiXin") {
                make_lixin(x, y);
                all_soldier.last()->set_blood(blood);
            } else if (type == "HouYi") {
                make_houyi(x, y);
                all_soldier.last()->set_blood(blood);
            } else if (type == "LuBan") {
                make_luban(x, y);
                all_soldier.last()->set_blood(blood);
            }
        }


        QJsonArray towers = level["towers"].toArray();
        for (int i = 0; i < towers.size(); ++i) {
            QJsonObject tower = towers[i].toObject();
            int x = tower["x"].toInt();
            int y = tower["y"].toInt();
            make_tower(x, y);
        }


        QJsonArray enemys = level["enemys"].toArray();
        for (int i = 0; i < enemys.size(); ++i) {
            QJsonObject enemy = enemys[i].toObject();
            int x = enemy["x"].toInt();
            int y = enemy["y"].toInt();
            int way=enemy["way"].toInt();
            int cur_place=enemy["cur_place"].toInt();
            QString type = enemy["type"].toString();
            float blood = enemy["blood"].toDouble();

            if (type == "BigFat") {
                BigFat *enemy = new BigFat(this, this, x, y,way,cur_place);
                enemy->set_blood(blood);
                enemy->show();
                all_enemy.append(enemy);
            } else if (type == "Normal") {
                Normal *enemy = new Normal(this, this, x, y,way,cur_place);
                enemy->set_blood(blood);
                enemy->show();
                all_enemy.append(enemy);
            } else if (type == "SmallQuick") {
                SmallQuick *enemy = new SmallQuick(this, this, x, y,way,cur_place);
                enemy->set_blood(blood);
                enemy->show();
                all_enemy.append(enemy);
            }
        }

        file.close();
    }


    QString PlayWindow::getClassName(Unit *unit)
    {
        if (dynamic_cast<DaMo*>(unit)) {
                return "DaMo";
            } else if (dynamic_cast<LiXin*>(unit)) {
                return "LiXin";
            } else if (dynamic_cast<HouYi*>(unit)) {
                return "HouYi";
            } else if (dynamic_cast<LuBan*>(unit)) {
                return "LuBan";
            } else if (dynamic_cast<BigFat*>(unit)) {
                return "BigFat";
            } else if (dynamic_cast<Normal*>(unit)) {
                return "Normal";
            } else if (dynamic_cast<SmallQuick*>(unit)) {
                return "SmallQuick";
            }
            return "Unknown";
    }
