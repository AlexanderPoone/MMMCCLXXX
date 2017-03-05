#include "musiclibrary.h"

QLayout *mesh;

MusicLibrary::MusicLibrary(QGridLayout *container, QWidget *parent) {
    //TODO: PICKLE ALL THESE
    mesh=container;
    scan();
    for (int i; i<9; i++) {
        AlbumEntry *entry;
        entry=new AlbumEntry(parent);
        QPixmap pixmap(QStringLiteral("://album%1.jpg").arg(i));
        entry->setAlbumArt(pixmap);
        entry->setAlbumTitle("She Wolf");
        entry->setArtistName("Shakira");
        container->addLayout(entry,i/5, i%5);
    }
}

void MusicLibrary::scan() {
    //Scan paths in the QStringList scanDirs to add song entries.
    scanDirs << QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QDir tmpDir(scanDirs[0]);
    QStringList filters;
    filters << "*.wav" << "*.wave" << "*.mp3";
    tmpDir.setNameFilters(filters);
    qDebug() << tmpDir.entryList(); //entryInfoList();
}
