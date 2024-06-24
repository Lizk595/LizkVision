#include "m_process.h"

m_PROCESS* m_PROCESS::instance=new m_PROCESS;
m_PROCESS* m_process=m_PROCESS::getInstance();

void m_PROCESS::reset()
{
    processFun.clear();
}


void m_PROCESS::addFunSlot(int& algtId,QList<QString>& inputName, QList<QString>& OutputName, QVariantList& adjustableList)
{
    switch(algtId)
    {
        case(m_algorithm::resize):{
            break;
        }
        case(m_algorithm::cvtcolor):{
            std::string imgName_Input  = inputName[0].toStdString();
            std::string imgName_Output = OutputName[0].toStdString();
            int mode =adjustableList[0].toInt();
            processFun.push_back(std::bind(fun_cvtColor, imgName_Input, imgName_Output, mode));
            break;
        }
        case(m_algorithm::split):{
            break;
        }
        case(m_algorithm::merge):{
            break;
        }
        case(m_algorithm::medianBlur):{
            break;
        }
        case(m_algorithm::blur):{
            break;
        }
        case(m_algorithm::threshold):{
            std::string imgName_Input  = inputName[0].toStdString();
            std::string imgName_Output = OutputName[0].toStdString();
            double Thres = adjustableList[0].toDouble();
            double maxValue = adjustableList[1].toDouble();
            int mode = adjustableList[2].toInt();
            processFun.push_back(std::bind(fun_threshold, imgName_Input, imgName_Output, Thres, maxValue, mode));
            break;
        }
        case(m_algorithm::dyn_threshold):{
            break;
        }
        case(m_algorithm::opening):{
            break;
        }
        case(m_algorithm::closing):{
            break;
        }
        case(m_algorithm::dilation):{
            break;
        }
        case(m_algorithm::erosion):{
            break;
        }
        case(m_algorithm::add):{
            break;
        }
        case(m_algorithm::sub):{
            break;
        }
        case(m_algorithm::invert):{
            break;
        }
        case(m_algorithm::addWeighted):{
            break;
        }
        case(m_algorithm::findContours):{
            break;
        }
        case(m_algorithm::drawContours):{
            break;
        }
        case(m_algorithm::minOuterRect):{
            break;
        }
        case(m_algorithm::minOuterCir):{
            break;
        }
        case(m_algorithm::areaConnect):{
            break;
        }
        default:
            break;
    }

}



//执行过程
void m_PROCESS::workProcess()
{
    for(auto& eachFun : processFun)
        eachFun();
}
