#pragma once
#include <windows.h>
#include <iostream>
#include <string>

#define CBR_300             300
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_38400           38400
#define CBR_57600           57600
#define CBR_128000          128000

using namespace std;

HANDLE openSerialPort(const wstring& portName, DWORD baudRate);

void sendMessage(HANDLE hSerial, const string& message);

string readMessage(HANDLE hSerial);
