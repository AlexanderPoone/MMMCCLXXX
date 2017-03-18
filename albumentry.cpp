#include "albumentry.h"

AlbumEntry::AlbumEntry() {
//    setStyleSheet("QToolTip { color: white; background-color: black }");
}

AlbumEntry::AlbumEntry(QWidget *parent) {
//    albumArtL=new QLabel(parent);
//    albumTitleL=new QLabel(parent);
//    artistNameL=new QLabel(parent);
//    albumArtL->setFixedWidth(400);
//    albumArtL->setFixedHeight(400);
//    albumArtL->setScaledContents(true);
//    albumArtL->setStyleSheet(QStringLiteral("border: 10px ridge Violet;"));
//    albumTitleL->setStyleSheet(QStringLiteral("background: transparent; font: 48px \"Futura PT\""));
//    artistNameL->setStyleSheet(QStringLiteral("background: transparent; font: 36px \"Futura PT\""));
//    albumArtL->setAlignment(Qt::AlignHCenter);
//    albumTitleL->setFixedWidth(400);
//    artistNameL->setFixedWidth(400);
//    albumTitleL->setAlignment(Qt::AlignHCenter);
//    artistNameL->setAlignment(Qt::AlignHCenter);
//    addWidget(albumArtL);
//    addWidget(albumTitleL);
//    addWidget(artistNameL);
}

void AlbumEntry::setAlbumArt(QPixmap albumPixmap) {
//    albumArtL->setPixmap(albumPixmap);
    this->albumPixmap=albumPixmap;
}
void AlbumEntry::setAlbumTitle(QString albumTitle) {
//    albumTitleL->setText(albumTitle);
    this->albumTitle=albumTitle;
}

void AlbumEntry::setArtistName(QString artistName) {
//    artistNameL->setText(artistName);
    this->artistName=artistName;
}

void AlbumEntry::setTracks(QJsonArray tracks) {
    //setStylesheet
    QList<QPair<QString, QString>> internal;
    int fixedHeightRef=0;
    for (int i=0; i<tracks.size(); i++) {
        fixedHeightRef+=50;
        internal << qMakePair(tracks[i].toObject().find("songTitle").value().toString(), tracks[i].toObject().find("path").value().toString());
        QListWidgetItem item;
        item.setToolTip(internal[i].second);
        item.setText(QStringLiteral("%1\t%2").arg(i+1).arg(internal[i].first));
        addItem(QStringLiteral("%1\t%2").arg(i+1).arg(internal[i].first));
    }
//    internal << qMakePair(QStringLiteral("Je veux"), QStringLiteral("C:\\Users\\Alexis Poon\\Music\\02.wav"));
//    internal << qMakePair(QStringLiteral("Le long de la route"), QStringLiteral("C:\\Users\\Alexis Poon\\Music\\03.wav"));
    setFixedHeight(fixedHeightRef);
}


void AlbumEntry::setTrackNames(QStringList trackNames) {

}

void AlbumEntry::setTrackPaths(QStringList trackPaths) {

}

void AlbumEntry::setTrackLengths(QStringList trackLengths) {

}

//AlbumEntry::AlbumEntry(QPixmap albumPixmap,
//                       QString albumTitle,
//                       QString artistName,
//                       QStringList trackNames,
//                       QStringList trackPaths,
//                       QStringList trackLengths) {

//}

QIcon AlbumEntry::getIcon() {
    return QIcon(albumPixmap);
}

QString AlbumEntry::getTitleString() {
    return QString("%1 - %2").arg(artistName).arg(albumTitle);
}
