#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

class QMediaPlayer;
class QMediaPlaylist;

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    QMediaPlayer::State getState();
    void play();
signals:


private:
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlayList;
};

#endif // VIDEOWIDGET_H
