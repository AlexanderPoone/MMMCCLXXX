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
    void createEntry();
    void generateJson();
signals:
    void itemClicked(QListWidgetItem *item);
    void itemDoubleClicked(QListWidgetItem *item);
public slots:
    void search(QString keyword);
    void revealAll();
private slots:
    void onItemClicked(QListWidgetItem *item);
    void onItemDoubleClicked(QListWidgetItem *item);
private:
    void pushEntry(AlbumEntry *entry);
    void popEntry(AlbumEntry *entry);
    QList<AlbumEntry *> popped;
    QList<AlbumEntry *> pushed;
    QToolBox *toolBox;
    QStringList scanDirs;
//    AlbumEntry albumEntry;
};

#endif // MUSICLIBRARY_H
