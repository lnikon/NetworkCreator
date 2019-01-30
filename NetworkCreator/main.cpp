#include "mainwindow.h"
#include <QApplication>
#include "graphwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    GraphWidget w;
//    w.show();
    MainWindow w;
    w.show();

    return a.exec();
}
