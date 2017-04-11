//Rewrite from QMW example

#include "videogiantwidget.h"

#include "videoplayercontrols.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QMediaMetaData>
#include <QtWidgets>

VideoGiantWidget::VideoGiantWidget(QWidget *parent)
    : QWidget(parent)
    , videoWidget(0)
    , coverLabel(0)
    , slider(0)
    , colorDialog(0)
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);

    connect(player, &QMediaPlayer::durationChanged, this, &VideoGiantWidget::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &VideoGiantWidget::positionChanged);
    connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &VideoGiantWidget::playlistPositionChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &VideoGiantWidget::statusChanged);
    connect(player, &QMediaPlayer::bufferStatusChanged, this, &VideoGiantWidget::bufferingProgress);
    connect(player, &QMediaPlayer::videoAvailableChanged, this, &VideoGiantWidget::videoAvailableChanged);
    connect(player, SIGNAL(error(QMediaPlayer::Error)), SLOT(displayErrorMessage()));

    videoWidget = new VideoCentralWidget(this);
    player->setVideoOutput(videoWidget);

    playlistModel = new PlaylistModel(this);
    playlistModel->setPlaylist(playlist);

    playlistView = new QListView(this);
    playlistView->setModel(playlistModel);
    playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));

    connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, player->duration() / 1000);

    labelDuration = new QLabel(this);
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    QPushButton *openButton = new QPushButton("Open", this);

    connect(openButton, SIGNAL(clicked()), SLOT(open()));

    VideoPlayerControls *controls = new VideoPlayerControls(this);
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());

    connect(controls, &VideoPlayerControls::play, player, &QMediaPlayer::play);
    connect(controls, &VideoPlayerControls::pause, player, &QMediaPlayer::pause);
    connect(controls, &VideoPlayerControls::stop, player, &QMediaPlayer::stop);
    connect(controls, &VideoPlayerControls::next, playlist, &QMediaPlaylist::next);
    connect(controls, &VideoPlayerControls::previous, this, &VideoGiantWidget::previousClicked);
    connect(controls, &VideoPlayerControls::changeVolume, player, &QMediaPlayer::setVolume);
    connect(controls, &VideoPlayerControls::changeMuting, player, &QMediaPlayer::setMuted);
    connect(controls, &VideoPlayerControls::changeRate, player, &QMediaPlayer::setPlaybackRate);

    connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));

    connect(player, &QMediaPlayer::stateChanged, controls, &VideoPlayerControls::setState);
    connect(player, &QMediaPlayer::volumeChanged, controls, &VideoPlayerControls::setVolume);
    connect(player, &QMediaPlayer::mutedChanged, controls, &VideoPlayerControls::setMuted);

    fullScreenButton = new QPushButton("Full screen", this);
    fullScreenButton->setCheckable(true);

    colorButton = new QPushButton("Color Options...", this);
    colorButton->setEnabled(false);
    connect(colorButton, &QPushButton::clicked, this, &VideoGiantWidget::showColorDialog);

    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(videoWidget, 2);
    displayLayout->addWidget(playlistView);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
    controlLayout->addWidget(fullScreenButton);
    controlLayout->addWidget(colorButton);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(displayLayout);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);
    hLayout->addWidget(labelDuration);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);

    setLayout(layout);

    if (!isPlayerAvailable()) {
        QMessageBox::warning(this, "Service not available",
                             "The QMediaPlayer object does not have a valid service.\n"\
                                "Please check the media service plugins are installed.");

        controls->setEnabled(false);
        playlistView->setEnabled(false);
        openButton->setEnabled(false);
        colorButton->setEnabled(false);
        fullScreenButton->setEnabled(false);
    }

    metaDataChanged();
}

VideoGiantWidget::~VideoGiantWidget()
{
}

bool VideoGiantWidget::isPlayerAvailable() const
{
    return player->isAvailable();
}

void VideoGiantWidget::open()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle("Open Files");
    QStringList supportedMimeTypes = player->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls());
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void VideoGiantWidget::addToPlaylist(const QList<QUrl> urls)
{
    foreach (const QUrl &url, urls) {
        if (isPlaylist(url))
            playlist->load(url);
        else
            playlist->addMedia(url);
    }
}

