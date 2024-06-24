#include "m_algroithmfun.h"



void fun_cvtColor(std::string& imgInputName, std::string& imgOutputName, int& mode)
{
    cv::Mat imgOutput;
    cv::cvtColor(m_imageManager->getImage(imgInputName),imgOutput,mode);
    m_imageManager->addImage(imgOutput,imgOutputName);
}



void fun_threshold(std::string& imgInputName, std::string& imgOutputName, double& thres, double& maxValue, int& mode)
{
    cv::Mat imgOutput;
    cv::threshold(m_imageManager->getImage(imgInputName),imgOutput,thres,maxValue,mode);
    m_imageManager->addImage(imgOutput,imgOutputName);
}



