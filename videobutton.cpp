#include "videobutton.h"

VideoButton::VideoButton() {
    Button::Button();
    setToolTip(QString("Launch video player"));
}

void VideoButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    painter->drawPixmap(25,0,60,60,QPixmap(":/filmIcon.png"));
}

void VideoButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    auto effect=new QGraphicsDropShadowEffect();
    effect->setColor(QColor(0xFF, 0xFF, 0x99)); //Canary yellow
    effect->setBlurRadius(40.);
    setGraphicsEffect(effect);
    setCursor(Qt::PointingHandCursor);
}

void VideoButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Video player launched";
    emit onClick();
    update();
}
