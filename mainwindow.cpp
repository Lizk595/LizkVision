#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1700,1000);
    setWindowTitle("LizkVision v1.0");

    setAcceptDrops(true);
    ui->plainTextEdit->setAcceptDrops(false);

    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setText("");
    ow=new OperatorWidget;


    myDiagram = new m_Diagram;

    //信号与槽
    connect(myDiagram->scene,&DiagramScene::OperatorShow,
            this,&MainWindow::OperatorShowSlot);
    connect(this,&MainWindow::diagramDispInput,
            myDiagram,&m_Diagram::dispImgInput);
    connect(this,&MainWindow::addFun,
            m_process,&m_PROCESS::addFunSlot);
    connect(myDiagram->pb_work,&QPushButton::clicked,
            this,&MainWindow::RUN);
    //当算子编辑窗口确认内容后，itemManager记录参数
    connect(ow,&OperatorWidget::updateItem,
            m_itemManager,&m_ItemManager::updateItem);
    //再次点击已经编辑好的处理框时，恢复到上次确认的内容
    connect(myDiagram->scene,&DiagramScene::recover,
            ow,&OperatorWidget::recover);
    //记录正在编辑的item
    connect(myDiagram->scene,&DiagramScene::isEditing,
            m_itemManager,&m_ItemManager::isEditing);
    //更新item中text的位置
    connect(m_itemManager,&m_ItemManager::updateTextPos,
            myDiagram->scene,&DiagramScene::updateTextPos);
    //单击按钮，显示图像
    connect(myDiagram->pb_dispImg,&QPushButton::clicked,
            myDiagram,&m_Diagram::showImage);

}

MainWindow::~MainWindow()
{
    delete ui;
}



//按钮：打开文件
void MainWindow::on_pushButton_3_clicked()
{
    //获取当前QT文件的路径
    QString currentPath=QCoreApplication::applicationDirPath();

    QString afilePath=QFileDialog::getOpenFileName(this,
                                                    "打开文件",     //对话框标题
                                                    currentPath,      //对话框路径
                                                    "所有文件(*);;.jpg;;.png"   //可选的文件格式筛选
                                                    );
    if(afilePath.isEmpty())
        return;


    //加载新内容
    dispimgInput(afilePath);



}


//显示输入图片
bool MainWindow::dispimgInput(QString& imgPath)
{
    cv::Mat imageInput=cv::imread(imgPath.toStdString());
    if(imageInput.empty()){
        QString Title="异常";
        QString Text="图片载入失败！";
        QMessageBox::critical(this,Title,Text);
        return false;
    }
    QImage imgdisp(imgPath);
    if(imgdisp.isNull()){
        QString Title="异常";
        QString Text="图片载入失败！";
        QMessageBox::critical(this,Title,Text);
        return false;
    }
    QPixmap pixmap1=QPixmap::fromImage(imgdisp);

    //更新m_imageManager
    //第一次载入图像
    if(m_imageManager->getImgNum()==0)
        m_imageManager->addImage(imageInput,"image_Input");
    //非第一次载入图像
    else
        m_imageManager->changeImg(0,imageInput,"image_Input");

    ui->plainTextEdit->appendPlainText("已载入： "+imgPath);

    int imgH=m_imageManager->getImage(0).rows;
    int imgW=m_imageManager->getImage(0).cols;
    int LabelH=ui->label->size().height();
    int LabelW =ui->label->size().width();
    //调整图片尺寸
    if(imgH>LabelH or imgW>LabelW){
        if( imgH/LabelH > imgW/LabelW )
            pixmap1 = pixmap1.scaled(imgW*LabelH/imgH , LabelH);
        else
            pixmap1 = pixmap1.scaled(LabelW , imgH*LabelW/imgW);
    }
    ui->label->setPixmap(pixmap1);
    emit diagramDispInput(QPixmap::fromImage(imgdisp));
    return true;
}


//打开算子编辑窗口
void MainWindow::OperatorShowSlot(DiagramItem* item)
{
    ow->show();
}


//执行流程并更新内容
void MainWindow::RUN()
{

    QList<DiagramItem*> sortedItems=m_itemManager->getItemList();

    //重置m_process
    m_process->reset();
    //将m_itemManager中的参数打包放入m_process中
    for(const auto& realItem : sortedItems){
        emit addFun(realItem->algtId,realItem->InputImgName,realItem->outputImgName,realItem->adjustableParaList);
    }
    //清空右侧可选择的输出图片
    m_imageManager->resetImgNames();
    //执行流程
    m_process->workProcess();
    //更新结果
    update();
    QString Title="信息";
    QString Text="执行完成！";
    QMessageBox::information(this,Title,Text);
}


//执行流程后，自动更新combbox内容
void MainWindow::update()
{
    myDiagram->cbB_dispImg->clear();
    int imgNum=m_imageManager->getImgNum();
    for(int i=0;i<imgNum;++i){
        QString imgName=QString::fromStdString(m_imageManager->getImgName(i));
        myDiagram->cbB_dispImg->addItem(imgName);
    }
}




//放下
void MainWindow::dropEvent(QDropEvent *event)
{
    QString imgPath=event->mimeData()->urls().at(0).path();
    imgPath=imgPath.right(imgPath.length()-1);
    dispimgInput(imgPath);
    event->accept();
}


//拖入
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QString pathInfo=event->mimeData()->urls().at(0).fileName();
        QFileInfo fileInfo(pathInfo);
        QString ex=fileInfo.suffix().toUpper();
        if( ex=="JPG" or
            ex=="PNG" or
            ex=="JPEG")
            event->acceptProposedAction();  //接受
    }
}



//执行流程按钮
void MainWindow::on_pushButton_6_clicked()
{
    if(0==m_imageManager->getImgNum()){
        QString Title="提示";
        QString Text="请先载入照片再执行流程！";
        QMessageBox::information(this,Title,Text);
        return;
    }

    myDiagram->show();
}



