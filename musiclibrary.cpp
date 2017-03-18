#include "musiclibrary.h"

MusicLibrary::MusicLibrary(QToolBox *toolBox, QWidget *parent) {
    this->toolBox=toolBox;

    QFile exampleJSON(QStringLiteral("C:\\Users\\Alexandre Poon\\Documents\\sans_titre\\example.json"));
    if (!exampleJSON.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QJsonDocument internalDoc=QJsonDocument::fromJson(exampleJSON.readAll());
    QJsonObject internalObj=internalDoc.object();
    qDebug() << "+------------------------------JSON--------------------------+";
    qDebug() << '|' << "Num of (key, value) pairs:\t" << internalObj.size() << "\t\t|";
    qDebug() << '|' << "Computer name:\t\t" << internalObj.find(QStringLiteral("computerName")).value().toString() << "\t|";
    qDebug() << '|' << "IP Adress:\t\t\t" << internalObj.find(QStringLiteral("ip")).value().toString() << "\t|";
    QJsonArray albums=internalObj.find(QStringLiteral("albums")).value().toArray();
    int numAlbums=albums.size();
    qDebug() << '|' << "Num of albums:\t\t" << numAlbums << "\t\t|";
    for (int i=0; i<numAlbums; i++) {
        AlbumEntry *entry;
        entry=new AlbumEntry(parent);
        QPixmap pixmap(QStringLiteral("://album%1.jpg").arg(i));
        entry->setAlbumArt(pixmap);
        entry->setAlbumTitle(albums[i].toObject().find(QStringLiteral("albumTitle")).value().toString());
        entry->setArtistName(albums[i].toObject().find(QStringLiteral("artist")).value().toString());
        entry->setTracks(albums[i].toObject().find(QStringLiteral("tracks")).value().toArray());
        this->toolBox->addItem(entry,entry->getIcon(),entry->getTitleString());
        qDebug() << '|' << "Reserved:\t\t" << albums[i].toObject().find(QStringLiteral("albumTitle")).value().toString()<< "\t\t|";
        qDebug() << '|' << "Reserved:\t\t" << albums[i].toObject().find(QStringLiteral("artist")).value().toString()<< "\t\t|";
        qDebug() << '|' << "Num of tracks:\t\t" << albums[i].toObject().find(QStringLiteral("tracks")).value().toArray().size()<< "\t\t|";
        if (i==0) entry->hide();
    }
    toolBox->removeItem(1);
//    toolBox->findChild<QWidget *>()->hide();
    qDebug() << "+------------------------------------------------------------+";

    //    QList<QPair>
}

//MusicLibrary::MusicLibrary(QGridLayout *container, QWidget *parent) {
//    //TODO: PICKLE ALL THESE
//    mesh=container;
//    scan();
//    for (int i=0; i<0; i++) {
//        AlbumEntry *entry;
//        entry=new AlbumEntry(parent);
//        QPixmap pixmap(QStringLiteral("://album%1.jpg").arg(i));
//        entry->setAlbumArt(pixmap);
//        entry->setAlbumTitle("She Wolf");
//        entry->setArtistName("Shakira");
////        container->addLayout(entry,i/2, i%2);
//    }
//}

void MusicLibrary::scan() {
    //Scan paths in the QStringList scanDirs to add song entries.
    scanDirs << QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QDir tmpDir(scanDirs[0]);
    QStringList filters;
    filters << "*.wav" << "*.wave" << "*.mp3";
    tmpDir.setNameFilters(filters);
    //    qDebug() << tmpDir.entryList(); //entryInfoList();
    //    QFile dc(QStringLiteral("db.json"));
    //    dc.open(QFile::ReadWrite | QFile::Text);
    //    QByteArray contents=dc.readAll();
    //    qDebug() << contents.left(100);
    //    qDebug() << dc.exists();
    //    QJsonDocument internalDoc;
    //    internalDoc=QJsonDocument::fromJson(doc.readAll());
}

void MusicLibrary::generateJson() {
    QJsonObject object
    {
        {"computerName", "myCheapWorkstation"},
        {"ip", "127.0.0.1"},
        {"tracks", QJsonArray()},
    };
}
