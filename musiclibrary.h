#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QObject>
#include "albumentry.h"

class MusicLibrary : public QObject
{
    Q_OBJECT
public:
    //TODO: PICKLE ALL THESE
    MusicLibrary(QGridLayout *container, QWidget *parent);
    void scan();
    void addEntry();
signals:
public slots:
private:
    QStringList scanDirs;
    AlbumEntry albumEntry;
};

#endif // MUSICLIBRARY_H
