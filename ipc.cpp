#include "ipc.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <QDebug>

#include <fcntl.h>

using namespace std;

char buf[32];
static int fd;

void startPython(std::string command)
{
    system(command.data());
}

void createPipe()
{
    fd = open("/home/faliks/Desktop/fifo.tmp", O_RDWR | O_NONBLOCK);
    if (-1 == fd)
    {
        fd = mkfifo("/home/faliks/Desktop/fifo.tmp", S_IRWXU);
        if (-1 == fd)
        {
            cout << "error mkfifo" << endl;
            exit(1);
        }
        fd = open("/home/faliks/Desktop/fifo.tmp", O_RDWR | O_NONBLOCK);
        if (-1 == fd)
        {
            cout <<  "error open" << endl;
            exit(1);
        }
    }
    cout << "create finish" << endl;
}


char readResult()
{
    int res;
    char value;
    fd = open("/home/faliks/Desktop/fifo.tmp", O_RDWR | O_NONBLOCK);
    res = read(fd, buf, sizeof(buf));
    if (-1 == res)
    {
        value = '0';
    }
    else
    {
        value = buf[0];
    }
    memset(buf, 0, sizeof(buf));
    return value;
}

void deletePipe()
{
    close(fd);
    unlink("/home/faliks/fifo.tmp");
}
