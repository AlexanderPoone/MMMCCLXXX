#include "button.h"
#include "gloweffect.h"

Button::Button()
{
    setAcceptHoverEvents(true);
    baseGradient.setRadius(100);
    baseGradient.setColorAt(1, 0x000001);
    baseGradient.setColorAt(0, 0xffffff);
    basePath.moveTo(2.63*20-60, 6.6*20-60);
    basePath.cubicTo(0.8*20-60, 2.14*20-60, 4.35*20-60, 0.65*20-60, 8.82*20-60, 2.66*20-60);
    basePath.cubicTo(12.54*20-60, 4.32*20-60, 4*20-60, 9.48*20-60, 2.63*20-60, 6.6*20-60);
    basePath.closeSubpath();
    //    nihiloPen.setWidth(0);
    nihiloPen.setColor(Qt::transparent);

    prepareGeometryChange();
    auto effect=new QGraphicsDropShadowEffect();
    this->setGraphicsEffect(effect);
}

//The clickable area of a QGraphicsItem is defined by its boundingRect and shape functions.
QRectF Button::boundingRect() const
{
    return QRectF(-50, -50, 200, 200);
}

QPainterPath Button::shape() const
{
    QPainterPath path;
    path.moveTo(2.63*20-60, 6.6*20-60);
    path.cubicTo(0.8*20-60, 2.14*20-60, 4.35*20-60, 0.65*20-60, 8.82*20-60, 2.66*20-60);
    path.cubicTo(12.54*20-60, 4.32*20-60, 4*20-60, 9.48*20-60, 2.63*20-60, 6.6*20-60);
    return path;
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    //    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    Q_UNUSED(widget);
    QPen pen;
    pen.setColor(Qt::transparent);
    //    pen.setWidth(5);
    painter->setPen(pen);
    QPainterPath path1;
    path1.moveTo(2.63*20-60, 6.6*20-60);
    QRadialGradient gradi;
    gradi.setRadius(100);
    gradi.setColorAt(1, 0x000001);
    gradi.setColorAt(0, 0xffffff);
    painter->setBrush(gradi);
    path1.cubicTo(0.8*20-60, 2.14*20-60, 4.35*20-60, 0.65*20-60, 8.82*20-60, 2.66*20-60);
    path1.cubicTo(12.54*20-60, 4.32*20-60, 4*20-60, 9.48*20-60, 2.63*20-60, 6.6*20-60);
    path1.closeSubpath();
    painter->drawPath(path1);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    auto effect=new QGraphicsDropShadowEffect();
//    effect->setColor(QColor(0xC5, 0xB3, 0x58));
    effect->setColor(QColor(0xFF, 0xBF, 0)); //Amber
    effect->setBlurRadius(40.);
    setGraphicsEffect(effect);
    setCursor(Qt::PointingHandCursor);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setGraphicsEffect(new QGraphicsDropShadowEffect());
//    setGraphicsEffect(NULL);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    qDebug("%f %f",event->pos().x(),event->pos().y());
    update();
}

void Button::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

