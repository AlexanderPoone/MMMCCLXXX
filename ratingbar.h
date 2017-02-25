#ifndef RATINGBAR_H
#define RATINGBAR_H

#include <QGraphicsItem>
#include <QtWidgets>

class RatingBar : public QGraphicsItem
{
public:
    RatingBar();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    QPainterPath halfStarLPath;
    QPainterPath halfStarRPath;
    QPainterPath wholeStarPath;
    QRadialGradient ratingBarGradient;
    QPen siennaPen;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // RATINGBAR_H
