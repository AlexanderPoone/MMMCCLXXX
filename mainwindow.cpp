#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "albumentry.h"
#include "musiclibrary.h"
#include "geniusmanager.h"
#include "lrchandler.h"
#include "previousbutton.h"
#include "playpausebutton.h"
#include "nextbutton.h"
#include "stopbutton.h"
#include "ratingbar.h"
#include "bulletscreen.h"
#include "winsockclientthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wavPlay=new WavPlayer;
    ui->thisShouldNotExist->hide();
    ui->localMusicToolbox->removeItem(0);
//    QHBoxLayout *a;
//    a=(QHBoxLayout *)(ui->tab_albumInfo);
//    QChartView *b=new QChartView(this);
//    a->addItem((QLayoutItem *)b);
    createServer();
    secTimer=new QTimer(this);
    lyricsTimer=new QTimer(this);
    auto musicLibrary=new MusicLibrary(ui->localMusicToolbox, this);
    //    setWindowFlags(Qt::FramelessWindowHint);
    connect(musicLibrary, &MusicLibrary::itemClicked, this, &MainWindow::onItemClicked);
    connect(musicLibrary, &MusicLibrary::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openFile);
    createSysTray();
    setArtist(QStringLiteral("ABBA"));
    setSongTitle(QStringLiteral("Chiquitita"));
    //    setArtist(QStringLiteral("The Carpenters"));
    //    setSongTitle(QStringLiteral("Flat Baroque"));
    //    setArtist(QStringLiteral("Séverine"));
    //    setSongTitle(QStringLiteral("Un banc, un arbre, une rue"));
    ui->scrollSpeedDial->setToolTip(QStringLiteral("Auto-scroll speed: 10"));
    previousScene=new QGraphicsScene(this);
    playPauseScene=new QGraphicsScene(this);
    nextScene=new QGraphicsScene(this);
    stopScene=new QGraphicsScene(this);
    ratingBarScene=new QGraphicsScene(this);
    bulletScrScene=new QGraphicsScene(this);
    PreviousButton *previousItem = new PreviousButton();
    PlayPauseButton *playPauseItem = new PlayPauseButton;
    NextButton *nextItem = new NextButton();
    StopButton *stopItem = new StopButton();
    QGraphicsItem *ratingBarItem = new RatingBar();
    QGraphicsItem *bulletScrItem = new BulletScreen();
    bindToView(ui->backwardView, previousScene, previousItem);
    bindToView(ui->playPauseView, playPauseScene, playPauseItem);
    bindToView(ui->nextView, nextScene, nextItem);
    bindToView(ui->stopView, stopScene, stopItem);
    bindToView(ui->repeatView, ratingBarScene, ratingBarItem);
    bindToView(ui->bulletScreenView, bulletScrScene, bulletScrItem);
    connect(playPauseItem, &PlayPauseButton::playActivated, this, &MainWindow::startSecTimer);
    connect(playPauseItem, &PlayPauseButton::playDeactivated, this, &MainWindow::stopSecTimer);
    connect(stopItem, &StopButton::stopSignal, this, &MainWindow::stopSlot);
    connect(previousItem, &PreviousButton::prevSignal, this, &MainWindow::stopSlot);
    connect(nextItem, &NextButton::nextSignal, this, &MainWindow::stopSlot);
    connect(stopItem, &StopButton::stopSignal, playPauseItem, &PlayPauseButton::resetSlot);
    connect(previousItem, &PreviousButton::prevSignal, playPauseItem, &PlayPauseButton::resetSlot);
    connect(nextItem, &NextButton::nextSignal, playPauseItem, &PlayPauseButton::resetSlot);
    connect(secTimer, &QTimer::timeout, this, &MainWindow::moveSeekBar);
    connect(lyricsTimer, &QTimer::timeout, this, &MainWindow::scrollScroller);
    connect(ui->scrollSpeedDial,&QDial::valueChanged,this,&MainWindow::setScrollSpeed);
    connect(ui->searchBox,&QLineEdit::textChanged, musicLibrary, &MusicLibrary::search);
    useGeniusAPI();
    on_seekSlider_valueChanged(0);
    on_volumeSlider_valueChanged(0);
    //Style the groove?
    setAcceptDrops(true);
}

