#include "musiclibrary.h"

MusicLibrary::MusicLibrary(QToolBox *toolBox, QWidget *parent) {
    QFile exampleJSON(QStringLiteral("C:\\Users\\Alexandre Poon\\Documents\\sans_titre\\example.json"));
    if (!exampleJSON.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QJsonDocument internalDoc=QJsonDocument::fromJson(exampleJSON.readAll());
    QJsonObject internalObj=internalDoc.object();
    qDebug() << "+------------------------------JSON--------------------------+";
    qDebug() << '|' << "Num of (key, value) pairs:\t" << internalObj.size() << "\t\t|";
    qDebug() << '|' << "Computer name:\t\t" << internalObj.find(QStringLiteral("computerName")).value().toString() << "\t|";
    qDebug() << '|' << "IP Adress:\t\t\t" << internalObj.find(QStringLiteral("ip")).value().toString() << "\t|";
    qDebug() << '|' << "Num of albums:\t\t" << internalObj.find(QStringLiteral("albums")).value().toArray().size() << "\t\t|";
    qDebug() << '|' << "Reserved:\t\t" << internalObj.find(QStringLiteral("albums")).value().toArray()[0].toObject().find(QStringLiteral("albumTitle")).value().toString()<< "\t\t|";
    qDebug() << '|' << "Reserved:\t\t" << internalObj.find(QStringLiteral("albums")).value().toArray()[0].toObject().find(QStringLiteral("artist")).value().toString()<< "\t\t|";
    qDebug() << "+------------------------------------------------------------+";

    this->toolBox=toolBox;
    //    QList<QPair>
    for (int i=0; i<2; i++) {
        AlbumEntry *entry;
        entry=new AlbumEntry(parent);
        QPixmap pixmap(QStringLiteral("://album%1.jpg").arg(i));
        entry->setAlbumArt(pixmap);
        entry->setAlbumTitle("Shakira");
        entry->setArtistName("She Wolf");
        this->toolBox->addItem(entry,entry->getIcon(),entry->getTitleString());
    }
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
