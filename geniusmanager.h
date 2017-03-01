#ifndef GENIUSMANAGER_H
#define GENIUSMANAGER_H

#include <QtNetwork>
#include <QtWidgets>
//#include <QtWebEngineWidgets>

class GeniusManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    GeniusManager(QLabel *label, QLabel *artistPhotoL, QLabel *albumArtL, QString artist, QString songTitle);
private slots:
    void result();
    void httpFinished();
    void artistPhotoFetched();
    void albumArtFetched();
};

#endif // GENIUSMANAGER_H
