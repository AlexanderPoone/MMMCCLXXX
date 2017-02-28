#ifndef PLAYPAUSEBUTTON_H
#define PLAYPAUSEBUTTON_H

#include "button.h"

class PlayPauseButton : public Button
{
    Q_OBJECT
public:
    PlayPauseButton(QScrollArea *scrollArea);
    bool isPlaying();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
//    void focusInEvent(QKeyEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
protected slots:
    void scrollScroller();

private:
    bool state;
    QLinearGradient playGradient;
    QLinearGradient pauseGradient;
    QPainterPath playPath;
    QPainterPath pausePath;
};

#endif // PLAYPAUSEBUTTON_H
