#include "m_graphicsTextitem.h"




//单击
void m_GraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setDefaultTextColor(Qt::red);
    //emit nowSelected();
}


//移动
void m_GraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}


//松开
void m_GraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}


//双击
void m_GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
