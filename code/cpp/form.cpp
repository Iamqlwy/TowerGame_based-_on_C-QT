#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setFixedSize(400,400);
    setWindowTitle("新存档");
    connect(ui->pushButton,&QPushButton::clicked,this,&Form::rename);
}

Form::~Form()
{
    delete ui;

}
void Form::rename()
{
    QString data=ui->lineEdit->text();
    if(data.trimmed().isEmpty())
    {

        QMessageBox::warning(this, "名字不能为空", "名字错误");
        return ;
    }
    ui->lineEdit->clear();
    emit data_ready(data);
    this->close();
}
