#include "ipc.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void startPython(std::string command)
{
    system(command.data());
}
