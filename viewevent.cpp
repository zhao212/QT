#include "viewevent.h"
#include "ui_viewevent.h"
#include "createevent.h"
#include <QMessageBox>

Viewevent::Viewevent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Viewevent)
{
    ui->setupUi(this);

    model->setTable("events");

    model->setHeaderData(1, Qt::Horizontal, "Date");
    model->setHeaderData(2, Qt::Horizontal, "Amount");
    model->setHeaderData(3, Qt::Horizontal, "Desciption");

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);//控制编辑

    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setStretchLastSection(true);
    ui->tableView->setModel(model);
    ui->tableView->show();

    renewMenuYear();
    renewMenuMonth();
    renewMenuDay();
    model->setSort(1, Qt::DescendingOrder);
    model->select();

    //connect(dlg, SIGNAL(sendData(QString, double, QString)), this,
    //SLOT(receiveData(QString, double, QString)));
}

bool Viewevent::searchEvent(QString year,QString month, QString day){
    //每当有值变化, run search function
    //if(year == "ALL"){  year = "*";}
    //if(month == "ALL"){  month = "*";}
    //if(day == "ALL"){  day = "*";}
    qDebug()<<"search called: "<<year<<month<<day<<endl;
    QSqlQuery query;//bind query
    if(year=="ALL" && month=="ALL" && day=="ALL"){
        model->setTable("events");
        model->select();
    }
    else if(year=="ALL"&&month=="ALL"){
        model->setFilter(QString("date like '%%1'").arg(day));
        model->select();
    }
    else if(year=="ALL"&&day=="ALL"){
        model->setFilter(QString("date like '%%1%'").arg("-"+month+"-"));
        model->select();
    }
    else if(month=="ALL"&&day=="ALL"){
        model->setFilter(QString("date like '%1%'").arg(year));
        model->select();
    }
    else if(year=="ALL"){
        model->setFilter(QString("date like '%%1'").arg(month+"-"+day));
        model->select();
    }
    else if(month == "ALL"){
        model->setFilter(QString("date like '%1%%2'").arg(year).arg(day));
        model->select();
    }
    else if(day == "ALL"){
        model->setFilter(QString("date like '%1%'").arg(year+"-"+month));
        model->select();
    }
    else{
        query.prepare("SELECT * FROM events WHERE date = ?");
        QString date = year+"-"+month+"-"+day;//获取日期
        query.addBindValue(date);
        query.exec();
        model->select();
        ui->tableView->update();
    }
}

Viewevent::~Viewevent()
{
    delete ui;
}

void Viewevent::on_yearSelect_currentIndexChanged(const QString &arg1)
{
    QString year = ui->yearSelect->currentText();
    QString month = ui->monthSelect->currentText();
    QString day = ui->daySelect->currentText();
    searchEvent(year,month,day);
}

void Viewevent::on_monthSelect_currentIndexChanged(const QString &arg1)
{
    QString year = ui->yearSelect->currentText();
    QString month = ui->monthSelect->currentText();
    QString day = ui->daySelect->currentText();
    searchEvent(year,month,day);
}

void Viewevent::on_daySelect_currentIndexChanged(const QString &arg1)
{
    QString year = ui->yearSelect->currentText();
    QString month = ui->monthSelect->currentText();
    QString day = ui->daySelect->currentText();
    searchEvent(year,month,day);
}

void Viewevent::on_deleteSelect_clicked()
{
    int curRow = ui->tableView->currentIndex().row();


    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                       "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes) {
        model->removeRow(curRow);
        model->submitAll();
    } //否则提交，在数据库中删除该行
    model->select();
}

void Viewevent::on_addNew_clicked()
{
    QDialog *dlg = new createevent(this);
    connect(dlg, SIGNAL(sendData(QString, double, QString)), this, SLOT(receiveData(QString, double, QString)));
    dlg->show();
}

void Viewevent::receiveData(QString DateData, double ValueData, QString DespData)
{
    //qDebug()<<DateData<<" "<<ValueData<<" "<<DespData<<endl;     //获取传递过来的数据
    QSqlQuery query;//绑定方法添加变量
    query.prepare("INSERT INTO events (date, amount,desp) VALUES (:date,:amount,:desp)");
    query.bindValue(0, DateData);
    query.bindValue(1, ValueData);
    query.bindValue(2, DespData);
    query.exec();

    ui->yearSelect->clear();
    ui->monthSelect->clear();
    ui->daySelect->clear();
    renewMenuYear();
    renewMenuMonth();
    renewMenuDay();
    model->select();
}

void Viewevent::renewMenuYear(){
    QSqlQuery query;
    query.prepare("SELECT DISTINCT strftime('%Y', date) FROM events");
    query.exec();
    QList<QString> menu;
    while (query.next()) {
        menu.append(query.value(0).toString());
    }
    qSort(menu);
    QList<QString> menuall = {"ALL"};
    menuall.append(menu);
    ui->yearSelect->addItems(menuall);
}

void Viewevent::renewMenuMonth(){
    QSqlQuery query;
    query.prepare("SELECT DISTINCT strftime('%m', date) FROM events");
    query.exec();
    QList<QString> menu;
    while (query.next()) {
        menu.append(query.value(0).toString());
    }
    qSort(menu);
    QList<QString> menuall = {"ALL"};
    menuall.append(menu);
    ui->monthSelect->addItems(menuall);
}

void Viewevent::renewMenuDay(){
    QSqlQuery query;
    query.prepare("SELECT DISTINCT strftime('%d', date) FROM events");
    query.exec();
    QList<QString> menu;
    while (query.next()) {
        menu.append(query.value(0).toString());
    }
    qSort(menu);
    QList<QString> menuall = {"ALL"};
    menuall.append(menu);
    ui->daySelect->addItems(menuall);
}



void Viewevent::on_selectSort_currentIndexChanged(int index)
{
    qDebug()<<"排序"<<index<<endl;
    switch(index){
    case 0:
        //日期降序
        model->setSort(1, Qt::DescendingOrder);
        model->select();
        break;
    case 1:
        //日期升序
        model->setSort(1, Qt::AscendingOrder);
        model->select();
        break;
    case 2:
        //金额降序
        model->setSort(2, Qt::DescendingOrder);
        model->select();
        break;
    case 3:
        //金额升序
        model->setSort(2, Qt::AscendingOrder);
        model->select();
        break;
    default:
        break;
    }
}
