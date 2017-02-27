#ifndef PREVIOUSBUTON_H
#define PREVIOUSBUTON_H

#include "button.h"

class PreviousButton : public Button
{
public:
    PreviousButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QLinearGradient previousGradient;
    QPainterPath previousPath;
};

#endif // PREVIOUSBUTON_H
