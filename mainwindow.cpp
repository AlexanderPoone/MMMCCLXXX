#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playpausebutton.h"
#include "stopbutton.h"
#include "geniusmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    ui->seekTag->setText("Fuck");
    //    ui->seekTag->setText("No");
    playPauseScene=new QGraphicsScene(this);
    stopScene=new QGraphicsScene(this);
    ui->playPauseView->setScene(playPauseScene);
    ui->backwardView->setScene(stopScene);
    ui->forwardView->setScene(stopScene);
    ui->repeatView->setScene(stopScene);
    ui->playPauseView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->backwardView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->forwardView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->repeatView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QGraphicsItem *playPauseItem = new PlayPauseButton();
    QGraphicsItem *stopItem = new StopButton();
    ui->playPauseView->setStyleSheet("background: transparent; border-style: none;");
    playPauseScene->addItem(playPauseItem);
    stopScene->addItem(stopItem);
    ui->horizontalSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/phonographSlider.png); "
                "padding: -30px -25px 0px -25px;}");
    ui->seekSlider->setStyleSheet(
                "QSlider::handle:horizontal { image: url(:/noteSlider.png); "
                "padding: -30px -10px 0px -10px;}");
    populateScene();
    qDebug() << QStyleFactory::keys();
    setStyle(QStyleFactory::create("Fusion")); //remember it's double colon
    //TODO: Style the groove

}
void MainWindow::populateScene() {
    this->setStyleSheet("background-image: url(:/dark.png);");
}

MainWindow::~MainWindow()
{
    delete ui;
}
