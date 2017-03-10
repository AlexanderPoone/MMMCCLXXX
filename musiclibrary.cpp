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
        container->addLayout(entry,i/2, i%2);
    }
}

void MusicLibrary::scan() {
    //Scan paths in the QStringList scanDirs to add song entries.
    scanDirs << QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QDir tmpDir(scanDirs[0]);
    QStringList filters;
    filters << "*.wav" << "*.wave" << "*.mp3";
    tmpDir.setNameFilters(filters);
//    qDebug() << tmpDir.entryList(); //entryInfoList();
    QFile dc(QStringLiteral("db.json"));
    dc.open(QFile::ReadWrite | QFile::Text);
    QByteArray contents=dc.readAll();
    qDebug() << contents.left(100);
    qDebug() << dc.exists();
    QJsonDocument internalDoc;
//    internalDoc=QJsonDocument::fromJson(doc.readAll());
}
