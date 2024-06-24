#include "operatorwidget.h"
#include "ui_operatorwidget.h"
#include <QMessageBox>
OperatorWidget::OperatorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OperatorWidget)
{
    ui->setupUi(this);
    setWindowTitle("编辑参数");
    ui->comboBox_2->addItem("THRESH_BINARY");
    ui->comboBox_2->addItem("THRESH_BINARY_INV");
    ui->comboBox_2->addItem("THRESH_TRUNC");
    ui->comboBox_2->addItem("THRESH_TOZERO");
    ui->comboBox_2->addItem("THRESH_TOZERO_INV");

    ui->comboBox_4->addItem("灰度图");
    ui->stackedWidget->setCurrentIndex(0);



}

OperatorWidget::~OperatorWidget()
{
    delete ui;
}



//初始化各算子的可选择的输入图像
void OperatorWidget::optInputImgInit(int& id,QComboBox* ComboBox)
{
    if(ComboBox->count()>0)
        ComboBox->clear();
    ComboBox->addItem("image_Input");
    if(id==0)
        return;
    else{
        QList<DiagramItem*> sortedItems = m_itemManager->getItemList();
        int i=0;
        for(const auto& item:sortedItems){
            for(const auto& eachOutput:item->outputImgName){
                ComboBox->addItem(eachOutput);
            }
            if(i==id-1)
                break;
            i++;
        }
    }
}


//检查输出图像的名字是否合法
bool OperatorWidget::isOutputName(QString& name)
{
    QRegularExpression regex("^[A-Za-z0-9_-]+$");
    QRegularExpressionMatch match = regex.match(name);
    return match.hasMatch();
}



//调整尺寸
void OperatorWidget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//颜色空间转换
void OperatorWidget::on_pushButton_4_clicked()
{
    int id=checkID();
    if(id==-1)
        return;
    optInputImgInit(id,ui->comboBox_3);
    ui->stackedWidget->setCurrentIndex(2);
}

//通道拆分
void OperatorWidget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//通道合并
void OperatorWidget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//中值滤波
void OperatorWidget::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


//均值滤波
void OperatorWidget::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


//二值化阈值分割
void OperatorWidget::on_pushButton_9_clicked()
{
    int id=checkID();
    if(id==-1)
        return;
    optInputImgInit(id,ui->comboBox);
    ui->stackedWidget->setCurrentIndex(7);
}

//动态阈值分割
void OperatorWidget::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

//退出按钮
void OperatorWidget::on_pushButton_2_clicked()
{
    this->close();
}


