#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include "button.h"

class StopButton : public Button
{
    Q_OBJECT
public:
    StopButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QLinearGradient stopGradient;
    QPainterPath stopPath;
signals:
    void stopSignal();
};

#endif // STOPBUTTON_H
