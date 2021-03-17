#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QPalette>
#include <QMessageBox>
#include <QFont>
#include <QTimer>
#include <QDebug>
#include <pthread.h>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "trashwidget.h"
#include "ipc.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    setMaximumSize(1024, 600);
//    setMinimumSize(1024, 600);
    showFullScreen();
    setWindowFlags(Qt::WindowStaysOnTopHint);

    usartInit();
    layout();
    connectButton();
    timerInit();

    checkReady();
}



Widget::~Widget()
{
    deletePipe();
    delete ui;
}

void Widget::classifyButtonSlot()
{
    videoWidget = new VideoWidget();
    videoWidget->play();
    videoWidget->setWindowModality(Qt::ApplicationModal);
    videoWidget->show();
    videoWidget->move(x(), y());
    videoFinishTimer->start();
}

void Widget::isFullButtonSlot()
{
    if (fullInformationBox == nullptr)
    {
        fullInformationBox = new QMessageBox(this);
        QFont font;
        font.setBold(true);
        font.setPointSize(20);
        fullInformationBox->setFont(font);
        fullInformationBox->setText(QString("检测中..."));
        fullInformationBox->show();
        fullInformationBox->move(width() / 3, height() / 2);

    }
    fullWorkFlag = true;
    waitingFlag = true;
    ipcTimer->stop();
    usartSendTimer->start();
    usartWaitTimer->start();

}

void Widget::advancedButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::setArgButtonSlot()
{
    QMessageBox::information(this, "Error", "此功能还未开发");
}

void Widget::handleIpcTimer()
{
    if (!usartCompleteFlag)
    {
//        ipcTimer->stop();
    }
    char res = readResult();
    qDebug() << res;
    switch (res)
    {
    case 'a':
        qDebug() << "here add a";
        table->addItem("果核", "厨余");
        harmfulWidget->addOne();
        setTip("果核");
        binIndex = 3;
        break;
    case 'b':
        qDebug() << "here add b";
        table->addItem("香蕉皮", "厨余");
        recoverableWidget->addOne();
        setTip("香蕉皮");
        binIndex = 3;
        break;
    case 'c':
        qDebug() << "here add c";
        table->addItem("易拉罐", "可回收");
        recoverableWidget->addOne();
        setTip("易拉罐");
        binIndex = 1;
        break;
    case 'f':
        qDebug() << "here add f";
        table->addItem("香烟", "其他");
        kitchenWidget->addOne();
        setTip("香烟");
        binIndex = 4;
        break;
    case 'g':
        qDebug() << "here add g";
        table->addItem("瓶子", "可回收");
        otherWidget->addOne();
        setTip("瓶子");
        binIndex = 4;
        break;
    case 'o':
        qDebug() << "here add o";
        table->addItem("橘子皮", "厨余");
        kitchenWidget->addOne();
        setTip("橘子皮");
        binIndex = 3;
        break;
    default:
        return;
    }
    waitingFlag = true;
    usartCompleteFlag = false;
//    writePipe('s');
    usartSendTimer->start();
    usartWaitTimer->start();
}

void Widget::handleCheckTimer()
{
    if (!ipcFlag)
    {
        char value1 = readResult();
        if (value1 == 'r')
        {
            ipcFlag = true;
            QFont font;
            font.setBold(true);
            font.setPointSize(20);
            checkInformationBox->setFont(font);
            checkInformationBox->setText(QString("Checking! If there is long time, please check the wiring!\n"
                                         "ipcConnect     [%1]\n"
                                          "usartConnect  [%2]").arg(ipcFlag).arg(usartFlag));
        }
        if (value1 == 'z')
        {
            QMessageBox::information(this, "Error", "摄像头没插好");
        }
    }
    if (!usartFlag)
    {
        usart->sendCheck();
    }
    int value2 = usart->receive(4);
    if (value2 == 1)
    {
        usartFlag = true;
        QFont font;
        font.setBold(true);
        font.setPointSize(20);
        checkInformationBox->setFont(font);
        checkInformationBox->setText(QString("Checking! If there is long time, please check the wiring!\n"
                                     "ipcConnect     [%1]\n"
                                     "usartConnect   [%2]").arg(ipcFlag).arg(usartFlag));
    }

    if (ipcFlag && usartFlag)
    {
        checkReadyTimer->stop();
        checkInformationBox->close();
        delete checkInformationBox;
        checkInformationBox = nullptr;
    }
}

void Widget::handleVideoFinishTimer()
{
    if (videoWidget->getState() == QMediaPlayer::StoppedState)
    {
        videoFinishTimer->stop();
        videoWidget->close();
        writePipe('p');
        if (videoWidget != nullptr)
        {
            delete videoWidget;
            videoWidget = nullptr;
        }
        ipcTimer->start();
        if (!usartWaitTimer->isActive())
        {
            usartWaitTimer->start();
        }
    }
}

