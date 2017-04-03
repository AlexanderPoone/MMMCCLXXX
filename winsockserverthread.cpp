// Server sends stuff

// Protocol: TCP
#include "winsockserverthread.h"
#include <QTextCodec>

using namespace std;

WinSockServerThread::WinSockServerThread() {

}

void WinSockServerThread::resolveLocalAddress() {
    // ↓ TESTING ↓
    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        qDebug() << "Exiting: Error" << WSAGetLastError() << "when getting local host name." << endl;
        return;
    }
    qDebug() << "Host name is" << ac;
    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        qDebug() << "Exiting: Bad host lookup.";
        return;
    }
    int sizeOfList=sizeof(phe->h_addr_list)/sizeof(phe->h_addr_list[0]);
    struct in_addr addr;
    if (sizeOfList>2) {
        memcpy(&addr, phe->h_addr_list[2], sizeof(struct in_addr));
        qDebug() << "Address:" << inet_ntoa(addr);
    }
    // ↑ TESTING ↑
}

void WinSockServerThread::init() {
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
    QByteArray arrayP = myport.toLocal8Bit();
    char* bufferP = arrayP.data();
    iResult = getaddrinfo(NULL, bufferP, &hints, &result);


    // ↓ TESTING ↓
    //    char ac[80];
    //    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
    //        qDebug() << "Exiting: Error" << WSAGetLastError() << "when getting local host name." << endl;
    //        return;
    //    }
    //    qDebug() << "Host name is" << ac;
    //    struct hostent *phe = gethostbyname(ac);
    //    if (phe == 0) {
    //        qDebug() << "Exiting: Bad host lookup.";
    //        return;
    //    }
    //    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
    //        struct in_addr addr;
    //        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
    //        qDebug() << "Address" << i << ":" << inet_ntoa(addr);
    //    }
    // ↑ TESTING ↑


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
    // 5. Setup the TCP listening socket: DO NOT HARD CODE
    // ↓ TESTING ↓
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    QByteArray array = myip.toLocal8Bit();
    char* buffer = array.data();
    server.sin_addr.s_addr = inet_addr(buffer);
    server.sin_port = htons(myport.toInt());
    // ↑ TESTING ↑
    iResult = bind(ListenSocket, (struct sockaddr *)&server, (int)result->ai_addrlen); //result->ai_addr
    if (iResult == SOCKET_ERROR) {
        qDebug() << "bind failed with error: " << WSAGetLastError();
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    freeaddrinfo(result);
    // 6. To listen on a socket: "Will somebody please call me?"
    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        qDebug() << "Listen failed with error: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Winsock server has been successfully set up.";
    emit connected(myip, myport);
}

void WinSockServerThread::run() {
    // 7. Accept a client socket: "Thank you for calling port 3490."
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



    // ***CRITICAL ERROR HERE: Receiving and Sending Data on the Server***
    //    char recvbuf[DEFAULT_BUFLEN];

    // Receive until the peer shuts down the connection
//    strcpy(sendbuf, QString("test").toStdString().c_str());
//    do {
//        iSendResult = send(ClientSocket, sendbuf, sizeof(sendbuf), 0);
//    } while (1);




    do {

        iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);
        if (iResult > 0) {
            //            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            //            QString field = codec->toUnicode(recvbuf).trimmed();
            QString field=recvbuf;
            field=field.mid(0,field.indexOf("\t"));
            qDebug() << "Receives (server):" << field << "(" << iResult << "bytes)";
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
        } else if (iResult == 0) {
            //            qDebug() << "Connection closing...";
        } else {
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

void WinSockServerThread::setMessage(QString message) {
    message.append("\t");
    //    QByteArray tmp1=message.toUtf8();
    sendbuf=(char *) malloc(sizeof(message.toStdString().c_str()));
    strcpy(sendbuf, message.toStdString().c_str());
    qDebug() << "Original msg: " << sendbuf << "(" << sizeof(message.toStdString().c_str()) << "bytes)";
}

void WinSockServerThread::setMessageByPath(QString path) {
    qDebug() << path;
    QFile plainText(path);
    if (!plainText.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while (!plainText.atEnd()) {
        char *buffer = (char *) malloc(256);
        plainText.read(buffer, 256);
        qDebug() << buffer;
        free(buffer);
    }
}

void WinSockServerThread::sendPart() {
    if (iResult > 0) {
        //            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        //            QString field = codec->toUnicode(recvbuf).trimmed();
//        QString field=recvbuf;
//        field=field.mid(0,field.indexOf("\t"));
//        qDebug() << "Receives (server):" << field << "(" << iResult << "bytes)";
//        this->label->setText(field);
        // Echo the buffer back to the sender
        iSendResult = send(ClientSocket, recvbuf, iResult, 0);
        if (iSendResult == SOCKET_ERROR) {
            qDebug() << "send failed: " << WSAGetLastError();
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }
        qDebug() << "Bytes sent (server): " << iSendResult;
    }
}

void WinSockServerThread::setNextLabelPointer(QLabel *label) {
    this->label=label;
}

void WinSockServerThread::setIpLastFourBits(int ip) {
    myip = QString("127.0.0.%1").arg(ip);
    qDebug() << myip << ip;
    //    //1024 through 49151
}

void WinSockServerThread::setPortNumber(int port) {
    myport = QString::number(port);
}
