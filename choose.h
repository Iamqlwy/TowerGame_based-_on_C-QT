#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>

namespace Ui {
class Choose;
}

class Choose : public QWidget
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr,int state=1,QString name="");
    void set_state(int x);
    void set_name(QString name);
    ~Choose();
signals:
    void level1();
    void level2();
    void level3();

private:
    Ui::Choose *ui;
};

#endif // CHOOSE_H
