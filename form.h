#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include<QCloseEvent>
#include<QMessageBox>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void rename();
signals:
    void data_ready(QString infor);
private:
    Ui::Form *ui;
};

#endif // FORM_H