void VideoGiantWidget::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    slider->setMaximum(duration / 1000);
}

void VideoGiantWidget::positionChanged(qint64 progress)
{
    if (!slider->isSliderDown()) {
        slider->setValue(progress / 1000);
    }
    updateDurationInfo(progress / 1000);
}

void VideoGiantWidget::metaDataChanged()
{
    if (player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2")
                     .arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
                     .arg(player->metaData(QMediaMetaData::Title).toString()));

        if (coverLabel) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            coverLabel->setPixmap(!url.isEmpty()
                                  ? QPixmap(url.toString())
                                  : QPixmap());
        }
    }
}

void VideoGiantWidget::previousClicked()
{
    if(player->position() <= 5000)
        playlist->previous();
    else
        player->setPosition(0);
}

void VideoGiantWidget::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        playlist->setCurrentIndex(index.row());
        player->play();
    }
}

void VideoGiantWidget::playlistPositionChanged(int currentItem)
{
    playlistView->setCurrentIndex(playlistModel->index(currentItem, 0));
}

void VideoGiantWidget::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

void VideoGiantWidget::statusChanged(QMediaPlayer::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
        setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia:
        setStatusInfo("Loading...");
        break;
    case QMediaPlayer::StalledMedia:
        setStatusInfo("Media Stalled");
        break;
    case QMediaPlayer::EndOfMedia:
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
        displayErrorMessage();
        break;
    }
}

void VideoGiantWidget::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
            status == QMediaPlayer::BufferingMedia ||
            status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}

void VideoGiantWidget::bufferingProgress(int progress)
{
    setStatusInfo(QStringLiteral("Buffering %4%").arg(progress));
}

void VideoGiantWidget::videoAvailableChanged(bool available)
{
    if (!available) {
        disconnect(fullScreenButton, &QPushButton::clicked,
                   videoWidget, &VideoCentralWidget::setFullScreen);
        disconnect(videoWidget, &VideoCentralWidget::fullScreenChanged,
                   fullScreenButton, &QPushButton::setChecked);
        videoWidget->setFullScreen(false);
    } else {
        connect(fullScreenButton, &QPushButton::clicked,
                videoWidget, &VideoCentralWidget::setFullScreen);
        connect(videoWidget, &VideoCentralWidget::fullScreenChanged,
                fullScreenButton, &QPushButton::setChecked);

        if (fullScreenButton->isChecked())
            videoWidget->setFullScreen(true);
    }
    colorButton->setEnabled(available);
}

void VideoGiantWidget::setTrackInfo(const QString &info)
{
    trackInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void VideoGiantWidget::setStatusInfo(const QString &info)
{
    statusInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void VideoGiantWidget::displayErrorMessage()
{
    setStatusInfo(player->errorString());
}

void VideoGiantWidget::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    labelDuration->setText(tStr);
}

void VideoGiantWidget::showColorDialog()
{
    if (!colorDialog) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(videoWidget->brightness());
        connect(brightnessSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setBrightness(int)));
        connect(videoWidget, SIGNAL(brightnessChanged(int)), brightnessSlider, SLOT(setValue(int)));

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(videoWidget->contrast());
        connect(contrastSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setContrast(int)));
        connect(videoWidget, SIGNAL(contrastChanged(int)), contrastSlider, SLOT(setValue(int)));

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(videoWidget->hue());
        connect(hueSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setHue(int)));
        connect(videoWidget, SIGNAL(hueChanged(int)), hueSlider, SLOT(setValue(int)));

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(videoWidget->saturation());
        connect(saturationSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setSaturation(int)));
        connect(videoWidget, SIGNAL(saturationChanged(int)), saturationSlider, SLOT(setValue(int)));

        QFormLayout *layout = new QFormLayout;
        layout->addRow("Brightness", brightnessSlider);
        layout->addRow("Contrast", contrastSlider);
        layout->addRow("Hue", hueSlider);
        layout->addRow("Saturation", saturationSlider);

        QPushButton *button = new QPushButton("Close");
        layout->addRow(button);

        colorDialog = new QDialog(this);
        colorDialog->setWindowTitle("Color Options");
        colorDialog->setLayout(layout);

        connect(button, SIGNAL(clicked()), colorDialog, SLOT(close()));
    }
    colorDialog->show();
}
