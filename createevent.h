#ifndef CREATEEVENT_H
#define CREATEEVENT_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class createevent;
}

class createevent : public QDialog
{
    Q_OBJECT

public:
    explicit createevent(QWidget *parent = 0);
    ~createevent();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::createevent *ui;

signals:
    void sendData(QString,double,QString);   //用来传递数据的信号
};

#endif // CREATEEVENT_H
