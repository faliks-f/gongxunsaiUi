#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "table.h"
#include "videowidget.h"
#include "usart.h"

class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class TrashWidget;
class QLabel;
class QTimer;
class QMessageBox;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void classifyButtonSlot();
    void isFullButtonSlot();
    void advancedButtonSlot();
    void setArgButtonSlot();
    void handleIpcTimer();
    void handleCheckTimer();
    void handleVideoFinishTimer();
    void handleUsartWaitTImer();
    void handleUsartSendTimer();
    void handleFullTimer();

private:
    void layout();
    void addButton(QHBoxLayout *);
    void addTrashWidget(QVBoxLayout *);
    void addTable(QVBoxLayout *);
    void connectButton();
    void setLabelWithWidget(QLabel *, TrashWidget *, QVBoxLayout *);
    void timerInit();
    void usartInit();
    void checkReady();
    void setTip(QString);
    void setFull();

    QPushButton *classifyButton;
    QPushButton *isFullButton;
    QPushButton *advancedButton;
    QPushButton *setArgButton;

    TrashWidget *recoverableWidget;
    TrashWidget *harmfulWidget;
    TrashWidget *kitchenWidget;
    TrashWidget *otherWidget;

    VideoWidget *videoWidget = nullptr;

    QLabel *label;
    Table *table;
    QMessageBox *checkInformationBox = nullptr;
    QMessageBox *fullInformationBox = nullptr;

    QTimer *ipcTimer;
    QTimer *checkReadyTimer;
    QTimer *videoFinishTimer;
    QTimer *usartWaitTimer;
    QTimer *usartSendTimer;
    QTimer *fullTimer;

    Usart *usart;

    bool ipcFlag = false;
    bool usartFlag = false;
    bool waitingFlag = false;
    bool usartCompleteFlag = true;
    bool fullWorkFlag = false;

    int binIndex = 0;
    char distance[4] = {0, 0, 0, 0};

    Ui::Widget *ui;
};
#endif // WIDGET_H
