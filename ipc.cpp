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

char bufRead[32];
char bufWrite[32];
static int fdr;
static int fdw;

const static char READFILE[] = "/home/faliks/Desktop/fifoPythonToCpp.tmp";
const static char WRITEFILE[] = "/home/faliks/Desktop/fifoCppToPython.tmp";

void startPython(std::string command)
{
    system(command.data());
}

void createPipe()
{
    fdr = open(READFILE, O_RDWR | O_NONBLOCK);
    fdw = open(WRITEFILE, O_RDWR | O_NONBLOCK);
    if (-1 == fdr || -1 == fdw)
    {
        fdr = mkfifo(READFILE, S_IRWXU);
        fdw = mkfifo(WRITEFILE, S_IRWXU);
        if (-1 == fdr || -1 == fdw)
        {
            cout << "error mkfifo" << endl;
            exit(1);
        }
        fdr = open(READFILE, O_RDWR | O_NONBLOCK);
        fdw = open(WRITEFILE, O_RDWR | O_NONBLOCK);
        if (-1 == fdr || -1 == fdw)
        {
            cout <<  "error open" << endl;
            exit(1);
        }
    }
}


char readResult()
{
    int res;
    char value;
    res = read(fdr, bufRead, sizeof(bufRead));
    if (-1 == res)
    {
        value = '0';
    }
    else
    {
        value = bufRead[0];
    }
    memset(bufRead, 0, sizeof(bufRead));
    return value;
}

void deletePipe()
{
    close(fdr);
    close(fdw);
    unlink(READFILE);
    unlink(WRITEFILE);
}

void writePipe(string s)
{
    int res = strcmp(bufWrite, s.data());
    res = write(fdw, bufWrite, strlen(bufWrite));
}
