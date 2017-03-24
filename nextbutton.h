#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H

#include "button.h"

class NextButton : public Button
{
    Q_OBJECT
public:
    NextButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QLinearGradient nextGradient;
    QPainterPath nextPath;
signals:
    void nextSignal();
};

#endif // NEXTBUTTON_H
