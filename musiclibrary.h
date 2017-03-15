#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QtWidgets>
#include <QDebug>
#include "albumentry.h"

class MusicLibrary : public QObject
{
    Q_OBJECT
public:
    //TODO: PICKLE ALL THESE
    MusicLibrary(QToolBox *toolBox, QWidget *parent);
//    MusicLibrary(QGridLayout *container, QWidget *parent);
    void scan();
    void addEntry();
    void generateJson();
signals:
public slots:
private:
    QToolBox *toolBox;
    QStringList scanDirs;
    AlbumEntry albumEntry;
};

#endif // MUSICLIBRARY_H
