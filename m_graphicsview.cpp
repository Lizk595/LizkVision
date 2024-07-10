#include "m_GraphicsView.h"


//m_GraphicsView初始化
m_GraphicsView::m_GraphicsView(QWidget *parent)
{

    scene=new QGraphicsScene();
    scene->setSceneRect(0, 0, 1000, 2000);
    setScene(scene);
    offsetPos=QPoint(width()/2,height()/2);


}


//向gv中添加item
bool m_GraphicsView::m_Additem(itemType signal, QPoint globalPos,QString text=NULL)
{
    switch(signal)
    {
        case(itemType::arrow):
        {
            return true;
        }

    }
    return false;
}


//鼠标松开
void m_GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    //test
    if (event->modifiers() & Qt::ControlModifier) {
        isCtrlPressed = false; // 确保在释放时重置Ctrl键状态

    }
    QGraphicsView::mouseReleaseEvent(event);

}


void m_GraphicsView::createLine(m_GraphicsTextItem *item1, m_GraphicsTextItem *item2) {
    QLineF line(item1->boundingRect().center(), item2->boundingRect().center());
    QGraphicsLineItem *lineItem = scene->addLine(line, QPen(Qt::black));
    // 可能还需要设置 lineItem 的其他属性
}



