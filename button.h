#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsItem>
#include <QtWidgets>


class Button : public QGraphicsObject
{
public:
    Button();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    QPainterPath basePath;
    QRadialGradient baseGradient;
    QPen nihiloPen;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BUTTON_H
