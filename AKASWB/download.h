#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include <stdlib.h>
#include <QString>
class DOWNLOAD{

public:
    DOWNLOAD(QString);
    bool wget_HTTP();
    bool get_HTTP_url(QString);
    QString filename();
 //   ~DOWNLOAD();
    bool STOP;
private:
    QString url;
};
#endif // DOWNLOAD_H
