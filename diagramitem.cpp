#include "diagramitem.h"


#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QFont>






//! [0]
DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
                         QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent), myDiagramType(diagramType)
    // , myContextMenu(contextMenu)
{
    QPainterPath path;
    switch (myDiagramType) {
        case StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        case Conditional:
            myPolygon << QPointF(-100, 0) << QPointF(0, 100)
                      << QPointF(100, 0) << QPointF(0, -100)
                      << QPointF(-100, 0);
            break;
        case Step:
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);


    //初始化textDisp
    textDisp=new QGraphicsTextItem;
    QFont font;
    font.setPointSize(20);
    //textDisp->setPlainText("111");
    textDisp->setFont(font);
    QFontMetrics metrics(font);
    QRect rect = metrics.boundingRect(textDisp->toPlainText());
    int fontWidth = rect.width();
    int fontHeight = rect.height();
    textDispPosOffset=QPointF(-fontWidth/2,-fontHeight/2);


}
//! [0]

//! [1]
void DiagramItem::removeArrow(Arrow *arrow)     //删除一个连接
{
    arrows.removeAll(arrow);
}
//! [1]

//! [2]
void DiagramItem::removeArrows()                //删除多个连接
{
    // need a copy here since removeArrow() will
    // modify the arrows container
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}
//! [2]

//! [3]
void DiagramItem::addArrow(Arrow *arrow)        //增加连接
{
    arrows.append(arrow);
}
//! [3]

//! [4]
QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}
//! [4]

//! [5]
////////////////////////////////////////////////////////////////////////////////////////////////////
// void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
// {
//     scene()->clearSelection();
//     setSelected(true);
//     myContextMenu->exec(event->screenPos());
// }
////////////////////////////////////////////////////////////////////////////////////////////////////
//! [5]

//! [6]
QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        QPointF newPos = value.toPointF();
        textDisp->setPos(newPos+textDispPosOffset);
        textPos=newPos+textDispPosOffset;
        for (Arrow *arrow : qAsConst(arrows))
            arrow->updatePosition();
    }


    return value;
}




void DiagramItem::updateText(QVariantList Paras)
{
    QString text=QString::number(Paras[0].toInt())+Paras[2].toString();
    textDisp->setPlainText(text);
    QFont font=textDisp->font();
    QFontMetrics metrics(font);
    QRect rect = metrics.boundingRect(text);
    int fontWidth = rect.width();
    int fontHeight = rect.height();
    QPointF old_textDispPosOffset=textDispPosOffset;
    textDispPosOffset=QPointF(-fontWidth/2,-fontHeight/2);
    textPos = textPos - old_textDispPosOffset + textDispPosOffset;
    textDisp->setPos(textPos);

}

//! [6]
