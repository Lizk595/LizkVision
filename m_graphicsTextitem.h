#ifndef M_GRAPHICSTEXTITEM_H
#define M_GRAPHICSTEXTITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QEvent>

class m_GraphicsTextItem : public QGraphicsTextItem
{

public:
    using QGraphicsTextItem::QGraphicsTextItem;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void nowSelected(int& index);
};

#endif // M_GRAPHICSTEXTITEM_H
