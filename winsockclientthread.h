#ifndef WINSOCKCLIENTTHREAD_H
#define WINSOCKCLIENTTHREAD_H

#ifndef WIN32_LEAN_AND_MEAN         //Required, or else Winsock will override Windows.h and cause error.
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_PORT "6894"
#define DEFAULT_BUFLEN 512

#include <winsock2.h>               //Winsock (P2P)
#include <ws2tcpip.h>               //Winsock (P2P)
//#include <iphlpapi.h>
#include <stdio.h>                  //Winsock (P2P)
#include <QThread>
#include <QDebug>

#pragma comment(lib, "Ws2_32.lib")  //Winsock (P2P)

class WinSockClientThread : public QThread
{
    Q_OBJECT
public:
//    WinSockClientThread();
    WinSockClientThread(int threadNumber);
    void run() Q_DECL_OVERRIDE;
    void sendMessage(QByteArray message);
private:
    int threadNumber;

    int iResult;
    WSADATA wsaData;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET ConnectSocket;
signals:
    void connected(int threadNumber);
    void resultReady(const QString &s);
};

#endif // WINSOCKCLIENTTHREAD_H
