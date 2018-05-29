#include <iostream>
#include "download.h"
#include <QDebug>
#include <unistd.h>
DOWNLOAD::DOWNLOAD(QString s):STOP(false){
    url = s;
}

bool DOWNLOAD::wget_HTTP(){
    filename();
    system("rm -f save_video/*");
    QString shell = "wget -P /home/swb/cpp/cpp_qt/vdio/build-qomoTest1-Desktop_Qt_5_9_2_GCC_64bit-Debug/save_video " + url;
    QByteArray ba = shell.toLatin1(); // must
    pid_t pidss;
    if((pidss = fork())<0)exit(0);
    if(pidss < 0)exit(0);
    if(pidss == 0){
        if(system(ba.data()))
            return true;
        else
            return false;

    }if(pidss > 0){

        if(STOP){

            qDebug()<<"change------------------------------";
            exit(0);

        }
    }
    return true;
}

bool DOWNLOAD::get_HTTP_url(QString s){

    url = s;
    return true;
}

QString DOWNLOAD::filename(){
    QString replay = NULL;
    for(auto x :url){
        if(x == '\\')break;
        if (x == '/') replay ="";
        else replay += x;

    }
    qDebug()<<replay;
    return replay;
}

