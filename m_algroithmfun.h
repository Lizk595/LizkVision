#ifndef M_ALGROITHMFUN_H
#define M_ALGROITHMFUN_H

#include "ImageMANAGER.h"

enum m_algorithm{
    //基本图像处理
    resize=0,
    cvtcolor=1,
    split=2,
    merge=3,
    //图像平滑
    medianBlur=4,
    blur=5,
    //阈值处理
    threshold=6,
    dyn_threshold=7,
    //形态学处理
    opening=8,
    closing=9,
    //图像运算
    dilation=10,
    erosion=11,
    add=12,
    sub=13,
    invert=14,
    addWeighted=15,
    //轮廓处理
    findContours=16,
    drawContours=17,
    //连通域特征计算
    minOuterRect=18,
    minOuterCir=19,
    areaConnect=20,
};

//颜色空间转换
void fun_cvtColor(std::string& imgInputName,std::string& imgOutputName,int& mode);


//阈值分割
void fun_threshold(std::string& imgInputName, std::string& imgOutputName, double& thres, double& maxValue, int& mode);

#endif // M_ALGROITHMFUN_H
