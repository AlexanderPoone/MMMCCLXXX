#ifndef VIDEOBUTTON_H
#define VIDEOBUTTON_H

#include "button.h"

class VideoButton : public Button
{
    Q_OBJECT
public:
    VideoButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void onClick();
};

#endif // VIDEOBUTTON_H
