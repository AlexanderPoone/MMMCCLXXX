#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include "button.h"

class StopButton : public Button
{
public:
    StopButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QLinearGradient stopGradient;
    QPainterPath stopPath;
};

#endif // STOPBUTTON_H