void MainWindow::createServer() {
    server=new WinSockServerThread;
    connect(server, &WinSockServerThread::connected, this, &MainWindow::createClients);
    server->setNextLabelPointer(ui->label);
    server->init();
}

void MainWindow::createClients(const QString &ip, const QString &port) {
    ui->listening->setText(QStringLiteral("The server is running on IP: %1, port %2. Run the client now.").arg(ip).arg(port));
    // Don't use for-loops here
    QString tmp;
    QFile exampleJSON(QStringLiteral("C:\\Users\\Alexandre Poon\\Documents\\sans_titre\\example.json"));
    if (exampleJSON.open(QIODevice::ReadOnly | QIODevice::Text)) {
        tmp=exampleJSON.readAll();
    }
    WinSockClientThread *client_1=new WinSockClientThread(1);
    client_1->init();
    client_1->setMessage(QString::fromUtf8("測試進行中……"));
    client_1->start();
    WinSockClientThread *client_2=new WinSockClientThread(2);
    client_2->init();
    client_2->setMessage(QString::fromUtf8("abcdef"));
    client_2->start();
    WinSockClientThread *client_3=new WinSockClientThread(3);
    client_3->init();
    client_3->setMessage(QString::fromUtf8("!@#$%"));
    client_3->start();
    server->start();
    server->start();
    server->start();
    // Assemble from tidbits when all threads are ready, using signals & slots
//    connect(client_1, );
//    connect(client_2, );
//    connect(client_3, );
}


void MainWindow::initWavFile(QString fileLocation) {
//    hmmioIn=new HMMIO();
}

void MainWindow::useGeniusAPI() {
    auto gManager=new GeniusManager(ui->lyricsLabel, ui->metadataAlbumArtLabel, ui->metadataArtistPhotoLabel, artist, songTitle);
}

void MainWindow::setArtist(QString artist) {
    if (artist.compare("The Carpenters")==0) artist="Carpenters";
    ui->artistTag->setText(artist);
    ui->metadataArtistLabel->setText(artist);
    this->artist=artist;
}

void MainWindow::setSongTitle(QString songTitle) {
    ui->trackNameTag->setText(songTitle);
    ui->metadataSongTitleLabel->setText(songTitle);
    this->songTitle=songTitle;
}

void MainWindow::on_lrcButton_clicked() {
    QString loc=QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QString path = QFileDialog::getOpenFileName(this, "Open LRC lyrics", loc, "LRC lyrics (*.lrc)");
    if (!path.isEmpty()) {
        LRCHandler handler(path, ui->lyricsLabel);
    }
    //error handling
}


void MainWindow::openFile() {
    QString loc=QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Open File", loc, "WAVE files (*.wav *.wave);;MP3 files (*.mp3)");
    if (!fileList.isEmpty()) {
        ui->seekSlider->setMaximum(90); //Just placeholder code. To be changed
        ui->seekSlider->setValue(0);
        qDebug() << fileList[0];
        QFileInfo info(fileList[0]);
        songTitle=info.baseName(); //Just placeholder code. To be deleted
        setSongTitle(songTitle);
        setArtist(QString());
        useGeniusAPI(); //Just placeholder code. To be deleted
    }
}

void MainWindow::createSysTray() {
    sysTray=new QSystemTrayIcon(this);
    QMenu *contextMenu;
    contextMenu=new QMenu(QString("3280MP"),this);
    contextMenu->addAction(QString("3280MP v.0")); //addSection does not work!
    contextMenu->addSeparator();
    QAction *mehAction;
    mehAction=new QAction(QString("Meh!"), this);
    mehAction->setDisabled(true);
    contextMenu->addAction(mehAction);
    QAction *quitAction;
    quitAction=new QAction(QString("&Quit"), this);
    QFont font=quitAction->font();
    font.setBold(true);
    quitAction->setFont(font);
    contextMenu->addAction(quitAction);
    sysTray->setIcon(QIcon(":/jukebox.png"));
    sysTray->setToolTip(QString("3280 Music Player"));
    sysTray->setContextMenu(contextMenu);
    sysTray->show();
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitSlot);
    connect(sysTray, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);
}

