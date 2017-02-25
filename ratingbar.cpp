#include "ratingbar.h"

RatingBar::RatingBar()
{
    setAcceptHoverEvents(true);
    ratingBarPath.moveTo(1.56*9-55, 2.88*9+25);
    ratingBarPath.lineTo(.2*9-55,1.85*9+25);
    ratingBarPath.lineTo(1.9*9-55,1.85*9+25);
    ratingBarPath.lineTo(2.5*9-55,.2*9+25);
    ratingBarPath.lineTo(3.1*9-55,1.85*9+25);
    ratingBarPath.lineTo(4.8*9-55,1.85*9+25);
    ratingBarPath.lineTo(3.44*9-55,2.88*9+25);
    ratingBarPath.lineTo(3.92*9-55,4.52*9+25);
    ratingBarPath.lineTo(2.5*9-55,3.54*9+25);
    ratingBarPath.lineTo(1.12*9-55,4.52*9+25);
    ratingBarPath.closeSubpath();
    ratingBarPath.moveTo(1.56*9-10, 2.88*9+25);
    ratingBarPath.lineTo(.2*9-10,1.85*9+25);
    ratingBarPath.lineTo(1.9*9-10,1.85*9+25);
    ratingBarPath.lineTo(2.5*9-10,.2*9+25);
    ratingBarPath.lineTo(3.1*9-10,1.85*9+25);
    ratingBarPath.lineTo(4.8*9-10,1.85*9+25);
    ratingBarPath.lineTo(3.44*9-10,2.88*9+25);
    ratingBarPath.lineTo(3.92*9-10,4.52*9+25);
    ratingBarPath.lineTo(2.5*9-10,3.54*9+25);
    ratingBarPath.lineTo(1.12*9-10,4.52*9+25);
    ratingBarPath.closeSubpath();
    ratingBarPath.moveTo(1.56*9+35, 2.88*9+25);
    ratingBarPath.lineTo(.2*9+35,1.85*9+25);
    ratingBarPath.lineTo(1.9*9+35,1.85*9+25);
    ratingBarPath.lineTo(2.5*9+35,.2*9+25);
    ratingBarPath.lineTo(3.1*9+35,1.85*9+25);
    ratingBarPath.lineTo(4.8*9+35,1.85*9+25);
    ratingBarPath.lineTo(3.44*9+35,2.88*9+25);
    ratingBarPath.lineTo(3.92*9+35,4.52*9+25);
    ratingBarPath.lineTo(2.5*9+35,3.54*9+25);
    ratingBarPath.lineTo(1.12*9+35,4.52*9+25);
    ratingBarPath.closeSubpath();
    ratingBarPath.moveTo(1.56*9+80, 2.88*9+25);
    ratingBarPath.lineTo(.2*9+80,1.85*9+25);
    ratingBarPath.lineTo(1.9*9+80,1.85*9+25);
    ratingBarPath.lineTo(2.5*9+80,.2*9+25);
    ratingBarPath.lineTo(3.1*9+80,1.85*9+25);
    ratingBarPath.lineTo(4.8*9+80,1.85*9+25);
    ratingBarPath.lineTo(3.44*9+80,2.88*9+25);
    ratingBarPath.lineTo(3.92*9+80,4.52*9+25);
    ratingBarPath.lineTo(2.5*9+80,3.54*9+25);
    ratingBarPath.lineTo(1.12*9+80,4.52*9+25);
    ratingBarPath.closeSubpath();
    ratingBarPath.moveTo(1.56*9+125, 2.88*9+25);
    ratingBarPath.lineTo(.2*9+125,1.85*9+25);
    ratingBarPath.lineTo(1.9*9+125,1.85*9+25);
    ratingBarPath.lineTo(2.5*9+125,.2*9+25);
    ratingBarPath.lineTo(3.1*9+125,1.85*9+25);
    ratingBarPath.lineTo(4.8*9+125,1.85*9+25);
    ratingBarPath.lineTo(3.44*9+125,2.88*9+25);
    ratingBarPath.lineTo(3.92*9+125,4.52*9+25);
    ratingBarPath.lineTo(2.5*9+125,3.54*9+25);
    ratingBarPath.lineTo(1.12*9+125,4.52*9+25);
    ratingBarPath.closeSubpath();

}

QRectF RatingBar::boundingRect() const
{
    return QRectF(-50, -50, 300, 300);
}

QPainterPath RatingBar::shape() const
{
    QPainterPath path;
    path.addRect(-50, -50, 300, 300);
    return path;
}

void RatingBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    painter->setBrush(Qt::yellow);
    painter->setPen(siennaPen);
    painter->drawPath(ratingBarPath);
}

void RatingBar::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

}

void RatingBar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {

}

void RatingBar::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}

void RatingBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}
