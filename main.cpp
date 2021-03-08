#include "widget.h"
#include "trashwidget.h"
#include "ipc.h"
#include "table.h"
#include <iostream>
#include <pthread.h>
#include <QApplication>
#include "videowidget.h"

void *startPythonThread(void *args);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createPipe();
    pthread_t t ;
    int ret = pthread_create(&t, nullptr, startPythonThread, nullptr);
    if (ret != 0)
    {
        std::cout << "pthread_create error: error_code=" << ret << std::endl;
        exit(1);
    }
//    Widget w;
//    w.show();
    VideoWidget w;
    w.show();
    return a.exec();
}

void *startPythonThread(void *args)
{
//    startPython("/home/faliks/pythonEnvironment/deepLearning/bin/python /home/faliks/Desktop/pythonProject/gongxunsai/predict.py");
    return 0;
}
