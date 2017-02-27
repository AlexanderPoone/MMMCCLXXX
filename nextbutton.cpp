#include "nextbutton.h"
#include <QtWidgets>

NextButton::NextButton()
{

}

void NextButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    //    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    Q_UNUSED(widget);
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    painter->setPen(nihiloPen);
}
