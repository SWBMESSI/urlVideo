#include "filestr.h"
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QDebug>

FILESTR::FILESTR()
{
    int line_num = 0;
    file = new QFile("/home/swb/cpp/cpp_qt/vdio/build-qomoTest1-Desktop_Qt_5_9_2_GCC_64bit-Debug/url/url.txt");
    if(!file->open(QIODevice::ReadOnly))qDebug()<<"open error!\n";
    while (!file->atEnd())
            {
                QByteArray line = file->readLine();
                STR = line;
                BTR_NAME[line_num] = re_name();  //retuen where???? how can i get this str>???
                BTR_URL[line_num] = re_url();   //return 1
                line_num++;
            }
    file->close();
}

QString FILESTR:: re_name(){
    video_name = "";
    for(auto X :STR){

        if (X== ',')break;
        else
            video_name+=X;
   }

   return video_name;  //how to get it
}

QString FILESTR:: re_url(){
    video_url = "";
    auto sign = 0;
    for(auto X: STR){

        if(X == ','){

            sign = 1;
            continue;
        }
        if(X == ';')break;
        if(sign == 1)video_url += X;
    }
    sign = 0;
    return video_url;
}
