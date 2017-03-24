#ifndef ALBUMENTRY_H
#define ALBUMENTRY_H

#include <QtWidgets>
#include <QDebug>

class AlbumEntry : public QListWidget
//class AlbumEntry : public QVBoxLayout
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
    void setTracks(QJsonArray tracks);
//
    void setTrackNames(QStringList trackNames);
    void setTrackPaths(QStringList trackPaths);
    void setTrackLengths(QStringList trackLengths);
//    void setToolBoxPosition(int pos);

//    int getToolBoxPosition();
    QIcon getIcon();
    QString getTitleString();
    QString getAlbumTitle();
    QString getArtistName();
private:
//    int toolBoxPosition;
    QPixmap albumPixmap;
    QString artistName;
    QString albumTitle;

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
