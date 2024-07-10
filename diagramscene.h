#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "m_itemmanager.h"
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE




class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem,InsertLine, InsertText, MoveItem , Step, Conditional, StartEnd, Io };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);
    //QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor &color);
    //void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    //void setFont(const QFont &font);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void updateTextPos(DiagramItem* editingItem,QVariantList Paras);
    //void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted(DiagramItem *item);
    //void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    //鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    DiagramItem::DiagramType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    //bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    //QFont myFont;
    //DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

    // QGraphicsScene interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void OperatorShow(DiagramItem *);
    void isEditing(DiagramItem *sItem);
    void recover(DiagramItem* item);
};


#endif // DIAGRAMSCENE_H
