
#include <string>
#include <iomanip>
#include <sstream>
#include <WS2tcpip.h>
#include <qobject.h>
#include <qstring.h>
#include <qtimer.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

#pragma once
#pragma comment(lib, "WS2_32")
class TelnetConnection
{
private:
    SOCKET marantzSocket;
    string address;
    QObject* textContainer;    

    string formatMessage(string message) {
        float value = stof(message) - 80;
        
        stringstream stream;
        stream << fixed << setprecision(1) << value;
        string dbValue = stream.str();
       
        return dbValue + " dB";
    }

    string parseMessage(char *buffer) {
        string value = (string)buffer;

        int valueEndIndex = value.find("\r") - 2;       
        string numberPart = value.substr(2, valueEndIndex);
        // MVMAX 80\rAX 80\r => max volume
        if (numberPart[0] == 'M') { 
            return "";
        }
        // MV47\r 80\rAX 80\r => current integer volume
        if (numberPart.length() == 2) {
            return formatMessage(numberPart);
        }
        // MV475\r80\rAX 80\r => current volume with "decimal"
        if (numberPart.length() == 3) {
            string numberValue = numberPart.substr(0, 2) + "." + numberPart[2];
            return formatMessage(numberValue);
        }

        return "";
    }

public:
    TelnetConnection(string address, QObject* textContainer) {        
        this->address = address;
        this->textContainer = textContainer;
    }

    bool open()
    {
        WSADATA wsaData;

        int iR = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (iR != 0) {
            return false;
        }

        marantzSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (marantzSocket == INVALID_SOCKET) {
            WSACleanup();
            return false;
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        addr.sin_port = htons(23);

        int connectionResult = connect(marantzSocket, (SOCKADDR*)&addr, sizeof(addr));

        if (connectionResult == SOCKET_ERROR) {
            WSACleanup();
            return false;
        }
        
        return true;
    }

    string getCurrentMessage() {
        int receiveResult;
        char buff[2048];
               
        receiveResult = recv(marantzSocket, buff, sizeof(buff), 0);

        if (receiveResult == SOCKET_ERROR) {
            // WSACleanup();
            return "";
        }
        
        return parseMessage(buff);
    }

    void beginUpdates() {        
        QTimer::singleShot(0, [this] {
            string currentValue = this->getCurrentMessage();
           
            if (currentValue.length() > 0) {
                this->textContainer->setProperty("text", QString::fromStdString(currentValue));                                
            }

            this->beginUpdates();
        });        
    }

    void close() {
        closesocket(marantzSocket);
    }
};
