#include "createevent.h"
#include "ui_createevent.h"
#include <QDebug>

createevent::createevent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createevent)
{
    ui->setupUi(this);
    ui->inputDate->setDate(QDate::currentDate());
}

createevent::~createevent()
{
    delete ui;
}

void createevent::on_buttonBox_clicked(QAbstractButton *button)
{
    double valueStr = ui->inputAmount->value();
    QDate mdate = ui->inputDate->date();
    QString dateStr = mdate.toString("yyyy-MM-dd");
    QString despStr = ui->inputDesp->toPlainText(); //取得desp;
    if(ui->buttonBox->button(QDialogButtonBox::Ok)  == button)   //判断按下的是否为"确定”按钮
    {
        //qDebug()<<dateStr<<endl;
        emit sendData(dateStr,valueStr,despStr);
    }
    else if(button == ui->buttonBox->button((QDialogButtonBox::Cancel))){
        qDebug()<<"strcanceled"<<endl;}
}
