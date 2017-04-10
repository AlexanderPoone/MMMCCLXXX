#ifndef WINSOCKCLIENTTHREAD_H
#define WINSOCKCLIENTTHREAD_H

#ifndef WIN32_LEAN_AND_MEAN         //Required, or else Winsock will override Windows.h and cause error.
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_BUFLEN 512

#include <winsock2.h>               //Winsock (P2P)
#include <ws2tcpip.h>               //Winsock (P2P)
//#include <iphlpapi.h>
#include <stdio.h>                  //Winsock (P2P)
#include <QThread>
#include <QFile>
#include <QDebug>
#include "wavassembler.h"

#pragma comment(lib, "Ws2_32.lib")  //Winsock (P2P)

class WinSockClientThread : public QThread
{
    Q_OBJECT
public:
//    WinSockClientThread();
    WinSockClientThread(int threadNumber);
    void init();
    void run() Q_DECL_OVERRIDE;
    void setMessage(QString message);
    void setMessageByPath(QString path);
    void freeSendbuf();
    void setIpLastFourBits(int ip);
    void sendPart(int bufSize);
    void setPortNumber(int port);
private:
    WavAssembler *wavAssembler;
    QString myip;
    QString myport;
    int threadNumber;

    int iResult;
    int iSendResult;
    WSADATA wsaData;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET ConnectSocket;
    char *sendbuf;
signals:
    void musicCatalogueReceived(QString rawJSON, int threadNumber);
    void connected(int threadNumber);
    void resultReady(const QString &s);
public slots:
    void pausePlayback();
};

#endif // WINSOCKCLIENTTHREAD_H
