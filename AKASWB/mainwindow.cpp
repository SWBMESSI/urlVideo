#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "download.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QTimer>
#include <QFileDialog>
#include <QString>
#include <QHBoxLayout>
#include <filestr.h>
#include <download.h>
#include <unistd.h>
#include<thread>
#include<QDebug>
#include<QDir>

/***********************************------------------------------------\
|  this is for ui 1.0                                                   |
|  i didn't try my bestto learn QTui you know..                         |
|  here have button out and hwo to use it                               |
|  so you need to see it very careful Yep                               |
\-----------------------------------************************************/
QTimer * timer;
int maxValue = 1000; //the largest size of that silder
bool state_slider_volume = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  
{

    ui->setupUi(this);
    //this->setCentralWidget(videoWidget);
    layout  = new QVBoxLayout;
    layouts = new QHBoxLayout;
   // layouts = new QVBoxLayout;
    widgets = new QWidget();
    VW = new QVideoWidget();
    player = new QMediaPlayer();
    button = new QPushButton(QIcon(),tr("&open file"),this);
    sound  = new QSlider(Qt::Horizontal);
    sounds = new QSlider(Qt::Horizontal);

    filestr = new FILESTR();
    pause.setText("PAUSE");
    volume_1.setText("voise");
    widgets  = new QWidget ();
    button ->setFlat(true);
    volume_1 .setFlat(true);
    pause .setFlat(true);


    ui->centralWidget->setLayout(layout);
    layout -> addWidget(VW);
    layout -> addWidget(sounds);
    layout -> addWidget(widgets);
    widgets->setLayout(layouts);

    layouts -> addWidget(&pause);
    layouts -> addWidget(&volume_1);

    player = new QMediaPlayer();
    player -> setVideoOutput(VW);

    for (int i = 0; i < 100; i ++) qaction[i] = NULL;
    this->set_program();

    download = new DOWNLOAD("http://liveal.quanmin.tv/live/2038343220_quanmin720.flv");
    download->wget_HTTP();


   //file = new QFile("/h/home/swb/cpp/cpp_qt/vdio/build-qomoTest1-Desktop_Qt_5_9_2_GCC_64bit-Debug/save_video");
   //if(!file->open(QIODevice::ReadOnly))
   //qDebug()<< "Could not open file";

    file_video = "2038343220_quanmin720.flv";
    //this->set_program();
    player -> setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/save_video/"+file_video));
    player -> play();

        on_pushButton_open_file_clicked();
        connect(button,&QPushButton::clicked,this,&MainWindow::open_file);

        connect(sounds,&QSlider::sliderPressed,this,&MainWindow::slider_progress_clicked);
        connect(sounds,&QSlider::sliderMoved,this,&MainWindow::slider_progress_moved);
        connect(sounds,&QSlider::sliderReleased,this,&MainWindow::slider_progress_released);
        connect(&pause,&QPushButton::clicked,this,&MainWindow::pause_button_clicked);

        connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::set_position);

        sounds->setValue(player->position()*maxValue/player->duration());

        slider_volume = new QSlider(this);
        slider_volume ->setOrientation(Qt::Vertical);

        slider_volume -> setEnabled(false);
        slider_volume -> hide();
            //由于不涉及到slider值的刷新，因此只需对move和自定义click两个信号进行处理，并且可以共用一个槽函数
        connect(slider_volume,&QSlider::sliderPressed,this,&MainWindow::slider_volume_changed);
        connect(slider_volume,&QSlider::sliderMoved,this,&MainWindow::slider_volume_changed);
        connect(&volume_1,&QPushButton::clicked,this,&MainWindow::on_pushButton_volume_clicked);

        //connect(qaction[1], SIGNAL(triggered()), this,SLOT(DOWNLOAD_S()));
        doyou = 0;
        while(qaction[doyou]!=NULL){
           connect(qaction[doyou],&QAction::triggered,this, [=](){doyou =0;while(qaction[doyou]!=qobject_cast<QAction*>(sender())){doyou++;}DOWNLOAD_S(doyou);});

           doyou++;
        }
        doyou = 0;
}



void MainWindow::on_pushButton_open_file_clicked()
{
    //前面部分代码与第2篇中相同//
    //启用slider并设置范围
    
    sounds ->setEnabled(true);
    sounds ->setRange(0,maxValue);

    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    //将timer连接至onTimerOut槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}


void MainWindow::onTimerOut()
{
    sounds->setValue(player->position()*maxValue/player->duration());
}

void MainWindow::slider_progress_clicked()
{
    player->setPosition(sounds->value()*player->duration()/maxValue);
}

void MainWindow::slider_progress_moved()
{
    //暂时停止计时器，在用户拖动过程中不修改slider的值
   // timer->stop();
    player->setPosition(sounds->value()*player->duration()/maxValue);
}

void MainWindow::slider_progress_released()
{
    //用户释放滑块后，重启定时器
    timer->start();
}

void MainWindow::open_file(){
    //file->close();

    free (files);
    QString path = QFileDialog::getOpenFileName(this, tr("open file"),".", tr("(*.*)"));

    files = new QFile(path);
    if(!files->open(QIODevice::ReadOnly))
        qDebug()<< "Could not open file";
    if(!path.isEmpty()){
        player -> setMedia(QUrl::fromLocalFile(path));
        player -> play();
        files -> close();
    }

}
void MainWindow :: play_button_clicked(){

    player->play();

}
void MainWindow :: pause_button_clicked(){

    if(pause.text() == "PAUSE"){
        player->pause();
        pause.setText("PLAY");
    }else{
        player->play();
        pause.setText("PAUSE");
    }
}
void MainWindow ::slider_volume_changed(){

    player->setVolume(slider_volume->value());
}

void MainWindow::on_pushButton_volume_clicked()
{
    slider_volume->setEnabled(true);
    if(state_slider_volume)
    {
        slider_volume->hide();
    }
    else
    {
        slider_volume->setValue(player->volume());
        //计算位置，使其位于音量控制按钮的上方
        slider_volume->setGeometry(QRect(volume_1.pos().rx()+0.5*volume_1.width()-15,volume_1.y()+VW->height() , 30, 50));
        slider_volume->show();
    }
    state_slider_volume = !state_slider_volume;
}

void MainWindow:: set_position(){

    sounds->setValue(player->position()*maxValue/player->duration());
}

void MainWindow::set_program(){

    int n = 0;



    while(!(filestr->BTR_NAME[n].isEmpty())){

        qaction[n] = new QAction(filestr->BTR_NAME[n]);
        ui->menuQOMO->addAction(qaction[n]);
        qDebug()<<qaction[n];
        n++;
    }
}

int MainWindow :: DOWNLOAD_S(int doyou){



    qDebug()<<"******************************************************************\n";

    filestrs = new FILESTR();
    if(check_OK == filestrs->BTR_URL[doyou])return 0;
    qDebug()<<filestrs->BTR_URL[1]<<"*********************************************";
    system("rm -f save_video/*");

    check_OK = filestrs->BTR_URL[doyou];

    download ->STOP = true;

    download = new DOWNLOAD(filestrs->BTR_URL[doyou]);
    download->wget_HTTP();

    player -> setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/save_video/"+download->filename()));
    player -> play();

    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete layouts;
    delete filestr;
    delete VW;
    delete player;
    delete button;
    delete sound;
    delete sounds;
    delete slider_volume;
    delete &volume_1;
    delete &pause;
    delete widgets;
}

