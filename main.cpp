#include "mainwin.h"

#include <QApplication>
#include <QFile>
#include <QStyle>
#include <QStyleFactory>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWin w;
    w.show();
    return a.exec();
}
