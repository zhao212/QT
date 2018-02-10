#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool addNew();
    bool writeFile();
    bool readFile();
    bool eraseFile();
    bool connectdb(const QString &dbName);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void receiveData(QString DateData,double ValueData,QString DespData);   //接收传递过来的数据的槽

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
