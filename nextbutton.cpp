#include "nextbutton.h"
#include <QtWidgets>

NextButton::NextButton()
{
    Button::Button();
    setToolTip(QString("Forward"));
    nextGradient.setStart(.0,.0);
    nextGradient.setFinalStop(100.,100);
    nextGradient.setColorAt(0.4, QColor(0xFF,0x79,0,0x9A)); //Safety orange
    nextGradient.setColorAt(0.6, QColor(0xC0,0x40,0,0x9A)); //Mahogany
    nextPath.moveTo(105-1.3*13, 4.*13);
    nextPath.quadTo(105-1.3*13, 5.*13, 105-1.5*13, 5.*13);
    nextPath.lineTo(105-1.8*13, 5.*13);
    nextPath.quadTo(105-2.*13, 5.*13, 105-2.*13, 4.*13);
    nextPath.lineTo(105-2.*13, 1.*13);
    nextPath.quadTo(105-2.*13, 0., 105-1.8*13, 0.);
    nextPath.lineTo(105-1.5*13, 0.);
    nextPath.quadTo(105-1.3*13, 0., 105-1.3*13, 1.*13);
    nextPath.closeSubpath();
    nextPath.moveTo(105-2.5*13, 1.81*13);
    nextPath.quadTo(105-1.848*13, 2.5*13, 105-2.5*13, 3.19*13);
    nextPath.lineTo(105-3.63*13, 4.33*13);
    nextPath.quadTo(105-4.5*13, 5.24*13, 105-4.5*13, 4.04*13);
    nextPath.lineTo(105-4.5*13, .97*13);
    nextPath.quadTo(105-4.5*13, -0.24*13, 105-3.63*13, 0.64*13);
    nextPath.closeSubpath();
    nextPath.moveTo(105-2.5*13-2.5*13, 1.81*13);
    nextPath.quadTo(105-1.848*13-2.5*13, 2.5*13, 105-2.5*13-2.5*13, 3.19*13);
    nextPath.lineTo(105-3.63*13-2.5*13, 4.33*13);
    nextPath.quadTo(105-4.5*13-2.5*13, 5.24*13, 105-4.5*13-2.5*13, 4.04*13);
    nextPath.lineTo(105-4.5*13-2.5*13, .97*13);
    nextPath.quadTo(105-4.5*13-2.5*13, -0.24*13, 105-3.63*13-2.5*13, 0.64*13);
    nextPath.closeSubpath();
}

void NextButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    //    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    Q_UNUSED(widget);
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    painter->setPen(nihiloPen);
    painter->setBrush(nextGradient);
    painter->drawPath(nextPath);
}

void NextButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    auto effect=new QGraphicsDropShadowEffect();
    effect->setColor(QColor(0xFF,0x9F,0)); //Orange peel
    effect->setBlurRadius(40.);
    setGraphicsEffect(effect);
    setCursor(Qt::PointingHandCursor);
}

void NextButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Next function is yet to be implemented!";
    update();
}
