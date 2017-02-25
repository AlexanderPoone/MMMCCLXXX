#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "geniusmanager.h"
#include "playpausebutton.h"
#include "ratingbar.h"
#include "stopbutton.h"
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    ui->seekTag->setText("No!");
    ui->playPauseView->setStyleSheet("background: transparent; border-style: none;");
    ui->seekSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/noteSlider.png); "
                "padding: -30px -10px 0px -10px;}");
    ui->volumeSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/phonographSlider.png); "
                "padding: -30px -25px 0px -25px;}");
    playPauseScene=new QGraphicsScene(this);
    stopScene=new QGraphicsScene(this);
    ratingBarScene=new QGraphicsScene(this);

    ui->playPauseView->setScene(playPauseScene);
    ui->backwardView->setScene(stopScene);
    ui->forwardView->setScene(stopScene);
    ui->repeatView->setScene(ratingBarScene);
    ui->playPauseView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->backwardView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->forwardView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->repeatView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QGraphicsItem *playPauseItem = new PlayPauseButton();
    QGraphicsItem *stopItem = new StopButton();
    QGraphicsItem *ratingBarItem = new RatingBar();
    playPauseScene->addItem(playPauseItem);
    stopScene->addItem(stopItem);
    ratingBarScene->addItem(ratingBarItem);

    populateScene();
    useGeniusAPI();
    qDebug() << QStyleFactory::keys();
    setStyle(QStyleFactory::create("Fusion")); //remember it's double colon
    on_seekSlider_valueChanged(0);
    on_volumeSlider_valueChanged(0);
    //TODO: Style the groove
}

void MainWindow::useGeniusAPI() {
    auto gManager=new GeniusManager();
}

void MainWindow::on_seekSlider_valueChanged(int value) {
    Q_UNUSED(value);
    ui->seekSlider->setToolTip(QStringLiteral("%1 / 1:00").arg(ui->seekSlider->value()));
}

void MainWindow::on_volumeSlider_valueChanged(int value) {
    Q_UNUSED(value);
    ui->volumeSlider->setToolTip(QStringLiteral("Volume: %1").arg(ui->volumeSlider->value()));
}

bool MainWindow::event(QEvent *event) {
    QMainWindow::event(event);
    if (event->type() == QEvent::WindowActivate) { //QEvent::Enter
        this->setWindowOpacity(1);
    } else if (event->type() == QEvent::WindowDeactivate) { // QEvent::Leave
        this->setWindowOpacity(0.8);
    }
    return true;
}

void MainWindow::populateScene() {
    this->setStyleSheet("background-image: url(:/dark.png);");
}


MainWindow::~MainWindow()
{
    delete ui;
}
