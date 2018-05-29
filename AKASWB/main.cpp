#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <download.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("rm -f save_video/*");
    MainWindow w;
    w.show();

    return a.exec();
}
