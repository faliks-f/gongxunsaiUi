#include "trashwidget.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QBoxLayout>

TrashWidget::TrashWidget(int pictureIndex, QWidget *parent)
{
    this->pictureIndex = pictureIndex;
    QLabel *label = new QLabel(this);
    QString string = QString("存放数量: %1").arg(i);
    label->setText(string);
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    label->setFont(font);
    label->move(width() * 5 / 8, height() / 6);
}

void TrashWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap;
    QString path = QString(":/bin/%1.jpg").arg(pictureIndex);
    pixmap.load(path);
    painter.drawPixmap(0, 0, width() / 3, height(), pixmap);
    QColor color;
    if (isFull)
    {
        color = QColor(255, 0, 0);
    }
    else
    {
        color = QColor(0, 255, 0);
    }
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawEllipse(width() * 3 / 6, height() * 3 / 5, height() / 4, height() / 4);
}
