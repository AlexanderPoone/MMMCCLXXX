#include "playpausebutton.h"
#include <QtWidgets>

QScrollArea *lyricsScroll;

PlayPauseButton::PlayPauseButton(QScrollArea *scrollArea)
    :state(true) {

    Button::Button();
    setToolTip(QString("Play"));
    lyricsScroll=scrollArea;
    playGradient.setStart(.0,.0);
    playGradient.setFinalStop(100.,100);
    playGradient.setColorAt(0.4, QColor(0xFF,0xFF,0,0x9A));
    playGradient.setColorAt(0.6, QColor(0x8D,0xB6,0,0x9A));
    playPath.moveTo(2*13+7, 5.6*13-59);
    playPath.quadTo(2*13+7, 4.06*13-59, 3.28*13+7, 4.88*13-59);
    playPath.lineTo(5.75*13+7, 6.4*13-59);
    playPath.quadTo(6.78*13+7, 7*13-59, 5.75*13+7, 7.59*13-59);
    playPath.lineTo(3.28*13+7, 9.18*13-59);
    playPath.quadTo(2*13+7, 10*13-59, 2*13+7, 8.53*13-59);
    playPath.closeSubpath();

    pauseGradient.setStart(.0,.0);
    pauseGradient.setFinalStop(100.,100.);
    pauseGradient.setColorAt(0.4, QColor(0x7D,0xF9,0xFF,0x9A)); //Electric blue
    pauseGradient.setColorAt(0.6, QColor(0x31,0x8C,0xE7,0x9A)); //Bleu de France
    pausePath.moveTo(2*12-3, 4*12+2);
    pausePath.quadTo(2*12-3, 5*12+2, 2.5*12-3, 5*12+2);
    pausePath.lineTo(3.5*12-3, 5*12+2);
    pausePath.quadTo(4*12-3, 5*12+2, 4*12-3, 4*12+2);
    pausePath.lineTo(4*12-3, 1*12+2);
    pausePath.quadTo(4*12-3, 0+2, 3.5*12-3, 0+2);
    pausePath.lineTo(2.5*12-3, 0+2);
    pausePath.quadTo(2*12-3, 0+2, 2*12-3, 1*12+2);
    pausePath.closeSubpath();
    pausePath.moveTo(2*12+37, 4*12+2);
    pausePath.quadTo(2*12+37, 5*12+2, 2.5*12+37, 5*12+2);
    pausePath.lineTo(3.5*12+37, 5*12+2);
    pausePath.quadTo(4*12+37, 5*12+2, 4*12+37, 4*12+2);
    pausePath.lineTo(4*12+37, 1*12+2);
    pausePath.quadTo(4*12+37, 0+2, 3.5*12+37, 0+2);
    pausePath.lineTo(2.5*12+37, 0+2);
    pausePath.quadTo(2*12+37, 0+2, 2*12+37, 1*12+2);
    pausePath.closeSubpath();

    //linea.setColorAt(0.4,0x00FFFF00); //Alpha at the back. 00=transparent. 7F=midway. Remember to remove this comment.
    //linea.setColorAt(0.6,0x008DB600);
    //    linea.setColorAt(0.4, QColor(0xFF,0xFF,0xFF,0x5F));
    //    linea.setColorAt(0.6, QColor(0xFF,0xFF,0xFF,0x5F));

    //    QLinearGradient linea(.0,.0,100,100);
    //linea.setColorAt(0.4,0x00FFFF00); //Alpha at the back. 00=transparent. 7F=midway. Remember to remove this comment.
    //linea.setColorAt(0.6,0x008DB600);
    //    linea.setColorAt(0.4, QColor(0xFF,0xFF,0xFF,0x5F));
    //    linea.setColorAt(0.6, QColor(0xFF,0xFF,0xFF,0x5F));
    //    QPolygonF polygon;
    //    polygon << QPointF(35, 2) << QPointF(35, 62) << QPointF(85, 32);
    //    path.addPolygon(polygon);


}

bool PlayPauseButton::isPlaying() {
    return state;
}

void PlayPauseButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    //    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(nihiloPen);
    painter->setBrush(baseGradient);
    painter->drawPath(basePath);
    if (state) {
        painter->setPen(nihiloPen);
        painter->setBrush(playGradient);
        painter->drawPath(playPath);
    } else {
        painter->setPen(nihiloPen);
        painter->setBrush(pauseGradient);
        painter->drawPath(pausePath);
    }
}

void PlayPauseButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    if (state) Button::hoverEnterEvent(event);
    else {
        // DANGER: SHOULD BE MEMBER!
        auto effect=new QGraphicsDropShadowEffect();
    //    effect->setColor(QColor(0xC5, 0xB3, 0x58));
        effect->setColor(QColor(0x7D, 0xF9, 0xFF)); //Electric blue
        effect->setBlurRadius(40.);
        setGraphicsEffect(effect);
    }
    setCursor(Qt::PointingHandCursor);
}

void PlayPauseButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Button::hoverLeaveEvent(event);
}

void PlayPauseButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    QTimer *timer;
    timer=new QTimer();
    if (state) {
        state=false;
        auto effect=new QGraphicsDropShadowEffect();
        effect->setColor(QColor(0x7D, 0xF9, 0xFF)); //Electric blue
        effect->setBlurRadius(40.);
        setGraphicsEffect(effect);
        update();
        setToolTip(QString("Pause"));
        QObject::connect(timer,&QTimer::timeout,this,&PlayPauseButton::scrollScroller);
        timer->start(2000);
    }
    else {
        state=true;
        auto effect=new QGraphicsDropShadowEffect();
    //    effect->setColor(QColor(0xC5, 0xB3, 0x58));
        effect->setColor(QColor(0xFF, 0xBF, 0)); //Amber
        effect->setBlurRadius(40.);
        setGraphicsEffect(effect);
        update();
        setToolTip(QString("Play"));
    }
    qDebug("%d", state);
}

void PlayPauseButton::scrollScroller() {
    lyricsScroll->verticalScrollBar()->setValue(lyricsScroll->verticalScrollBar()->value()+100);
}

void PlayPauseButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    update();
}
