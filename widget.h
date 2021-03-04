#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class TrashWidget;
class QLabel;

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

private:
    void addButton(QHBoxLayout *);
    void addTrashWidget(QVBoxLayout *);
    void connectButton();
    void setLabelWithWidget(QLabel *, TrashWidget *, QVBoxLayout *);

    QPushButton *classifyButton;
    QPushButton *isFullButton;
    QPushButton *advancedButton;
    QPushButton *setArgButton;

    TrashWidget *recoverableWidget;
    TrashWidget *harmfulWidget;
    TrashWidget *kitchenWidget;
    TrashWidget *otherWidget;

    Ui::Widget *ui;
};
#endif // WIDGET_H
