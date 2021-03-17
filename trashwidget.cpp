#include "trashwidget.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QBoxLayout>

TrashWidget::TrashWidget(int pictureIndex, QWidget *parent)
{
    this->pictureIndex = pictureIndex;
    label = new QLabel(this);
    QString string = QString("存放数量: %1").arg(i);
    label->setText(string);
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    label->setFont(font);
    label->move(width() * 2 / 10, height() / 6);
}

void TrashWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap;
    QString path = QString(":/bin/%1.png").arg(pictureIndex);
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
    painter.drawEllipse(width() * 4 / 7, height() * 3 / 5, height() / 4, height() / 4);
}

void TrashWidget::addOne()
{
    i++;
    QString string = QString("存放数量: %1").arg(i);
    label->setText(string);
}

void TrashWidget::isFullJudge(bool flag)
{
    isFull = flag;
    QString string =  QString(flag?"  已": "  未") + QString("  满 ");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    label->setFont(font);
    if (flag)
    {
        label->setStyleSheet("color:red");
    }
    label->setText(string);
    repaint();
}