void MainWindow::quitSlot() {
    sysTray->hide();
    exit(0);
}

void MainWindow::startSecTimer() { //play
    wavPlay->start();
    secTimer->start(1000);
    lyricsTimer->start(1000-speed*10); //1100-speed*10
    setWindowTitle(windowTitle()+" 🔊");
}

void MainWindow::stopSecTimer() { //pause
    secTimer->stop();
    lyricsTimer->stop();
    setWindowTitle(QStringLiteral("GUI Experiment"));
}

void MainWindow::moveSeekBar() {
    ui->seekSlider->setValue(ui->seekSlider->value()+1);
}

void MainWindow::stopSlot() {
    wavPlay->exit();
    secTimer->stop();
    lyricsTimer->stop();
    setWindowTitle(QStringLiteral("GUI Experiment"));
    ui->seekSlider->setValue(0);
    ui->lyricsScrollArea->verticalScrollBar()->setValue(0);
}

void MainWindow::scrollScroller() {
    ui->lyricsScrollArea->verticalScrollBar()->setValue(ui->lyricsScrollArea->verticalScrollBar()->value()+speed);
}

void MainWindow::setScrollSpeed() {
    speed=ui->scrollSpeedDial->value();
    ui->scrollSpeedDial->setToolTip(QStringLiteral("Auto-scroll speed: %1").arg(speed));
    if (lyricsTimer->isActive()) {
        lyricsTimer->stop();
        lyricsTimer->start(1000-speed*10);
    }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason==QSystemTrayIcon::DoubleClick) {
        this->show();
        setWindowState(Qt::WindowActive);
        //        this->raise();
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

//void MainWindow::on_scrollSpeedDial_valueChanged(int value) {
//    ui->scrollSpeedDial->setToolTip(QStringLiteral("Scroll speed: %1").arg(value));
//}

void MainWindow::on_sendButton_clicked() {
    ui->bulletMessageBox->clear();
}

void MainWindow::onItemClicked(QListWidgetItem *item) {
    QString title=item->text();
    title.remove(QRegExp(".*\\t"));
    if (title.length()>15) {
        title.truncate(15);
        title.append("...");
    }
    ui->trackNameTag->setText(title);
    ui->artistTag->setText(item->toolTip());
    qDebug() << "Clicked!" << title;
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item) {
    QString title=item->text();
    title.remove(QRegExp(".*\\t"));
    qDebug() << "Double clicked!" << title;
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
        sysTray->hide();
        qDebug() << "App closed.";
        //        mmioClose(*hmmioIn, NULL);
        //        waveOutClose((HWAVEOUT) *hAudioOut);
        break;
    case QEvent::WindowStateChange:
        if (isMinimized()) {
            QMessageBox reply;
            //            reply.setObjectName(QString("asdf"));
            //            reply.setStyleSheet(QString("background-image:\"\";"));
            //            reply.setStyle(NULL);
            reply.information(this, QString("3280 Music Player"), QString("The music player will keep running in the system tray. To "
                                                                          "terminate the program, choose <b>Quit</b> in the "
                                                                          "context menu of the system tray entry."));
            this->hide();
            //            event->ignore();

            //                    reply.show();
            //        reply=QMessageBox::information(this, QString("3280 Music Player"),
            //                                         QString("The program will keep running in the system tray. To "
            //                                                 "terminate the program, choose <b>Quit</b> in the "
            //                                                 "context menu of the system tray entry."));
            //        QMessageBox.information(this, "Systray", "asdf").show();
            //        QMessageBox.information(this, "Systray",
            //                "The program will keep running in the system tray. To "
            //                "terminate the program, choose <b>Quit</b> in the "
            //                "context menu of the system tray entry.");
            break;
        }
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


void MainWindow::bindToView(QGraphicsView *view, QGraphicsScene *scene, QGraphicsItem *item) {
    scene->addItem(item);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setScene(scene);
}


MainWindow::~MainWindow()
{
    delete ui;
}
