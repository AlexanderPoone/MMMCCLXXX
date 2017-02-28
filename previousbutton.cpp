#include "previousbutton.h"
#include <QtWidgets>

PreviousButton::PreviousButton()
{
    Button::Button();
    setToolTip(QString("Backward"));
    previousGradient.setStart(.0,.0);
    previousGradient.setFinalStop(100.,100);
    previousGradient.setColorAt(0.4, QColor(0xC9,0xA0,0xDC,0x9A)); //Wisteria
    previousGradient.setColorAt(0.6, QColor(0x8E,0x45,0x85,0x9A)); //Crayola plum
    previousPath.moveTo(1.3*13, 4.*13);
    previousPath.quadTo(1.3*13, 5.*13, 1.5*13, 5.*13);
    previousPath.lineTo(1.8*13, 5.*13);
    previousPath.quadTo(2.*13, 5.*13, 2.*13, 4.*13);
    previousPath.lineTo(2.*13, 1.*13);
    previousPath.quadTo(2.*13, 0., 1.8*13, 0.);
    previousPath.lineTo(1.5*13, 0.);
    previousPath.quadTo(1.3*13, 0., 1.3*13, 1.*13);
    previousPath.closeSubpath();
    previousPath.moveTo(2.5*13, 1.81*13);
    previousPath.quadTo(1.848*13, 2.5*13, 2.5*13, 3.19*13);
    previousPath.lineTo(3.63*13, 4.33*13);
    previousPath.quadTo(4.5*13, 5.24*13, 4.5*13, 4.04*13);
    previousPath.lineTo(4.5*13, .97*13);
    previousPath.quadTo(4.5*13, -0.24*13, 3.63*13, 0.64*13);
    previousPath.closeSubpath();
    previousPath.moveTo(2.5*13+2.5*13, 1.81*13);
    previousPath.quadTo(1.848*13+2.5*13, 2.5*13, 2.5*13+2.5*13, 3.19*13);
    previousPath.lineTo(3.63*13+2.5*13, 4.33*13);
    previousPath.quadTo(4.5*13+2.5*13, 5.24*13, 4.5*13+2.5*13, 4.04*13);
    previousPath.lineTo(4.5*13+2.5*13, .97*13);
    previousPath.quadTo(4.5*13+2.5*13, -0.24*13, 3.63*13+2.5*13, 0.64*13);
    previousPath.closeSubpath();
}

void PreviousButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    //    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    Q_UNUSED(widget);
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    painter->setPen(nihiloPen);
    painter->setBrush(previousGradient);
    painter->drawPath(previousPath);
}

void PreviousButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    auto effect=new QGraphicsDropShadowEffect();
    effect->setColor(QColor(0xE6,0xE6,0xFA)); //Lavender
    effect->setBlurRadius(40.);
    setGraphicsEffect(effect);
    setCursor(Qt::PointingHandCursor);
}

void PreviousButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Previous function is yet to be implemented!";
    update();
}
