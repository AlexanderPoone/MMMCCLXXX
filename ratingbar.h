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
    QPainterPath backPath, halfStarLPath, halfStarRPath, wholeStarPath;
    QRadialGradient ratingBarGradient;
    QPen siennaPen;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    bool isHover;
    qreal hoverRating;
    qreal rating;
};

#endif // RATINGBAR_H
