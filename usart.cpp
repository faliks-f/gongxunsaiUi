#include "usart.h"
#include <QDebug>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <cstring>

using namespace std;

static const char insure[4] = {0x75, 0x01, 0x01, 0x00};
static const char check[4] = {0x75, 0x02, 0x10, 0x00};
static const char down[4][4] = {{0x75, 0x03, 0x01, 0x00},
                                {0x75, 0x03, 0x02, 0x00},
                                {0x75, 0x03, 0x03, 0x00},
                                {0x75, 0x03, 0x04, 0x00}};
static const char complete[4] = {0x75, 0x04, 0x01, 0x00};
static const char fullWork[4] = {0x75, 0x05, 0x10, 0x00};

Usart::Usart()
{
    serial = nullptr;
}

bool Usart::usartOpen()
{
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    if (list.empty())
    {
        return false;
    }
    QSerialPortInfo info;
    for (auto x: list)
    {
        if (x.portName() == "ttyUSB0")
            info = x;
    }
    serial = new QSerialPort(info);
    if (serial->isOpen())
    {
        serial->clear();
        serial->close();
    }
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    if (serial->isOpen())
    {
        return true;
    }
    return false;
}

int Usart::receive(int i)
{
    int len = serial->read(data, i);
    if (len == 0)
    {
        return -1;
    }
    if (!strcmp(data, check))
    {
        return 1;
    }

    if (!strcmp(data, insure))
    {
        return 2;
    }

    if (!strcmp(data, complete))
    {
        return 3;
    }
    memset(data, 0, sizeof(data));
    return -1;
}

void Usart::sendCheck()
{
    serial->write(check, 4);
}


void Usart::usartClose()
{
    if (serial != nullptr)
    {
        if (serial->isOpen())
        {
            serial->close();
        }
        delete serial;
        serial = nullptr;
    }
}

void Usart::sendDown(int i)
{
    serial->write(down[i], 4);
}

void Usart::sendFullWork()
{
    serial->write(fullWork, 4);
}

int Usart::receiveDistance(int i)
{
    int len = serial->read(data, i);
    int distance = 0;
    if (len != 0)
    {
        if (data[0] == 0x75)
        {
            if (data[1] == 0x06)
            {
                if (data[3] == 0x00)
                {
                    distance = data[2];
                }
            }
        }
//        cout << endl;
    }
    memset(data, -1, sizeof(data));
    return distance;
}

void Usart::clearBuffer()
{
    while (serial->read(data, 32));
    memset(data, 0, sizeof (data));
}
