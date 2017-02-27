#ifndef GENIUSMANAGER_H
#define GENIUSMANAGER_H

#include <QtNetwork>
#include <QtWebEngineWidgets>

class GeniusManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    GeniusManager(QLabel *label, QString artist, QString songTitle);
private slots:
    void result();
    void httpFinished();
};

#endif // GENIUSMANAGER_H
