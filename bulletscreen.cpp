#include "bulletscreen.h"

BulletScreen::BulletScreen() {

}

QRectF BulletScreen::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

QPainterPath BulletScreen::shape() const
{
    QPainterPath path;
    path.addPolygon(QRectF(0, 0, 600, 600));
    return path;
}

void BulletScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
//QPainterPath phrases;
    QTimer *timer;
    int color[]={Qt::green, Qt::yellow, Qt::lightGray, Qt::white, Qt::cyan, Qt::magenta};
    qsrand(1);
    painter->setPen(Qt::green); //Random color color[qrand()%6]
    painter->drawText(60,60,QString::fromUtf8("いろはにほへと"));
    painter->setPen(Qt::yellow);
    painter->drawText(80,80,QString::fromUtf8("いろはにほへと"));
}

void BulletScreen::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}

void BulletScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

}

void BulletScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}

