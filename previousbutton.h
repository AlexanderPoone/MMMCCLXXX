#ifndef PREVIOUSBUTON_H
#define PREVIOUSBUTON_H

#include "button.h"

class PreviousButton : public Button
{
    Q_OBJECT
public:
    PreviousButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QLinearGradient previousGradient;
    QPainterPath previousPath;
signals:
    void prevSignal();
};

#endif // PREVIOUSBUTON_H
