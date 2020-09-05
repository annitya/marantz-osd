
#include "TelnetConnection.h"
#include <string>
#include <WS2tcpip.h>

using namespace std;

#pragma once
#pragma comment(lib, "WS2_32")
void TelnetConnection::connectMarantz() {         
    WSADATA wsaData;
        
    int iR = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (iR != 0) {
        return;
    }
    
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.10.128");
    addr.sin_port = htons(23);

    int connectionResult = connect(server, (SOCKADDR*)&addr, sizeof(addr));

    if (connectionResult == SOCKET_ERROR) {
        WSACleanup();           
        return;
    }

    int receiveResult;
    char buff[2048];

    int i = 0;

    do {
        receiveResult = recv(server, buff, sizeof(buff), 0);

        i++;
    } while (i < 100);

    
    if (receiveResult == SOCKET_ERROR) {
        WSACleanup();
        return;
    }                  

    WSACleanup();
}
