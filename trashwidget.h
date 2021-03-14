#ifndef TRASHWIDGET_H
#define TRASHWIDGET_H

#include <QWidget>

class QLabel;

class TrashWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrashWidget(int pictureIndex, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void addOne();
    void isFullJudge(bool);

private:

    QLabel *label;

    int i = 0;
    int pictureIndex = 1;
    bool isFull = false;

signals:

};

#endif // TRASHWIDGET_H
