#ifndef VIDEOCENTRALWIDGET_H
#define VIDEOCENTRALWIDGET_H

#include <QVideoWidget>

class VideoCentralWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoCentralWidget(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // VIDEOCENTRALWIDGET_H
