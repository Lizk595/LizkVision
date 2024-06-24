#ifndef M_PROCESS_H
#define M_PROCESS_H

#include <QObject>
#include <QVariantList>
#include <vector>
#include <functional>
#include "m_algroithmfun.h"
#include <QList>

class m_PROCESS : public QObject
{
    Q_OBJECT
public:
    /////////////////////////////////////////////
    /// reset()：
    ///         重置processFun容器
    /////////////////////////////////////////////
    void reset();

    static m_PROCESS* getInstance(){return instance;}

private:
    /////////////////////////////////////////////
    /// processFun：
    ///         存储流程所需执行的算子
    /////////////////////////////////////////////
    std::vector<std::function<void()>> processFun;

    m_PROCESS(){}

    static m_PROCESS* instance;

    m_PROCESS(const m_PROCESS&) = delete;

    m_PROCESS& operator=(const m_PROCESS&) = delete;


public slots:
    /////////////////////////////////////////////
    /// addFunSlot()：
    ///         存储流程所需执行的算子
    /// para0: 算子序号
    /// para1: 算子的所有输入图像名字
    /// para2: 算子的所有输出图像名字
    /// para3: 算子的所有参数
    /////////////////////////////////////////////
    void addFunSlot(int& algtId, QList<QString>& inputName, QList<QString>& OutputName, QVariantList& adjustableList);

    /////////////////////////////////////////////
    /// workProcess()：
    ///         根据processFun中元素的顺序执行算子
    /////////////////////////////////////////////
    void workProcess();
};
extern m_PROCESS* m_process;

#endif // M_PROCESS_H
