#include "m_itemmanager.h"

m_ItemManager* m_ItemManager::instance=new m_ItemManager;
m_ItemManager* m_itemManager=m_ItemManager::getInstance();


m_ItemManager::m_ItemManager()
{
    editingItem=nullptr;
}


m_ItemManager::~m_ItemManager()
{
    if(editingItem!=nullptr){
        delete editingItem;
        editingItem=nullptr;
    }
    delete instance;
    instance=nullptr;
}


//获得目前编辑好的处理框的数量
int m_ItemManager::getItemNum()
{
    return (int)ItemList.size();
}



//根据id更新处理框内显示的id文本
void m_ItemManager::updateText(int& index)
{
    int id=ItemList[index]->id;
    QString text=QString::number(id) + ItemList[index]->text;
    ItemList[index]->textDisp->setPlainText(text);
}



//编辑某个处理框后，记录参数，更新内容
void m_ItemManager::updateItem(QVariantList Paras,QVariantList adjustableParaList)
{
    int old_index=editingItem->id;  //旧的处理框序号
    int index=Paras[0].toInt();     //新的处理框序号
    //更新editingItem
    editingItem->textDisp->setPlainText(QString::number(index));
    editingItem->text=Paras[2].toString();
    editingItem->id=index;
    editingItem->algtId=Paras[1].toInt();   //算子序号

    QList<QString> tempInput;
    for(auto& each:Paras[3].toList())
        tempInput.emplace_back(each.toString());
    editingItem->InputImgName=tempInput;

    QList<QString> tempOutput;
    for(auto& each:Paras[4].toList())
        tempOutput.emplace_back(each.toString());
    editingItem->outputImgName=tempOutput;

    editingItem->adjustableParaList=adjustableParaList.toList();

    //更新ItemList
    //新增处理框
    if(old_index==-1){
        //在末尾新增处理框
        if(index>=ItemList.size()){
            ItemList.emplaceBack(editingItem);

            updateText(index);
        //在非末尾处新增处理框
        }else{
            ItemList.insert(index,editingItem);
            //更新其后续处理框的id文本
            for(int i=index;i<ItemList.size();i++){
                ItemList[i]->id=i;
                updateText(i);
            }
        }
    //修改已经编辑好的处理框
    }else{
        //处理框的序号已改变
        if(index!=old_index){
            ItemList.erase(ItemList.begin()+old_index);
            ItemList.insert(index,editingItem);
            //更新其后续处理框的id文本
            for(int i=index;i<ItemList.size();i++){
                ItemList[i]->id=i;
                updateText(i);
            }
        }
    }

    emit updateTextPos(editingItem,Paras);
}



//移除某个处理框
void m_ItemManager::removeItem(DiagramItem* item)
{
    //处理框没有设置参数
    int index=item->id;
    if(index==-1 or index>ItemList.size())
        return;
    //更新ItemList
    //若移除的是末尾的处理框
    if(item->id==ItemList.size()){
        ItemList.pop_back();
    //若移除的是非末尾的处理框,更新item文本的序号
    }else{
        ItemList.removeAt(index);
        for(int i=index;i<ItemList.size();++i)
        {
            ItemList[i]->id=i;
            updateText(i);
        }
    }



    //移除输入图像列表中的名字
    for(auto& each:item->outputImgName){
        m_imageManager->removeImageNameInput(each.toStdString());
    }
}



//记录正在编辑的处理框
void m_ItemManager::isEditing(DiagramItem* item)
{
    editingItem=item;
}