//确认按钮
void OperatorWidget::on_pushButton_clicked()
{

    //检查id序号
    QString idStr=ui->lineEdit_6->text();
    bool idisInt;
    int idInt=idStr.toInt(&idisInt);
    int itemNum=m_itemManager->getItemNum();
    if((!idisInt) or idInt<0 or idInt>itemNum){
        QString title="异常";
        QString text="序号应为数字!\n取值范围：不超过"+QString::number(itemNum)+"的自然数。";
        QMessageBox::critical(this,title,text);
    }
    //检查输入参数是否正常
    int Algorithm_index=ui->stackedWidget->currentIndex();
    switch(Algorithm_index)
    {
    case(0):{   //未选择任何算子
        QString Title="提示";
        QString Text="未选择算子并编辑参数，请检查后再确认!";
        QMessageBox::information(this,Title,Text);
        return;
    }
    case(1):{   //调整尺寸
        break;
    }
    case(2):{   //颜色空间转换
        //获得输入图像的名字
        QString imgName_Input_1=ui->comboBox_3->currentText();
        QList<QString> imgNameInputList;
        imgNameInputList.emplace_back(imgName_Input_1);
        //获得转换模式
        int mode=-1;
        QString selectedMode=ui->comboBox_4->currentText();
        for(int i=0;i<1;i++){
            if(selectedMode=="灰度图"){
                //判断输入图像是否为单通道
                std::string inputName=ui->comboBox_3->currentText().toStdString();
                if(m_imageManager->getImage(inputName).channels()==CV_8UC1){
                    QString Title="输入异常";
                    QString Text="输入图像为单通道，无法转换！";
                    QMessageBox::warning(this,Title,Text);
                    return;
                }
                mode=6;     //cv::COLOR_BGR2GRAY == 6 , cv::COLOR_RGB2GRAY == 7
                break;
            }
            //if(selectedMode=="RGB图")
        }
        QVariantList adjustableParaList;
        adjustableParaList.emplace_back(mode);

        //获得输出图像名字
        QString imgOutputName_1=ui->lineEdit_12->text();
        if(imgOutputName_1.isNull()){
            imgOutputError();
            return;
        }
        bool isProper=isOutputName(imgOutputName_1);
        if(!isProper){
            imgOutputError();
            return;
        }
        QList<QString> imgNameOutputList;
        imgNameOutputList.emplace_back(imgOutputName_1);
        //发送信号
        QVariantList paraList;
        paraList.append(idInt);
        paraList.append((int)m_algorithm::cvtcolor);
        paraList.append("颜色空间转换");
        paraList.append(imgNameInputList);
        paraList.append(imgNameOutputList);
        //将输出图片的名字保存到imagemanager中，使下次编辑算子参数时可以选择其为输入
        for(const auto each:imgNameOutputList)
            m_imageManager->addImageNameInput(each.toStdString());

        emit updateItem(paraList,adjustableParaList);  //更新itemManager中的item
        break;
    }
    case(3):{   //通道拆分
        break;
    }
    case(4):{   //通道合并
        break;
    }
    case(5):{   //中值滤波

    }
    case(6):{   //均值滤波
        break;
    }
    case(7):{   //二值化阈值分割
        //检查Thres
        QString ThresStr=ui->lineEdit_31->text();
        if(ThresStr==""){
            QString Title="输入异常";
            QString Text="请输入Thres!\n取值范围：0≤Thres≤255";
            QMessageBox::warning(this,Title,Text);
            return;
        }
        bool ThresisDouble;
        double Thres = ThresStr.toDouble(&ThresisDouble);
        if((!ThresisDouble) or Thres<=0 or Thres>255){
            QString Title="输入异常";
            QString Text="Thres输入有误!\n取值范围：0≤Thres≤255";
            QMessageBox::warning(this,Title,Text);
            return;
        }
        //检查maxValue
        QString maxValueStr=ui->lineEdit->text();
        if(ThresStr.isNull()){
            QString Title="输入异常";
            QString Text="请输入maxValue!\n取值范围：0≤Thres≤255";
            QMessageBox::warning(this,Title,Text);
            return;
        }
        bool maxValueisDouble;
        double maxValue = maxValueStr.toDouble(&maxValueisDouble);
        if((!maxValueisDouble) or maxValue<=0 or maxValue>255){
            QString Title="输入异常";
            QString Text="maxValue输入有误!\n取值范围：0≤maxValue≤255";
            QMessageBox::warning(this,Title,Text);
            return;
        }
        //检查用户定义的输出图像名字
        QString imgOutputName=ui->lineEdit_32->text();
        if(imgOutputName.isNull()){
            imgOutputError();
            return;
        }
        bool isProper=isOutputName(imgOutputName);
        if(!isProper){
            imgOutputError();
            return;
        }
        //获取输入图像的名字
        int curIndex1=ui->comboBox->currentIndex();
        QString imgName_Input_1=ui->comboBox->itemText(curIndex1);
        QList<QString> imgNameInputList;
        imgNameInputList.emplace_back(imgName_Input_1);
        //获取输出图像的名字
        QString imgName_Output_1=ui->lineEdit_32->text();
        QList<QString> imgNameOutputList;
        imgNameOutputList.emplace_back(imgName_Output_1);
        //获取处理模式
        int curIndex2=ui->comboBox_2->currentIndex();
        std::string modeStr=ui->comboBox_2->itemText(curIndex2).toStdString();
        int mode;
        for(int i=0;i<1;i++){
            if(modeStr=="THRESH_BINARY"){
                mode=0;
                break;
            }
            if(modeStr=="THRESH_BINARY_INV"){
                mode=1;
                break;
            }
            if(modeStr=="THRESH_TRUNC"){
                mode=2;
                break;
            }
            if(modeStr=="THRESH_TOZERO"){
                mode=3;
                break;
            }
            if(modeStr=="THRESH_TOZERO_INV"){
                mode=4;
                break;
            }
        }
        QVariantList adjustableParaList;
        adjustableParaList.emplace_back(Thres);
        adjustableParaList.emplace_back(maxValue);
        adjustableParaList.emplace_back(mode);
        //发送信号
        QVariantList paraList;
        paraList.append(idInt);
        paraList.append((int)m_algorithm::threshold);
        paraList.append("二值化阈值分割");
        paraList.append(imgNameInputList);
        paraList.append(imgNameOutputList);

        emit updateItem(paraList,adjustableParaList);
        //将输出图片的名字保存到imagemanager中，使下次编辑算子参数时可以选择其为输入
        for(const auto each:imgNameOutputList)
            m_imageManager->addImageNameInput(each.toStdString());
        break;
    }
    case(8):{   //动态阈值分割
        break;
    }
    case(9):{
        break;
    }
    case(10):{
        break;
    }
    case(11):{
        break;
    }
    case(12):{
        break;
    }
    case(13):{
        break;
    }
    }
    updateCombobox();
    this->close();
}




