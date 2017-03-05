#ifndef ALBUMENTRY_H
#define ALBUMENTRY_H

#include <QtWidgets>

class AlbumEntry : public QVBoxLayout
{
public:
    AlbumEntry();
    AlbumEntry(QWidget *parent);
//    AlbumEntry(QPixmap albumPixmap,
//               QString albumTitle,
//               QString artistName,
//               QStringList trackNames,
//               QStringList trackPaths,
//               QStringList trackLengths);
    void setAlbumArt(QPixmap albumPixmap);
    void setAlbumTitle(QString albumTitle);
    void setArtistName(QString artistName);
    void setTrackNames(QStringList trackNames);
    void setTrackPaths(QStringList trackPaths);
    void setTrackLengths(QStringList trackLengths);
private:
    QLabel *albumArtL;
    QLabel *albumTitleL;
    QLabel *artistNameL;
    QStringList *trackNames;
    QStringList *trackPaths;
    QStringList *trackLengths;
signals:

public slots:
};

#endif // ALBUMENTRY_H
