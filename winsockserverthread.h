#ifndef WINSOCKSERVERTHREAD_H
#define WINSOCKSERVERTHREAD_H

#ifndef WIN32_LEAN_AND_MEAN         //Required, or else Winsock will override Windows.h and cause error.
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_BUFLEN 512

#include <winsock2.h>               //Winsock (P2P)
#include <ws2tcpip.h>               //Winsock (P2P)
//#include <iphlpapi.h>
#include <stdio.h>                  //Winsock (P2P)
#include <QThread>
#include <QDebug>
#include <QLabel>
#include <QFile>

#pragma comment(lib, "Ws2_32.lib")  //Winsock (P2P)

class WinSockServerThread : public QThread
{
    Q_OBJECT
public:
    WinSockServerThread();
    void init();
//    void run() override;
    void run() Q_DECL_OVERRIDE;
    void resolveLocalAddress();
    void setMessage(QString message);
    void setMessageByPath(QString path);
    void setNextLabelPointer(QLabel *label);
    void setIpLastFourBits(int ip);
    void setPortNumber(int port);
private:
    void sendPart(int bufSize);
    SOCKET ClientSocket;
    int iSendResult;

    QString myip;
    QString myport;
    QLabel *label;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    WSADATA wsaData;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET ConnectSocket;
    SOCKET ListenSocket;
    char *sendbuf;
signals:
    void connected(const QString &ip, const QString &port);
    void resultReady(const QString &s);
};
#endif // WINSOCKSERVERTHREAD_H
