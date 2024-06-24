#ifndef M_ITEMMANAGER_H
#define M_ITEMMANAGER_H

#include "diagramitem.h"
#include "imagemanager.h"
#include <QObject>

class m_ItemManager :public QObject
{
    Q_OBJECT
public:
    //  当前正在算子编辑窗口编辑的处理框
    DiagramItem*                                editingItem;

private:
    //  单例模式
    static m_ItemManager*                       instance;

    //  根据处理框序号顺序存储的处理框
    QList<DiagramItem*>                         ItemList;

public:
    ///////////////////////////////////////////////////////////////////////////////////
    /// getItemNum：
    ///         获得现存的处理框的数量
    /// return: (int)现存的处理框的数量
    ///////////////////////////////////////////////////////////////////////////////////
    int getItemNum();

    ///////////////////////////////////////////////////////////////////////////////////
    /// getInstance：
    ///         单例模式，返回该类的对象的指针
    /// return: (m_ItemManager*) m_ItemManager实例
    ///////////////////////////////////////////////////////////////////////////////////
    static m_ItemManager* getInstance() {return instance;}

    ///////////////////////////////////////////////////////////////////////////////////
    /// getItemList：
    ///         获得所有现存的处理框
    /// return: ( QList<DiagramItem*> ) 所有现存的处理框
    ///////////////////////////////////////////////////////////////////////////////////
    QList<DiagramItem*> getItemList() {return ItemList;}

private:

    m_ItemManager();

    ~m_ItemManager();

    m_ItemManager(const m_ItemManager&) = delete;

    m_ItemManager& operator=(const m_ItemManager&) = delete;

    ///////////////////////////////////////////////////////////////////////////////////
    /// updateText：
    ///         更新某个处理框中的文本
    /// para0: (int&) 该处理框在ItemList中索引
    ///////////////////////////////////////////////////////////////////////////////////
    void updateText(int& index);

public slots:

    ///////////////////////////////////////////////////////////////////////////////////
    /// updateItem：
    ///         更新某个处理框中的信息
    /// para0: (QVariantList)
    ///        index0: (int) 处理框序号
    ///        index1: (int) 算子序号
    ///        index2: (QString) 算子名字
    ///        index3: (QList<QString>) 算子的所有输入图像名字列表
    ///        index4: (QList<QString>) 算子的所有输出图像名字列表
    /// para1: (QVariantList) 算子的所有可调整的参数列表
    ///////////////////////////////////////////////////////////////////////////////////
    void updateItem(QVariantList Paras,QVariantList adjustableParaList);

    ///////////////////////////////////////////////////////////////////////////////////
    /// removeItem：
    ///         移除某个处理框
    /// para0: (DiagramItem*) 该处理框的指针
    ///////////////////////////////////////////////////////////////////////////////////
    void removeItem(DiagramItem* item);

    ///////////////////////////////////////////////////////////////////////////////////
    /// isEditing：
    ///         记录正在编辑的处理框到editingItem中
    /// para0: (DiagramItem*) 该处理框的指针
    ///////////////////////////////////////////////////////////////////////////////////
    void isEditing(DiagramItem*);

signals:
    ///////////////////////////////////////////////////////////////////////////////////
    /// isEditing：
    ///         记录正在编辑的处理框到editingItem中
    /// para0: (DiagramItem*) 该处理框的指针
    /// para1: (QVariantList) 相应参数
    ///////////////////////////////////////////////////////////////////////////////////
    void updateTextPos(DiagramItem* editingItem,QVariantList Paras);

};

extern m_ItemManager* m_itemManager;

#endif // M_ITEMMANAGER_H
