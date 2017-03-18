// Protocol: TCP
#include "winsockserverthread.h"
#include <QTextCodec>

WinSockServerThread::WinSockServerThread() {
    qDebug() << "°º¤ø,¸¸,ø¤º°`°º¤ø,SERVER,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸";
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSAStartup failed: " << iResult;
    } else {
        qDebug() << "WSAStartup succeeded!";
    }
    ConnectSocket = INVALID_SOCKET;
    // 1.
    //    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        qDebug() << "getaddrinfo failed: " << iResult;
        WSACleanup();
        return;
    }
    // 2.
    ListenSocket = INVALID_SOCKET;
    // 3. Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    // 4.
    if (ListenSocket == INVALID_SOCKET) {
        qDebug() << "Error at socket(): " << WSAGetLastError();
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    // 5. Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        qDebug() << "bind failed with error: " << WSAGetLastError();
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    freeaddrinfo(result);
    // 6. To listen on a socket
    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        qDebug() << "Listen failed with error: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Winsock server has been successfully set up.";
}

//void WinSockServerThread::setPortNumber() {
//    //1024 through 49151
//}

void WinSockServerThread::run() {
    // 7. Accept a client socket
    SOCKET ClientSocket;
    ClientSocket = INVALID_SOCKET;
    qDebug() << "All is well";
    //accept() is a blocking function, meaning that it will not finish until it accept()s a connection or an error occurs
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        qDebug() << "accept failed: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Woah! Don't panic.";
    //***Receiving and Sending Data on the Server***
//    char recvbuf[DEFAULT_BUFLEN];
    int iSendResult;

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);
        if (iResult > 0) {
//            qDebug() << "Server received message:" << QString::fromUtf8(recvbuf) << "(" << iResult << "bytes)";
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QString field = codec->toUnicode(recvbuf).trimmed();
            field=field.mid(0,field.indexOf("\t"));
            qDebug() << recvbuf;
            this->label->setText(field);
            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                qDebug() << "send failed: " << WSAGetLastError();
                closesocket(ClientSocket);
                WSACleanup();
                return;
            }
            qDebug() << "Bytes echoed (server): " << iSendResult;
        } else if (iResult == 0)
            qDebug() << "Connection closing...";
        else {
            qDebug() << "recv failed: " << WSAGetLastError();
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }
    } while (iResult > 0);
    qDebug() << "°º¤ø,¸¸,ø¤º°`°º¤ø,SERVER-END,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸";
    QString done;
    emit resultReady(done);
}

void WinSockServerThread::sendMessage(QByteArray message) {
    int size=message.size();
}

void WinSockServerThread::setNextLabelPointer(QLabel *label) {
    this->label=label;
}

