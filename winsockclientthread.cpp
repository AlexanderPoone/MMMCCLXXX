#include "winsockclientthread.h"

void WinSockClientThread::run() {
    //    ioctlsocket(ListenSocket,FIONBIO,1);
    QString done;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        qDebug() << "getaddrinfo failed: " << iResult;
        WSACleanup();
    } else {
        qDebug() << "Winsock client has been successfully set up.";
    }
    // Attempt to connect to the first address returned by the call to getaddrinfo
    ptr=result;
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    emit resultReady(done);
}