//从diagramscene中得到正在编辑的item
// void OperatorWidget::getEditingItem(DiagramItem *item)
// {
//     editingItem=item;
// }



//输出图像名字不符合要求
void OperatorWidget::imgOutputError()
{
    QString Title="输出异常";
    QString Text="输出图像的名字有误！\n名字应仅包含字母、数字、-和_。";
    QMessageBox::warning(this,Title,Text);
}


//在点击本次算子编辑的确认按钮后，更新每个算子编辑的输出图像的combobox
void OperatorWidget::updateCombobox()
{
    ui->comboBox->clear();      //二值化阈值处理
    ui->comboBox_3->clear();    //颜色空间转换

    int imgNum=m_imageManager->getImgNum();
    for(int i=0;i<imgNum;++i){
        QString imgName=QString::fromStdString(m_imageManager->getImgName(i));
        ui->comboBox->addItem(imgName);
        ui->comboBox_3->addItem(imgName);
    }
}

//检查用户定义的序号是否合理,当不合理，返回-1，若合理，返回id
int OperatorWidget::checkID()
{
    bool isInt;
    int id=ui->lineEdit_6->text().toInt(&isInt);
    int itemNum=m_itemManager->getItemNum();
    if(!isInt or id<0 or id>itemNum ){
        QString Title="异常";
        QString Text="序号应为数字!\n取值范围：不超过"+QString::number(itemNum)+"的自然数。";
        QMessageBox::warning(this,Title,Text);
    }

    if(isInt)
        return id;
    return -1;
}


//恢复到上次保存的结果
void OperatorWidget::recover(DiagramItem *item)
{
    //初始化处理框序号
    ui->lineEdit_6->setText(QString::number(m_itemManager->getItemNum()));
    //未编辑的处理框
    if(item->id==-1){
        ui->lineEdit_6->setText(QString::number(m_itemManager->getItemNum()));
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    //已经保存过的处理框
    int id=item->id;
    ui->lineEdit_6->setText(QString::number(id));
    int algtID=item->algtId;
    switch(algtID)
    {
    //颜色空间转换
    case((int)m_algorithm::cvtcolor):{
        optInputImgInit(item->id,ui->comboBox_3);
        ui->stackedWidget->setCurrentIndex(2);
        QString imgInputName=item->InputImgName[0];
        QString imgOutputName=item->outputImgName[0];
        ui->comboBox_3->setCurrentText(imgInputName);
        ui->lineEdit_12->setText(imgOutputName);

        int Mode=item->adjustableParaList[0].toInt();
        switch(Mode){
        case(6)://灰度图
            ui->comboBox_4->setCurrentIndex(0);
            break;
        }
        break;
    }
    //二值化阈值
    case((int)m_algorithm::threshold):{
        optInputImgInit(item->id,ui->comboBox);
        ui->stackedWidget->setCurrentIndex(7);
        QString imgInputName=item->InputImgName[0];
        double Thres=item->adjustableParaList[0].toDouble();
        double maxValue=item->adjustableParaList[1].toDouble();
        int mode=item->adjustableParaList[2].toInt();
        QString imgOutputName=item->outputImgName[0];
        ui->comboBox->setCurrentText(imgInputName);
        ui->lineEdit_31->setText(QString::number(Thres));
        ui->lineEdit->setText(QString::number(maxValue));
        ui->comboBox_2->setCurrentIndex(mode);
        ui->lineEdit_32->setText(imgOutputName);
        break;
    }
    }
}

//当序号改变，可选择的输入图像也相应改变
void OperatorWidget::on_lineEdit_6_textChanged(const QString &arg1)
{
    int id=checkID();
    if(id==-1)
        return;
    //根据序号，更新相应算子的可选择的输入图像
    switch(ui->stackedWidget->currentIndex())
    {
    case(2):{       //颜色空间转换
        optInputImgInit(id,ui->comboBox_3);
    }
    case(7):{       //二值化阈值分割
        optInputImgInit(id,ui->comboBox);
    }
    default:break;
    }
}

