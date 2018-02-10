#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createevent.h"
#include "viewevent.h"
#include <QFile>
#include <QDebug>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

bool MainWindow::readFile(){
    if(MainWindow::connectdb("test.db")){
        qDebug() << "Database Create Sucessfully!";
        QSqlQuery query;

        if (!query.exec("CREATE TABLE events ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "date DATE,"
        "amount DOUBLE,"
        "desp VARCHAR)")) {
        }

        return true;
    }
    else{
        qDebug() << "Database Create Failed!";
        return false;
    }
    return false;
}

bool MainWindow::connectdb(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qDebug() << "Database Error!";
        return false;
    }
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QDialog *dlg = new createevent(this);
    qDebug()<<"clickedp1"<<endl;
    connect(dlg, SIGNAL(sendData(QString, double, QString)), this, SLOT(receiveData(QString, double, QString)));
    dlg->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QDialog *dlg = new Viewevent(this);
    
    dlg->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::receiveData(QString DateData, double ValueData, QString DespData)
{
    //qDebug()<<DateData<<" "<<ValueData<<" "<<DespData<<endl;     //获取传递过来的数据
    QSqlQuery query;//绑定方法添加变量
    query.prepare("INSERT INTO events (date, amount,desp) VALUES (:date,:amount,:desp)");
    query.bindValue(0, DateData);
    query.bindValue(1, ValueData);
    query.bindValue(2, DespData);
    query.exec();
}
