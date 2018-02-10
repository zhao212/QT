#ifndef VIEWEVENT_H
#define VIEWEVENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>

namespace Ui {
class Viewevent;
}

class Viewevent : public QDialog
{
    Q_OBJECT

public:
    explicit Viewevent(QWidget *parent = 0);
    bool searchEvent(QString year,QString month, QString day);

    ~Viewevent();

private slots:

    void on_yearSelect_currentIndexChanged(const QString &arg1);

    void on_monthSelect_currentIndexChanged(const QString &arg1);

    void on_daySelect_currentIndexChanged(const QString &arg1);

    void on_deleteSelect_clicked();

    void on_addNew_clicked();
    void receiveData(QString DateData,double ValueData,QString DespData);   //接收传递过来的数据的槽


    void on_selectSort_currentIndexChanged(int index);

private:
    Ui::Viewevent *ui;
    QSqlTableModel *model = new QSqlTableModel;
    void renewMenuYear();
    void renewMenuMonth();
    void renewMenuDay();
};

#endif // VIEWEVENT_H
