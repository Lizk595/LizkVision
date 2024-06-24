/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
