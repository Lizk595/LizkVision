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
        // case(itemType::label):
        // {
        //     QPoint viewPos = mapFromGlobal(globalPos);
        //     QPointF scenePos = mapToScene(viewPos);
        //     QPointF rectCenterPos = scenePos-QPoint(50,20);
        //     QGraphicsRectItem* rectItem = scene->addRect(rectCenterPos.x(),rectCenterPos.y(), 100, 40, QPen(Qt::black, 4));   //宽100,高40的矩形
        //     vRectItem.emplace_back(rectItem);

        //     rectItem->setBrush(Qt::white); // 设置填充颜色
        //     //m_GraphicsTextItem* textItem = scene->addText(text);
        //     m_GraphicsTextItem* textItem=new m_GraphicsTextItem(text);
        //     scene->addItem(textItem);
        //     vTextItem.emplace_back(textItem);
        //     textItem->setPos(rectCenterPos.x() + (100 - textItem->boundingRect().width()) / 2,
        //                      rectCenterPos.y() + (40 - textItem->boundingRect().height()) / 2); // 居中
        //     return true;
        // }

        case(itemType::arrow):
        {
            return true;
        }

    }
    return false;
}



//鼠标按下
void m_GraphicsView::mousePressEvent(QMouseEvent *event)
{


    // //鼠标位于某个算子框內部
    // if(isInsideRectItem(event->pos())!=-1)
    //     return;


    // //按下ctrl，点击两点，在scene中生成线条
    // if (event->modifiers() & Qt::ControlModifier) {
    //     isCtrlPressed = true;
    //     if (firstPoint.isNull()) {
    //         // 记录第一个点击点
    //         firstPoint = mapToScene(event->pos());
    //     } else {
    //         // 第二个点击点，创建线
    //         QPointF secondPoint = mapToScene(event->pos());
    //         QGraphicsLineItem* line = scene->addLine(QLineF(firstPoint, secondPoint), QPen(Qt::black,4));
    //         vLineItem.emplace_back(line);
    //         firstPoint = QPointF(); // 重置firstPoint以进行下一次连接
    //         isCtrlPressed = false; // 重置Ctrl键状态
    //     }
    //     return;
    // }







}



//鼠标移动
void m_GraphicsView::mouseMoveEvent(QMouseEvent *event)
{


    //test
    // QPoint viewPos = event->pos();
    // QPointF scenePos = mapToScene(viewPos);
    // QString x=QString::number(scenePos.x());
    // QString y=QString::number(scenePos.y());
    // QString text=x+","+y;
    //emit getMousePos("secne内移动"+text);
}


//鼠标松开
void m_GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    //test
    if (event->modifiers() & Qt::ControlModifier) {
        isCtrlPressed = false; // 确保在释放时重置Ctrl键状态

    }
    QGraphicsView::mouseReleaseEvent(event);


    //test
    // QPoint viewPos = event->pos();
    // QPointF scenePos = mapToScene(viewPos);
    // QString x=QString::number(scenePos.x());
    // QString y=QString::number(scenePos.y());
    // QString text=x+","+y;
    //emit getMousePos("scene内松开"+text);
}




//键位按下
void m_GraphicsView::keyPressEvent(QKeyEvent *event)
{
    // //按delete键盘删除流程图中被选中的算子
    // if (event->key() == Qt::Key_Delete)
    //     if(nowSelectTextItem_index!=-1){
    //         delete vTextItem[nowSelectTextItem_index];
    //         vTextItem.erase(vTextItem.begin() + nowSelectTextItem_index);
    //         delete vRectItem[nowSelectTextItem_index];
    //         vRectItem.erase(vRectItem.begin() + nowSelectTextItem_index);
    //         nowSelectTextItem_index=-1;
    //         //test
    //         //emit text("流程图中存在 "+QString::number(vTextItem.size())+"个算子");
    //     }

}



//判断鼠标是否在某个RectItem内,
//若在，则返回该RectItem的index
//否则，返回-1
// int m_GraphicsView::isInsideRectItem(QPoint gvPos)
// {
//     QPointF scenePos = mapToScene(gvPos);
//     for(auto each:vTextItem)
//         each->setDefaultTextColor(Qt::black);
//     for(int i=0;i<vRectItem.size();++i)
//         if (vRectItem[i]->contains(scenePos)){
//             if(i==nowSelectTextItem_index)
//                 return i;
//             vTextItem[i]->setDefaultTextColor(Qt::red);
//             nowSelectTextItem_index=i;
//             return i;
//         }

//     nowSelectTextItem_index=-1; //-1代表在流程图中没有算子被选中
//     return -1;
// }


void m_GraphicsView::createLine(m_GraphicsTextItem *item1, m_GraphicsTextItem *item2) {
    QLineF line(item1->boundingRect().center(), item2->boundingRect().center());
    QGraphicsLineItem *lineItem = scene->addLine(line, QPen(Qt::black));
    // 可能还需要设置 lineItem 的其他属性
}



