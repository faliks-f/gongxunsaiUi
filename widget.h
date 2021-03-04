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
    void handleTimer1Out();
private:
    void layout();
    void addButton(QHBoxLayout *);
    void addTrashWidget(QVBoxLayout *);
    void addTable(QVBoxLayout *);
    void connectButton();
    void setLabelWithWidget(QLabel *, TrashWidget *, QVBoxLayout *);
    void timerInit();

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
    QString tip;
    QString name;
    QTimer *timer1;

    Ui::Widget *ui;
};
#endif // WIDGET_H
