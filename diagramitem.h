#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QVariantList>
#include "arrow.h"
QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

//! [0]
class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    enum DiagramType { Step, Conditional, StartEnd, Io };

    DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const { return myDiagramType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const override { return Type; }


    //id of the item
    int id=-1;                      //item的id,-1表示为该处理框未编辑
    //the item with the id of algt
    int algtId=-1;
    //0:idInt
    //1:ID of algt
    //2:Text of algt
    //3-:paras about algt
    QList<QString> outputImgName;
    QList<QString> InputImgName;
    QVariantList adjustableParaList;
    //Text which displays in item
    QString text;
    //Textitem which displays in item
    QGraphicsTextItem* textDisp;
    //the offset of position of text which displays in item
    QPointF textDispPosOffset=QPointF(0,0);
    //the position of text which displays in item
    QPointF textPos;


protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////右击流程图的item触发的事件函数
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:
    //void itemEdit();
private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    //QMenu *myContextMenu;
    QList<Arrow *> arrows;
public slots:
    void updateText(QVariantList Paras);
    // QGraphicsItem interface

};
//! [0]

#endif // DIAGRAMITEM_H
