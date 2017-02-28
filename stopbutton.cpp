#include "stopbutton.h"
#include <QtWidgets>

StopButton::StopButton() {
    Button::Button();
    setToolTip(QString("Stop playback"));
    stopGradient.setStart(.0,.0);
    stopGradient.setFinalStop(100.,100);
    stopGradient.setColorAt(0.4, QColor(0xFF,0x08,0,0x9A)); //Candy apple red
    stopGradient.setColorAt(0.6, QColor(0x80,0,0x20,0x9A)); //Oxblood
    stopPath.moveTo(2*11+4, 4*11+2);
    stopPath.quadTo(2*11+4, 5*11+2, 3*11+4, 5*11+2);
    stopPath.lineTo(6*11+4, 5*11+2);
    stopPath.quadTo(7*11+4, 5*11+2, 7*11+4, 4*11+2);
    stopPath.lineTo(7*11+4, 1*11+2);
    stopPath.quadTo(7*11+4, 0+2, 6*11+4, 0+2);
    stopPath.lineTo(3*11+4, 0+2);
    stopPath.quadTo(2*11+4, 0+2, 2*11+4, 1*11+2);
    stopPath.closeSubpath();

}

void StopButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    painter->setBrush(stopGradient);
    painter->drawPath(stopPath);
}

void StopButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    auto effect=new QGraphicsDropShadowEffect();
    effect->setColor(QColor(0xC8, 0x1D, 0x11)); //Persian red
    effect->setBlurRadius(40.);
    setGraphicsEffect(effect);
    setCursor(Qt::PointingHandCursor);
}

void StopButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Stop function is yet to be implemented!";
    update();
}
