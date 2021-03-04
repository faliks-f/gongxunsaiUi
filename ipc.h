#ifndef IPC_H
#define IPC_H

#include <string>

void startPython(std::string);
void createPipe();
char readResult();
void deletePipe();

#endif // IPC_H
