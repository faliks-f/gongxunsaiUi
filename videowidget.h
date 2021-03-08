#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>

class QMediaPlayer;
class QMediaPlaylist;

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QVideoWidget *parent = nullptr);

signals:


private:
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlayList;
};

#endif // VIDEOWIDGET_H
