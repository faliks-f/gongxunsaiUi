#ifndef TRASHWIDGET_H
#define TRASHWIDGET_H

#include <QWidget>

class TrashWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrashWidget(int pictureIndex, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

private:
    int i = 0;
    int pictureIndex = 1;
    bool isFull = false;

signals:

};

#endif // TRASHWIDGET_H
