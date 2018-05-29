#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QFile>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QString>
#include <filestr.h>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <download.h>

namespace Ui {
class MainWindow;
}

class QSlider;
class QlineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    QVBoxLayout *layout;
    QHBoxLayout *layouts;
    //QVBoxLayout *layouts;
    QVideoWidget * VW;
    QMediaPlayer * player;
    QPushButton * button;
     //QDialog *sound;
    QSlider *sound;
    QSlider *sounds;
    QSlider *slider_volume;
    QPushButton volume_1;
    QPushButton pause;
    QWidget *widgets;
    QString file_video;
    QMediaPlaylist *mediaPlayerlist;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    FILESTR  *filestr;
    FILESTR  *filestrs;
    QAction *qaction[200];
    DOWNLOAD *download;
    QString check_OK;
    int doyou;




    void on_pushButton_open_file_clicked();

    void slider_progress_clicked();
    void slider_progress_moved();
    void slider_progress_released();
    void open_file();

    void play_button_clicked();
    void pause_button_clicked();

    void slider_volume_changed();
    void on_pushButton_volume_clicked();
    void set_position();
    void set_program();
    void send_file_url();
public slots:
    int DOWNLOAD_S(int );
    void onTimerOut();

private:
    QFile *file;
    QFile *files;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
