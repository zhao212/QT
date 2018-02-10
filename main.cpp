#include "mainwindow.h"
#include "createevent.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.readFile();

    return a.exec();
}
