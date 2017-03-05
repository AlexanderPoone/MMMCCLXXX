#include "musiclibrary.h"

QLayout *mesh;

MusicLibrary::MusicLibrary(QGridLayout *container, QWidget *parent) {
    //TODO: PICKLE ALL THESE
    mesh=container;
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

MusicLibrary::scan() {
    //Scan paths in the QStringList scanDirs to add song entries.
}
