#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "table.h"

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

private:
    void layout();
    void addButton(QHBoxLayout *);
    void addTrashWidget(QVBoxLayout *);
    void addTable(QVBoxLayout *);
    void connectButton();
    void setLabelWithWidget(QLabel *, TrashWidget *, QVBoxLayout *);
    void timerInit();
    void checkReady();

    QPushButton *classifyButton;
    QPushButton *isFullButton;
    QPushButton *advancedButton;
    QPushButton *setArgButton;

    TrashWidget *recoverableWidget;
    TrashWidget *harmfulWidget;
    TrashWidget *kitchenWidget;
    TrashWidget *otherWidget;

    QLabel *label;
    Table *table;
    QMessageBox *checkInformationBox;

    QString tip;
    QString name;
    QTimer *ipcTimer;
    QTimer *checkReadyTimer;

    bool ipcFlag = false;
    bool usartFlag = false;

    Ui::Widget *ui;
};
#endif // WIDGET_H
