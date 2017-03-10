#include "albumentry.h"

AlbumEntry::AlbumEntry() {

}

AlbumEntry::AlbumEntry(QWidget *parent) {
    albumArtL=new QLabel(parent);
    albumTitleL=new QLabel(parent);
    artistNameL=new QLabel(parent);
    albumArtL->setFixedWidth(400);
    albumArtL->setFixedHeight(400);
    albumArtL->setScaledContents(true);
    albumArtL->setStyleSheet(QStringLiteral("border: 10px ridge Violet;"));
    albumTitleL->setStyleSheet(QStringLiteral("background: transparent; font: 48px \"Futura PT\""));
    artistNameL->setStyleSheet(QStringLiteral("background: transparent; font: 36px \"Futura PT\""));
    albumArtL->setAlignment(Qt::AlignHCenter);
    albumTitleL->setFixedWidth(400);
    artistNameL->setFixedWidth(400);
    albumTitleL->setAlignment(Qt::AlignHCenter);
    artistNameL->setAlignment(Qt::AlignHCenter);
    addWidget(albumArtL);
    addWidget(albumTitleL);
    addWidget(artistNameL);
}

void AlbumEntry::setAlbumArt(QPixmap albumPixmap) {
    albumArtL->setPixmap(albumPixmap);
}
void AlbumEntry::setAlbumTitle(QString albumTitle) {
    albumTitleL->setText(albumTitle);
}

void AlbumEntry::setArtistName(QString artistName) {
    artistNameL->setText(artistName);
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