void Widget::handleUsartWaitTImer()
{
    int value = usart->receive(4);
    if (value == 2)
    {
        waitingFlag = false;
        if (fullWorkFlag)
        {
            usartWaitTimer->stop();
            qDebug() << "clear";
            usart->clearBuffer();
            fullTimer->start();
        }
        return;
    }

    if (value == 3)
    {
        usartCompleteFlag = true;
        writePipe('p');
//        setTip("OK");
        ipcTimer->start();
        usartWaitTimer->stop();
        return;
    }
}

void Widget::handleUsartSendTimer()
{
    if (!waitingFlag)
    {
        usartSendTimer->stop();
        return;
    }
    if (fullWorkFlag)
    {
        usart->sendFullWork();
    }
    else
    {
        usart->sendDown(binIndex);
    }
}

void Widget::handleFullTimer()
{
    static int index = 0;
    if (index == 4)
    {
        fullTimer->stop();
        setFull();
        return;
    }
    int temp = usart->receiveDistance(4);
    if (temp)
    {
        distance[index] = temp;
        qDebug() << int(temp);
        ++index;
    }
}

void Widget::layout()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton(buttonLayout);

    QVBoxLayout *trashLayout = new QVBoxLayout();
    addTrashWidget(trashLayout);

    QVBoxLayout *tableLayout = new QVBoxLayout();
    addTable(tableLayout);

    QHBoxLayout *downLayout = new QHBoxLayout();
    downLayout->addLayout(tableLayout, 4);
    downLayout->addLayout(trashLayout, 5);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(buttonLayout);
    layout->addLayout(downLayout);
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

void Widget::addTable(QVBoxLayout *layout)
{
    table = new Table();
    QString name = QString(" ");
    QString tip = QString("当前垃圾：【%1】  OK！").arg(name);
    label = new QLabel(tip);
    label->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    label->setFont(font);
    layout->addWidget(table);
    layout->addWidget(label);
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

void Widget::timerInit()
{
    ipcTimer = new QTimer(this);
    connect(ipcTimer, &QTimer::timeout, this, &Widget::handleIpcTimer);
    ipcTimer->setInterval(100);

    checkReadyTimer = new QTimer(this);
    connect(checkReadyTimer, &QTimer::timeout, this, &Widget::handleCheckTimer);
    checkReadyTimer->setInterval(500);

    videoFinishTimer = new QTimer(this);
    connect(videoFinishTimer, &QTimer::timeout, this, &Widget::handleVideoFinishTimer);
    videoFinishTimer->setInterval(1000);

    usartWaitTimer = new QTimer(this);
    connect(usartWaitTimer, &QTimer::timeout, this, &Widget::handleUsartWaitTImer);
    usartWaitTimer->setInterval(500);

    usartSendTimer = new QTimer(this);
    connect(usartSendTimer, &QTimer::timeout, this, &Widget::handleUsartSendTimer);
    usartSendTimer->setInterval(1000);

    fullTimer = new QTimer(this);
    connect(fullTimer, &QTimer::timeout, this, &Widget::handleFullTimer);
    usartSendTimer->setInterval(100);
}

void Widget::usartInit()
{
    usart = new Usart();
    if (!usart->usartOpen())
    {
        QMessageBox::information(this, "Error", "串口打开失败", QMessageBox::Yes);
    }
}

void Widget::checkReady()
{
    checkInformationBox = new QMessageBox();
    checkInformationBox->setWindowFlags(Qt::WindowStaysOnTopHint);
    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    checkInformationBox->setFont(font);
    checkInformationBox->setText(QString("Checking! If there is long time, please check the wiring!\n"
                                 "ipcConnect     [%1]\n"
                                 "usartConnect   [%2]").arg(ipcFlag).arg(usartFlag));
    checkInformationBox->show();
    checkInformationBox->move(width() / 3, height() / 2);

    checkReadyTimer->start();
}

void Widget::setTip(QString name)
{
    QString tip = QString("当前垃圾：【%1】  OK！").arg(name);
    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    label->setFont(font);
    label->setText(tip);
}

void Widget::setFull()
{
    if (fullInformationBox != nullptr)
    {
        fullInformationBox->close();
        delete fullInformationBox;
        fullInformationBox = nullptr;
    }
    int thresh = 30;
    recoverableWidget->isFullJudge(distance[0] <= thresh);
    harmfulWidget->isFullJudge(distance[1] <= thresh);
    kitchenWidget->isFullJudge(distance[2] <= thresh);
    otherWidget->isFullJudge(distance[3] <= thresh);
}

