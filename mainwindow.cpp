#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "geniusmanager.h"
#include "previousbutton.h"
#include "playpausebutton.h"
#include "nextbutton.h"
#include "stopbutton.h"
#include "ratingbar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openFile);
    setArtist(QString("Sia"));
    setSongTitle(QString("Chandelier"));
    ui->playPauseView->setStyleSheet("background: transparent; border-style: none;");
    ui->seekSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/noteSlider.png); "
                "padding: -30px -10px 0px -10px;}");
    ui->volumeSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/phonographSlider.png); "
                "padding: -30px -25px 0px -25px;}");
    previousScene=new QGraphicsScene(this);
    playPauseScene=new QGraphicsScene(this);
    nextScene=new QGraphicsScene(this);
    stopScene=new QGraphicsScene(this);

    ratingBarScene=new QGraphicsScene(this);

    ui->backwardView->setScene(previousScene);
    ui->playPauseView->setScene(playPauseScene);
    ui->nextView->setScene(nextScene);
    ui->stopView->setScene(stopScene);
    ui->repeatView->setScene(ratingBarScene);
    ui->playPauseView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->backwardView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->nextView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->stopView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->repeatView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QGraphicsItem *previousItem = new PreviousButton();
    QGraphicsItem *playPauseItem = new PlayPauseButton();
    QGraphicsItem *nextItem = new NextButton();
    QGraphicsItem *stopItem = new StopButton();
    QGraphicsItem *ratingBarItem = new RatingBar();
    previousScene->addItem(previousItem);
    playPauseScene->addItem(playPauseItem);
    nextScene->addItem(nextItem);
    stopScene->addItem(stopItem);
    ratingBarScene->addItem(ratingBarItem);
    populateScene();
    useGeniusAPI();
    qDebug() << QStyleFactory::keys();
    setStyle(QStyleFactory::create("Fusion")); //remember it's double colon
    on_seekSlider_valueChanged(0);
    on_volumeSlider_valueChanged(0);
    //TODO: Style the groove
    setAcceptDrops(true);
}

//void MainWindow::initWav() {
//}

void MainWindow::useGeniusAPI() {
    auto gManager=new GeniusManager(ui->lyricsLabel, artist, songTitle);
}

void MainWindow::setArtist(QString artist) {
    ui->artistTag->setText(artist);
    this->artist=artist;
}

void MainWindow::setSongTitle(QString songTitle) {
    ui->trackNameTag->setText(songTitle);
    this->songTitle=songTitle;
}

void MainWindow::openFile() {
    QString loc=QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Open File", loc, "WAVE files (*.wav *.wave);;MP3 files (*.mp3)");
    if (!fileList.isEmpty()) {
        qDebug() << fileList[0];
    QFileInfo info(fileList[0]);
    songTitle=info.baseName();
    setSongTitle(songTitle);
    setArtist(QString());
    useGeniusAPI();
    }
}

void MainWindow::on_seekSlider_valueChanged(int value) {
    Q_UNUSED(value);
    ui->seekSlider->setToolTip(QStringLiteral("%1 / 1:00").arg(ui->seekSlider->value()));
}

void MainWindow::on_volumeSlider_valueChanged(int value) {
    Q_UNUSED(value);
    ui->volumeSlider->setToolTip(QStringLiteral("Volume: %1").arg(ui->volumeSlider->value()));
    //waveOutSetVolume(HWAVEOUT hwo, DWORD dwVolume);
    //Volume: between 0xFFFF (255 255) and 0x0000, int qRound(2.55*volumeSlider.value()) << 8;
    //Left two bits: left-channel, right two bits: right-channel
}

bool MainWindow::event(QEvent *event) {
    QMainWindow::event(event);
    switch (event->type()) {
    case QEvent::WindowActivate: //QEvent::Enter
        this->setWindowOpacity(1);
        break;
    case QEvent::WindowDeactivate: //QEvent::Leave
        this->setWindowOpacity(0.8);
        break;
    case QEvent::Close:
        qDebug("App closed.");
        HWAVEOUT hAudioOut;
        waveOutClose(hAudioOut);
        break;
    }
    //    if (event->type() == QEvent::WindowActivate) { //QEvent::Enter
    //        this->setWindowOpacity(1);
    //    } else if (event->type() == QEvent::WindowDeactivate) { // QEvent::Leave
    //        this->setWindowOpacity(0.8);
    //    } else if
    return true;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event) {
    qDebug() << event->mimeData()->urls();
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(event->mimeData()->text());
    qDebug() << "Mime type:" << type.name();
}


void MainWindow::populateScene() {
    this->setStyleSheet("background-image: url(:/dark.png);");
}


MainWindow::~MainWindow()
{
    delete ui;
}
