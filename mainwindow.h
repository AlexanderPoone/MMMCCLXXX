#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_seekSlider_valueChanged(int value);
    void on_volumeSlider_valueChanged(int value);

private:
    void changeTooltip();
    bool event(QEvent *event) override;
    void populateScene();
    Ui::MainWindow *ui;
    QGraphicsScene *playPauseScene;
    QGraphicsScene *stopScene;
    QGraphicsScene *ratingBarScene;
};

#endif // MAINWINDOW_H
