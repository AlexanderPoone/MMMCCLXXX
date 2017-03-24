#include "musiclibrary.h"

//QListWidget {\n  position:relative;\n  padding:50px 15px;\n  margin:1em 0 3em;\n  border:10px solid #5a8f00;\n  text-align:center;\n  color:#333;\n  background:#fff;\n  border-radius:20px;\n}\nQListWidget:before {\n  content:"";\n  position:absolute;\n  z-index:10;\n  bottom:-40px;\n  left:50px;\n  width:50px;\n  height:30px;\n  border-style:solid;\n  border-width:0 10px 10px 0;\n  border-color:#5a8f00;\n  background:transparent;\n  /* css3 */\n  -webkit-border-bottom-right-radius:80px 50px;\n  -moz-border-radius-bottomright:80px 50px;\n  border-bottom-right-radius:80px 50px;\n  /* reduce the damage in FF3.0 */\n  display:block;\n}\nQListWidget:after {\n  content:"";\n  position:absolute;\n  z-index:10;\n  bottom:-40px;\n  left:50px;\n  width:20px;\n  height:30px;\n  border-style:solid;\n  border-width:0 10px 10px 0;\n  border-color:#5a8f00;\n  background:transparent;\n  /* css3 */\n  -webkit-border-bottom-right-radius:40px 50px;\n  -moz-border-radius-bottomright:40px 50px;\n  border-bottom-right-radius:40px 50px;\n  /* reduce the damage in FF3.0 */\n  display:block;\n}

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
//        entry->setToolBoxPosition(this->toolBox->count()-1);
//        qDebug() << '|' << "Place in ToolBox:\t\t" << entry->getToolBoxPosition();
        pushed.append(entry);
        qDebug() << "+-------------------------next entry-------------------------+";
    }

    pushed.at(0)->hide();
    //pushed.at(0)->setParent(NULL);
    toolBox->removeItem(0); //entry->getToolBoxPosition()
    popped.append(pushed.at(0));
    pushed.removeAt(0);
    toolBox->addItem(popped.last(), popped.last()->getIcon(), popped.last()->getTitleString());
    pushed.append(popped.last());
    popped.removeLast();



//    popped.at(0)->show();
//    toolBox->findChild<QWidget *>()->hide();
    qDebug() << "+------------------------------------------------------------+";

    //    QList<QPair>
}

void MusicLibrary::search(QString keyword) {
    qDebug() << "The keyword is " << keyword;
    if (keyword.isEmpty()) {
        qDebug() << "Empty";
        revealAll();
        return;
    }
//    keyword.prepend("(");
//    keyword.append(")");
    QRegExp titleRegex(keyword, Qt::CaseInsensitive);
    QRegExp artistRegex(keyword, Qt::CaseInsensitive);
    QString title;
    QString artist;
    for (int i=pushed.length()-1; i>=0; i--) {
        title=pushed.at(i)->getAlbumTitle();
        artist=pushed.at(i)->getArtistName();
//        qDebug() << title << artist << titleRegex << artistRegex;
        titleRegex.indexIn(title);
        artistRegex.indexIn(artist);
//        titleRegex.cap();
//        artistRegex.cap();
        if ((titleRegex.cap().isEmpty()) && (artistRegex.cap().isEmpty())) {
            pushed.at(i)->hide();
            //pushed.at(i)->setParent(NULL);
            toolBox->removeItem(i);
            popped.append(pushed.at(i));
            pushed.removeAt(i);
        }
    }
    for (int i=popped.length()-1; i>=0; i--) {
        title=popped.at(i)->getAlbumTitle();
        artist=popped.at(i)->getArtistName();
        titleRegex.indexIn(title);
        artistRegex.indexIn(artist);
//        titleRegex.cap();
//        artistRegex.cap();
//        qDebug() << title << artist << titleRegex << artistRegex;
        if ((!titleRegex.cap().isEmpty()) || (!artistRegex.cap().isEmpty())) {
//            qDebug() << "yes";
            toolBox->addItem(popped.at(i), popped.at(i)->getIcon(), popped.at(i)->getTitleString());
            pushed.append(popped.at(i));
            popped.removeAt(i);
        }
    }
}

void MusicLibrary::revealAll() {
    for (int i=popped.length()-1; i>=0; i--) {
        toolBox->addItem(popped.at(i), popped.at(i)->getIcon(), popped.at(i)->getTitleString());
        pushed.append(popped.at(i));
        popped.removeAt(i);
    }
}

void MusicLibrary::pushEntry(AlbumEntry *entry) {
    pushed.append(entry);
}

void MusicLibrary::popEntry(AlbumEntry *entry) {
    popped.append(entry);
}

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
