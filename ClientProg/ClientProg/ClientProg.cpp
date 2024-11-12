#include "SerialPortFile.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    while (true) {

        wstring portName;
        wcout << L"Enter port name or type 'end' to quit: ";
        getline(wcin, portName);

        if (portName == L"end") {
            break;
        }

        cout << "Select port speed:" << endl;
        cout << "for 300 press 1" << endl;
        cout << "for 1200 press 2" << endl;
        cout << "for 2400 press 3" << endl;
        cout << "for 4800 press 4" << endl;
        cout << "for 9600 press 5" << endl;
        cout << "for 14400 press 6" << endl;
        cout << "for 38400 press 7" << endl;
        cout << "for 57600 press 8" << endl;
        cout << "for 128000 press 9" << endl;
        cout << "Pick the desired port speed: ";

        int choice;
        DWORD portSpeed;

        cin >> choice;
        switch (choice) {
        case 1: portSpeed = CBR_300; break;
        case 2: portSpeed = CBR_1200; break;
        case 3: portSpeed = CBR_2400; break;
        case 4: portSpeed = CBR_4800; break;
        case 5: portSpeed = CBR_9600; break;
        case 6: portSpeed = CBR_14400; break;
        case 7: portSpeed = CBR_38400; break;
        case 8: portSpeed = CBR_57600; break;
        case 9: portSpeed = CBR_128000; break;
        default:
            cout << "Try again. Invalid selection." << endl;
            cin.ignore();
            continue;
        }

        cin.ignore();

        while (true) {

            string messageToSend;
            cout << "Enter message to send: ";
            getline(cin, messageToSend);

            HANDLE hSerial = openSerialPort(portName, portSpeed);
            if (hSerial == INVALID_HANDLE_VALUE) {
                cout << "Try again. Failed to open serial port." << endl;
                break;
            }

            sendMessage(hSerial, messageToSend);
            cout << "Message sent: " << messageToSend << endl;

            cout << "- - - Waiting for response - - -" << endl;
            string receivedMessage = readMessage(hSerial);
            cout << "Received message: " << receivedMessage;

            CloseHandle(hSerial);
            cout << "Serial port closed.\n" << endl;

            cout << "Continue?\n 'n' to send new message,\n 'c' to select a new port, \n another to exit: ";
            string cont;
            cin >> cont;
            cin.ignore();

            if (cont == "c") { break; }
            else if (cont != "n" && cont != "N") {
                cout << "Exit from program." << endl;
                return 0;
            }

        }
    }
    cout << "Exit from program." << endl;
    return 0;
}
