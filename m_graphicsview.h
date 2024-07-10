#ifndef M_GRAPHICSVIEW_H
#define M_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <vector>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "m_graphicsTextitem.h"
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsLineItem>


enum itemType{  label=0,
                arrow=1,


                };

class m_GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    //using QGraphicsView::QGraphicsView;
    m_GraphicsView(QWidget *parent = nullptr);
public:
    QGraphicsScene* scene=nullptr;
    bool m_Additem(itemType signal,QPoint globalPos,QString text);

signals:
    void getMousePos(QString text);     //text
    void text(QString text);            //text

    // QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //int isInsideRectItem(QPoint gvPos);
    void createLine(m_GraphicsTextItem *item1, m_GraphicsTextItem *item2);
private:
    std::vector<QGraphicsRectItem*> vRectItem;
    //std::vector<m_GraphicsTextItem*> vTextItem;
    std::vector<QGraphicsLineItem*> vLineItem;
    QPoint offsetPos;
    int nowSelectTextItem_index=-1;
    QPointF firstPoint;
    bool isCtrlPressed = false;


};

#endif // M_GRAPHICSVIEW_H
