// Clients receives stuff, client 1: R, client 2: G, client 3: B

//whoareyou: The getpeername function retrieves the address of the peer to which a socket is connected.
//int getpeername(_In_ SOCKET s, _Out_ struct sockaddr *name, _Inout_ int *namelen);
//s [in] A descriptor identifying a connected socket.
//name [out] The SOCKADDR structure that receives the address of the peer.
//namelen [in, out] A pointer to the size, in bytes, of the name parameter

//whoami: The gethostname function retrieves the standard host name for the local computer.
//int gethostname(_Out_ char *name, _In_ int namelen);
//name [out] A pointer to a buffer that receives the local host name.
//namelen [in] The length, in bytes, of the buffer pointed to by the name parameter.

#include "winsockclientthread.h"

//void WinSockClientThread::setPortNumber() {
//    //1024 through 49151
//}

WinSockClientThread::WinSockClientThread(int threadNumber) {
    this->threadNumber=threadNumber;
}

void WinSockClientThread::init() {
    //    addrinfo.sin_addr.s_addr = INADDR_ANY;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;                                            // Protocol: TCP
    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.7", "6894", &hints, &result);          //"127.0.0.1"/"192.168.192.1"
    if (iResult != 0) {
        qDebug() << "getaddrinfo failed: " << iResult;
        WSACleanup();
        return;
    }
    qDebug() << "Winsock client" << threadNumber << "has been successfully set up.";
    // Attempt to connect to the first address returned by the call to getaddrinfo
    ptr=result;
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        qDebug() << "Error at socket(): " << WSAGetLastError();
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) {
        qDebug() << "Unable to connect to server!";
        WSACleanup();
        return;
    }
}


void WinSockClientThread::run() {
    // Receiving and Sending Data on the Client

//    setMessage(QString::fromUtf8("2017年2月22號，天文學家宣布圍繞 TRAPPIST-1 嘅外行星加多四個。"));
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
//    char *sendbuf = QString("I am a client, short and stout").toLatin1().data();
//    char *sendbuf = QString("2017年2月22號，天文學家宣布圍繞 TRAPPIST-1 嘅外行星加多四個。").toUtf8().data();
//    QByteArray tmp=QString::fromUtf8("2017年2月22號，天文學家宣布圍繞 TRAPPIST-1 嘅外行星加多四個。\t").toUtf8();
//    sendbuf = tmp.data();
//    qDebug() << "Original msg: " << sendbuf;

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0); //(int) strlen(sendbuf)
    if (iResult == SOCKET_ERROR) {
        qDebug() << "send failed: " << WSAGetLastError();
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Bytes sent (client):" << iResult;


    // Shutdown the connection for sending since no more data will be sent
    // The client can still use the ConnectSocket for receiving data
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        qDebug() << "shutdown failed: " << WSAGetLastError();
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }


    // Receive data until the server closes the connection
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            qDebug() << "Client" << threadNumber << "received message:" << QString::fromUtf8(recvbuf) << "(" << iResult << "bytes)";
        else if (iResult == 0)
            qDebug() << "Connection closed";
        else
            qDebug() << "recv failed: " << WSAGetLastError();
    } while (iResult > 0);
    // // // // // // // // // // // // // // // // // // // //
    // QString done;                                         //
    // emit resultReady(done);                               //
    // // // // // // // // // // // // // // // // // // // //
}

void WinSockClientThread::setMessage(QString message) {
    message.append("\t");
//    QByteArray tmp1=message.toUtf8();
    sendbuf=(char *) malloc(sizeof(message.toStdString().c_str()));
    strcpy(sendbuf, message.toStdString().c_str());
    qDebug() << "Original msg: " << sendbuf << "(" << sizeof(message.toStdString().c_str()) << "bytes)";
}

void WinSockClientThread::setMessageByPath(QString path) {
}

void WinSockClientThread::freeSendbuf() {
    free(sendbuf);
}