#include "widget.h"
#include "trashwidget.h"
#include "ipc.h"
#include "table.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
//    startPython("/home/faliks/pythonEnvironment/deepLearning/bin/python /home/faliks/Desktop/pythonProject/gongxunsai/predict.py");
    createPipe();
    w.show();
    return a.exec();
}
