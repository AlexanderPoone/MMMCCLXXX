#include "ratingbar.h"

RatingBar::RatingBar()
    :rating(0.)
{
    setAcceptHoverEvents(true);
    setToolTip(QStringLiteral("Rate this song"));
    siennaPen.setColor(QColor(0xCB, 0xA1, 0x35)); //Metallic gold
    //    siennaPen.setColor(QColor(0xA0,0x52,0x2D)); //Sienna
    siennaPen.setWidth(2);
    siennaPen.setJoinStyle(Qt::RoundJoin);

    wholeStarPath.moveTo(1.56*9-48, 2.88*9+25);
    wholeStarPath.lineTo(.2*9-48,1.85*9+25);
    wholeStarPath.lineTo(1.9*9-48,1.85*9+25);
    wholeStarPath.lineTo(2.5*9-48,.2*9+25);
    wholeStarPath.lineTo(3.1*9-48,1.85*9+25);
    wholeStarPath.lineTo(4.8*9-48,1.85*9+25);
    wholeStarPath.lineTo(3.44*9-48,2.88*9+25);
    wholeStarPath.lineTo(3.92*9-48,4.52*9+25);
    wholeStarPath.lineTo(2.5*9-48,3.54*9+25);
    wholeStarPath.lineTo(1.12*9-48,4.52*9+25);
    wholeStarPath.closeSubpath();
    QPainterPath tmpPath(wholeStarPath);
    backPath.addPath(tmpPath);
    tmpPath.translate(48.,0);
    backPath.addPath(tmpPath);
    tmpPath.translate(48.,0);
    backPath.addPath(tmpPath);
    tmpPath.translate(48.,0);
    backPath.addPath(tmpPath);
    tmpPath.translate(48.,0);
    backPath.addPath(tmpPath);
    halfStarLPath.moveTo(1.56*9-48, 2.88*9+25);
    halfStarLPath.lineTo(.2*9-48,1.85*9+25);
    halfStarLPath.lineTo(1.9*9-48,1.85*9+25);
    halfStarLPath.lineTo(2.5*9-48,.2*9+25);
    halfStarLPath.lineTo(2.5*9-48,3.54*9+25);
    halfStarLPath.lineTo(1.12*9-48,4.52*9+25);
    halfStarLPath.closeSubpath();
    halfStarRPath.moveTo(2.5*9*2 -1.56*9-48, 2.88*9+25);
    halfStarRPath.lineTo(2.5*9*2 -.2*9-48,1.85*9+25);
    halfStarRPath.lineTo(2.5*9*2 -1.9*9-48,1.85*9+25);
    halfStarRPath.lineTo(2.5*9*2 -2.5*9-48,.2*9+25);
    halfStarRPath.lineTo(2.5*9*2 -2.5*9-48,3.54*9+25);
    halfStarRPath.lineTo(2.5*9*2 -1.12*9-48,4.52*9+25);
    halfStarRPath.closeSubpath();
    //    backPath.moveTo(1.56*9-48, 2.88*9+25);
    //    backPath.lineTo(.2*9-48,1.85*9+25);
    //    backPath.lineTo(1.9*9-48,1.85*9+25);
    //    backPath.lineTo(2.5*9-48,.2*9+25);
    //    backPath.lineTo(3.1*9-48,1.85*9+25);
    //    backPath.lineTo(4.8*9-48,1.85*9+25);
    //    backPath.lineTo(3.44*9-48,2.88*9+25);
    //    backPath.lineTo(3.92*9-48,4.52*9+25);
    //    backPath.lineTo(2.5*9-48,3.54*9+25);
    //    backPath.lineTo(1.12*9-48,4.52*9+25);
    //    backPath.closeSubpath();
    //    backPath.moveTo(1.56*9-3, 2.88*9+25);
    //    backPath.lineTo(.2*9-3,1.85*9+25);
    //    backPath.lineTo(1.9*9-3,1.85*9+25);
    //    backPath.lineTo(2.5*9-3,.2*9+25);
    //    backPath.lineTo(3.1*9-3,1.85*9+25);
    //    backPath.lineTo(4.8*9-3,1.85*9+25);
    //    backPath.lineTo(3.44*9-3,2.88*9+25);
    //    backPath.lineTo(3.92*9-3,4.52*9+25);
    //    backPath.lineTo(2.5*9-3,3.54*9+25);
    //    backPath.lineTo(1.12*9-3,4.52*9+25);
    //    backPath.closeSubpath();
    //    backPath.moveTo(1.56*9+42, 2.88*9+25);
    //    backPath.lineTo(.2*9+42,1.85*9+25);
    //    backPath.lineTo(1.9*9+42,1.85*9+25);
    //    backPath.lineTo(2.5*9+42,.2*9+25);
    //    backPath.lineTo(3.1*9+42,1.85*9+25);
    //    backPath.lineTo(4.8*9+42,1.85*9+25);
    //    backPath.lineTo(3.44*9+42,2.88*9+25);
    //    backPath.lineTo(3.92*9+42,4.52*9+25);
    //    backPath.lineTo(2.5*9+42,3.54*9+25);
    //    backPath.lineTo(1.12*9+42,4.52*9+25);
    //    backPath.closeSubpath();
    //    backPath.moveTo(1.56*9+87, 2.88*9+25);
    //    backPath.lineTo(.2*9+87,1.85*9+25);
    //    backPath.lineTo(1.9*9+87,1.85*9+25);
    //    backPath.lineTo(2.5*9+87,.2*9+25);
    //    backPath.lineTo(3.1*9+87,1.85*9+25);
    //    backPath.lineTo(4.8*9+87,1.85*9+25);
    //    backPath.lineTo(3.44*9+87,2.88*9+25);
    //    backPath.lineTo(3.92*9+87,4.52*9+25);
    //    backPath.lineTo(2.5*9+87,3.54*9+25);
    //    backPath.lineTo(1.12*9+87,4.52*9+25);
    //    backPath.closeSubpath();
    //    backPath.moveTo(1.56*9+132, 2.88*9+25);
    //    backPath.lineTo(.2*9+132,1.85*9+25);
    //    backPath.lineTo(1.9*9+132,1.85*9+25);
    //    backPath.lineTo(2.5*9+132,.2*9+25);
    //    backPath.lineTo(3.1*9+132,1.85*9+25);
    //    backPath.lineTo(4.8*9+132,1.85*9+25);
    //    backPath.lineTo(3.44*9+132,2.88*9+25);
    //    backPath.lineTo(3.92*9+132,4.52*9+25);
    //    backPath.lineTo(2.5*9+132,3.54*9+25);
    //    backPath.lineTo(1.12*9+132,4.52*9+25);
    //    backPath.closeSubpath();
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
    painter->setBrush(Qt::lightGray);
    painter->setPen(siennaPen);
    painter->drawPath(backPath);
    //2 for loops
    QPainterPath tmpHalfPath(halfStarLPath);
    QPainterPath tmpWholePath(wholeStarPath);
    if (isHover) {
        painter->setBrush(Qt::yellow);
        if (hoverRating==.5f) {
            painter->drawPath(tmpHalfPath);
        }
        else if (hoverRating==1.f) {
            painter->drawPath(tmpWholePath);
        }
        else if (hoverRating==1.5f) {
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (hoverRating==2.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (hoverRating==2.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*2,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (hoverRating==3.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (hoverRating==3.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*3,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (hoverRating==4.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (hoverRating==4.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*4,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (hoverRating==5.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
    } else {
        painter->setBrush(QColor(0xFC, 0xC2, 0x00));
        if (rating==.5f) {
            painter->drawPath(tmpHalfPath);
        }
        else if (rating==1.f) {
            painter->drawPath(tmpWholePath);
        }
        else if (rating==1.5f) {
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (rating==2.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (rating==2.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*2,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (rating==3.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (rating==3.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*3,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (rating==4.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
        else if (rating==4.5f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpHalfPath.translate(48.*4,0);
            painter->drawPath(tmpHalfPath);
        }
        else if (rating==5.f) {
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
            tmpWholePath.translate(48.,0);
            painter->drawPath(tmpWholePath);
        }
    }
    //    backPath.translate(48.,0);
    //    painter->drawPath(backPath);
    //    backPath.translate(48.,0);
    //    painter->drawPath(backPath);
    //    backPath.translate(48.,0);
    //    painter->drawPath(backPath);
    //    backPath.translate(48.,0);
    //    painter->drawPath(backPath);
}

void RatingBar::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    //    qreal x, y;
    QPainterPath tmpLPath(halfStarLPath);
    QPainterPath tmpRPath(halfStarRPath);
    isHover=false;
    for (float foo=0.5f; foo<=4.5f; foo++) {
        if (tmpLPath.contains(QPoint(event->pos().x(), event->pos().y()))) {
            hoverRating=foo;
            isHover=true;
        }
        tmpLPath.translate(48., 0);
    }
    for (float foo=1.f; foo<=5.f; foo++) {
        if (tmpRPath.contains(QPoint(event->pos().x(), event->pos().y()))) {
            hoverRating=foo;
            isHover=true;
        }
        tmpRPath.translate(48., 0);
    }
    update(-50,-50,300,300);
    //    qDebug("%f %f", event->pos().x(), event->pos().y());
}

void RatingBar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
}

void RatingBar::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPainterPath tmpLPath(halfStarLPath);
    QPainterPath tmpRPath(halfStarRPath);
    for (float foo=0.5f; foo<=4.5f; foo++) {
        if (tmpLPath.contains(QPoint(event->pos().x(), event->pos().y()))) {
            rating=foo;
        }
        tmpLPath.translate(48., 0);
    }
    for (float foo=1.f; foo<=5.f; foo++) {
        if (tmpRPath.contains(QPoint(event->pos().x(), event->pos().y()))) {
            rating=foo;
        }
        tmpRPath.translate(48., 0);
    }
    setToolTip(QStringLiteral("Rating: %1").arg(rating));
}

void RatingBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
}
