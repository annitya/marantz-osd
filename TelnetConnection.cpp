
#include <string>
#include <iomanip>
#include <sstream>
#include <WS2tcpip.h>
#include <qstring.h>

using namespace std;

#pragma once
#pragma comment(lib, "WS2_32")
class TelnetConnection
{   
private:
    SOCKET marantzSocket;
    string address;     
   
public:   
    TelnetConnection(string address) {        
        this->address = address;        
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

    char* getCurrentMessage() {
        int receiveResult;
        char buff[2048];
               
        receiveResult = recv(marantzSocket, buff, sizeof(buff), 0);

        if (receiveResult == SOCKET_ERROR) {
            // WSACleanup();
            return "";
        }
        
        return buff;
    }
    
    void close() {
        closesocket(marantzSocket);
    }
};
