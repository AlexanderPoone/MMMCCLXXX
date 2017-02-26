#ifndef GENIUSMANAGER_H
#define GENIUSMANAGER_H

#include <QtNetwork>

class GeniusManager : public QNetworkAccessManager
{
public:
    GeniusManager();
    void result();
};

#endif // GENIUSMANAGER_H
