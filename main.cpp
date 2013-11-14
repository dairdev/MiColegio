#include <QApplication>
#include "mainwindow.h"
#include "myapplication.h"

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    MainWindow* w=new MainWindow();
    w->showMaximized();
    return a.exec();
}
