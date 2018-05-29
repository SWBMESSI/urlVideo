#ifndef FILESTR_H
#define FILESTR_H
#include <QFile>
#include <QFileDialog>
#include <QString>
/******************---------------------\
|  this is about get url and vedioname  |
|  layout is                            |
|  vedio_name,url(http or https)        |
\-----------------**********************/
class FILESTR
{
public:
    FILESTR();
    QString re_name();
    QString re_url();

    QString BTR_NAME[100];
    QString BTR_URL[100];

private:
    QFile *file;
    QString video_name;
    QString video_url;
    QString STR;

};

#endif // FILESTR_H
