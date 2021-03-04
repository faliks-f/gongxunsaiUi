#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QPalette>
#include <QMessageBox>
#include <QFont>
#include "trashwidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setMaximumSize(1024, 600);
    setMinimumSize(1024, 600);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    addButton(buttonLayout);

    QVBoxLayout *trashLayout = new QVBoxLayout();

    addTrashWidget(trashLayout);

    QVBoxLayout *centerLayout = new QVBoxLayout(this);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addLayout(trashLayout);

    connectButton();
}



Widget::~Widget()
{
    delete ui;
}

void Widget::classifyButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::isFullButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::advancedButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::setArgButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::addButton(QHBoxLayout *layout)
{
    QFont font;
    font.setPointSize(30);
    QPalette palette;
    palette.setColor(QPalette::ButtonText, Qt::white);

    classifyButton = new QPushButton();
    classifyButton->setFont(font);
    classifyButton->setText("垃圾分类功能");
    classifyButton->setPalette(palette);
    classifyButton->setStyleSheet("background-color:blue");
    layout->addWidget(classifyButton);

    isFullButton = new QPushButton();
    isFullButton->setFont(font);
    isFullButton->setText("满载检测功能");
    isFullButton->setPalette(palette);
    isFullButton->setStyleSheet("background-color:blue");
    layout->addWidget(isFullButton);

    advancedButton = new QPushButton();
    advancedButton->setFont(font);
    advancedButton->setText("高级检测");
    advancedButton->setPalette(palette);
    advancedButton->setStyleSheet("background-color:blue");
    layout->addWidget(advancedButton);

    setArgButton = new QPushButton();
    setArgButton->setFont(font);
    setArgButton->setText("参数设置");
    setArgButton->setPalette(palette);
    setArgButton->setStyleSheet("background-color:blue");
    layout->addWidget(setArgButton);
}

void Widget::addTrashWidget(QVBoxLayout *trashLayout)
{
    QHBoxLayout *trashLayoutUp = new QHBoxLayout();
    QHBoxLayout *trashLayoutDown = new QHBoxLayout();

    recoverableWidget = new TrashWidget(1);
    harmfulWidget = new TrashWidget(2);
    kitchenWidget = new TrashWidget(3);
    otherWidget = new TrashWidget(4);

    QFont font;
    font.setBold(true);
    font.setPointSize(15);

    QLabel *label1 = new QLabel();
    label1->setFont(font);
    label1->setText("可回收垃圾");
    QVBoxLayout *recoverableLayout = new QVBoxLayout();
    setLabelWithWidget(label1, recoverableWidget, recoverableLayout);

    QLabel *label2 = new QLabel();
    label2->setFont(font);
    label2->setText("有害垃圾");
    QVBoxLayout *harmfulLayout = new QVBoxLayout();
    setLabelWithWidget(label2, harmfulWidget, harmfulLayout);

    QLabel *label3 = new QLabel();
    label3->setFont(font);
    label3->setText("厨余垃圾");
    QVBoxLayout *kitchenLayout = new QVBoxLayout();
    setLabelWithWidget(label3, kitchenWidget, kitchenLayout);

    QLabel *label4 = new QLabel();
    label4->setFont(font);
    label4->setText("其他垃圾");
    QVBoxLayout *otherLayout = new QVBoxLayout();
    setLabelWithWidget(label4, otherWidget, otherLayout);

    trashLayoutUp->addLayout(recoverableLayout);
    trashLayoutUp->addLayout(harmfulLayout);
    trashLayoutDown->addLayout(kitchenLayout);
    trashLayoutDown->addLayout(otherLayout);

    trashLayout->addLayout(trashLayoutUp);
    trashLayout->addLayout(trashLayoutDown);
}

void Widget::connectButton()
{
    connect(classifyButton, &QPushButton::clicked, this, &Widget::classifyButtonSlot);
    connect(isFullButton, &QPushButton::clicked, this, &Widget::isFullButtonSlot);
    connect(advancedButton, &QPushButton::clicked, this, &Widget::advancedButtonSlot);
    connect(setArgButton, &QPushButton::clicked, this, &Widget::setArgButtonSlot);
}

void Widget::setLabelWithWidget(QLabel *label, TrashWidget *widget, QVBoxLayout *layout)
{
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addStretch();
    labelLayout->addWidget(label);
    labelLayout->addStretch();
    layout->addLayout(labelLayout);
    layout->addWidget(widget);
    layout->setStretchFactor(labelLayout, 1);
    layout->setStretchFactor(widget, 6);
}

