#include "videowidget.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QLayout>
#include <iostream>

VideoWidget::VideoWidget(QVideoWidget *parent) : QVideoWidget(parent)
{
    setMaximumSize(1024, 600);
    setMinimumSize(1024, 600);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayList = new QMediaPlaylist(mediaPlayer);
    QString path = "/home/faliks/Desktop/gongxunsaiUi/1.mp4";
    mediaPlayList->addMedia(QUrl::fromLocalFile(path));
    mediaPlayList->setCurrentIndex(0);
    mediaPlayer->setPlaylist(mediaPlayList);
    mediaPlayer->play();
    mediaPlayer->setVideoOutput(this);
    std::cout << mediaPlayer->EndOfMedia;
}
