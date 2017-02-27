#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H


class nextButton
{
public:
    nextButton();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    QLinearGradient nextGradient;
    QPainterPath nextPath;
};

#endif // NEXTBUTTON_H
