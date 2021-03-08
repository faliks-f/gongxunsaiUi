#include "videowidget.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QLayout>
#include <QDebug>
#include <iostream>

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent)
{
    setMaximumSize(1024, 600);
    setMinimumSize(1024, 600);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayList = new QMediaPlaylist(mediaPlayer);
    QString path = "/home/faliks/Desktop/gongxunsaiUi/1.mp4";
    mediaPlayList->addMedia(QUrl::fromLocalFile(path));
    mediaPlayList->setCurrentIndex(0);
    mediaPlayer->setPlaylist(mediaPlayList);
    mediaPlayer->setVideoOutput(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

QMediaPlayer::State VideoWidget::getState()
{
    return mediaPlayer->state();
}

void VideoWidget::play()
{
    mediaPlayer->play();
}
