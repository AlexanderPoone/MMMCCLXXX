#ifndef BULLETSCREEN_H
#define BULLETSCREEN_H

#include <QtWidgets>

class BulletScreen : public QGraphicsObject
{
public:
    BulletScreen();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BULLETSCREEN_H
