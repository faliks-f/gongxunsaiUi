#ifndef USART_H
#define USART_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Usart
{
public:
    Usart();

    bool usartOpen();
    int receive(int i);
    void sendCheck();
    void usartClose();
    void sendDown(int i);
    void sendFullWork();
    int receiveDistance(int i);
    void sendTest(char);
    void sendInsure();
    void clearBuffer();

private:
    QSerialPort *serial;
    char data[64];
};

#endif // USART_H
