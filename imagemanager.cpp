#include "ImageMANAGER.h"

ImageMANAGER* ImageMANAGER::instance=new ImageMANAGER;
ImageMANAGER* m_imageManager=ImageMANAGER::getInstance();



//初始化
ImageMANAGER::ImageMANAGER()
{
    imgsNameInput.emplace_back("image_Input");
}


ImageMANAGER::~ImageMANAGER()
{
    delete instance;
    instance=nullptr;
}


//当载入新的image_Input时，重置m_imageManager
void ImageMANAGER::reset()
{
    imgs.clear();
    imgsName.clear();
    imgsNameInput.clear();
    imgsNameInput.emplace_back("image_Input");
}


//增加图像
void ImageMANAGER::addImage(cv::Mat& img,std::string imgName)
{
    cv::Mat temp=img;
    imgs.emplace_back(temp);
    imgsName.emplace_back(imgName);
}


cv::Mat ImageMANAGER::getImage(int& index)
{
    return imgs[index];
}



cv::Mat ImageMANAGER::getImage(int&& index)
{
    return imgs[index];
}


//通过图像名字返回图像
cv::Mat ImageMANAGER::getImage(std::string name)
{
    int index=0;
    for(const auto each:imgsName){
        if(each==name)
            break;
        index++;
    }
    if(index>=imgsName.size())
        return cv::Mat::zeros(1,1,CV_8UC1);
    return imgs[index];
}



std::string ImageMANAGER::getImgName(int &index)
{
    return imgsName[index];
}


//根据索引更新imageManager中记录的图像
bool ImageMANAGER::changeImg(int& index, cv::Mat& img,std::string Name)
{
    if(index<imgs.size()){
        imgs[index]=std::move(img);
        imgsName[index]=Name;
        return true;
    }
    return false;
}


//根据索引更新imageManager中记录的图像
bool ImageMANAGER::changeImg(int&& index, cv::Mat& img,std::string Name)
{
    if(index<imgs.size()){
        imgs[index]=std::move(img);
        imgsName[index]=Name;
        if(index==0)
            imgsNameInput[index]=Name;
        return true;
    }
    return false;
}


//清空图像容器
void ImageMANAGER::clearImgs()
{
    imgs.clear();
    imgsName.clear();
}


//重置imgsName容器
void ImageMANAGER::resetImgNames()
{
    imgsName.clear();
    imgsName.emplace_back("image_Input");
}



int ImageMANAGER::getImgNum()
{
    return (int)imgsName.size();
}



std::string ImageMANAGER::getImageNameInput(int &index)
{
    return imgsNameInput[index];
}


//返回image_Input的数量
int ImageMANAGER::getImageNameInputNum()
{
    if(imgsNameInput.empty())
        return 0;
    return (int)imgsNameInput.size();
}


//当移除已经编辑好的item时，需要删除其输出图像的名字
void ImageMANAGER::removeImageNameInput(std::string name)
{
    int i=0;
    for(const auto each:imgsNameInput){
        if(name==each)
            break;
        i++;
    }
    imgsNameInput.erase(imgsNameInput.begin()+i);
}



//将输出图片的名字保存到imageManager中，使下次编辑算子参数时可以选择其作为输入
void ImageMANAGER::addImageNameInput(std::string name)
{
    for(const auto each:imgsNameInput)
        if(each==name)
            return;
    imgsNameInput.emplace_back(name);
}





