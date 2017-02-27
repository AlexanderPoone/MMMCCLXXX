#ifndef PREVIOUSBUTON_H
#define PREVIOUSBUTON_H


class previousButon : public Button
{
public:
    previousButon();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    QLinearGradient previousGradient;
    QPainterPath previousPath;
};

#endif // PREVIOUSBUTON_H
