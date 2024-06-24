
#include "m_diagram.h"



const int InsertTextButton = 10;

m_Diagram::m_Diagram()
{
    createActions();
    createToolBox();
    //createMenus();

    scene = new DiagramScene(itemMenu, this);

    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, &DiagramScene::itemInserted,     //插入item
            this, &m_Diagram::itemInserted);
    // connect(scene, &DiagramScene::textInserted,     //选中文本item
    //         this, &m_Diagram::textInserted);
    // connect(scene, &DiagramScene::itemSelected,     //选中item
    //         this, &m_Diagram::itemSelected);
    createToolbars();

    layout = new QHBoxLayout;
    //layout->addWidget(toolBox);
    view = new QGraphicsView(scene);

    //初始化view的缩放为50%
    double newScale = 0.5;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);

    //layout->addWidget(view);




    //////////////////////////////////////////////////////////////////////////
    //test
    // QPushButton* pb=new QPushButton;
    // pb->setText("11111");
    // layout->addWidget(pb);

    //设置图像显示GroupBox
    cbB_dispImg =new QComboBox;

    pb_dispImg = new QPushButton;
    pb_dispImg->setText("显示图像");
    connect(pb_dispImg,&QPushButton::click,this,&m_Diagram::showImage);

    pb_saveImg = new QPushButton;
    pb_saveImg->setText("保存图像");
    hLayout_up = new QHBoxLayout;
    hLayout_up->addWidget(cbB_dispImg);
    hLayout_up->addWidget(pb_dispImg);
    hLayout_up->addWidget(pb_saveImg);
    hLayout_up->setStretch(0,1111);
    hLayout_up->setStretch(1,1);
    hLayout_up->setStretch(2,1);
    gb_up = new QGroupBox;
    gb_up->setTitle("图像显示");
    gb_up->setLayout(hLayout_up);

    //设置图像预览GroupBox
    gb_mid = new QGroupBox;
    gb_mid->setTitle("图像预览");
    vLayout_mid = new QVBoxLayout(gb_mid);
    vLayout_mid->setStretch(0,100);
    label_dispImg = new QLabel();
    vLayout_mid->addWidget(label_dispImg);
    label_dispImg->setText(" ");
    label_dispImg->setAlignment(Qt::AlignCenter);


    // gb_mid = new QGroupBox;
    // vLayout_mid = new QVBoxLayout(gb_mid);
    // label_dispImg = new QLabel(gb_mid);
    // vLayout_mid->addWidget(label_dispImg);
    // vLayout_mid->setStretch(0,0);
    // label_dispImg->setText(" ");
    // label_dispImg->setAlignment(Qt::AlignCenter);   //文本居中

    // vLayout_mid->addWidget(label_dispImg);
    // gb_mid->setLayout(vLayout_mid);

    //设置图像预览GroupBox下方的tabWidget
    tW_result = new QTabWidget;
    //设置tab_0
    pte_0 = new QPlainTextEdit;
    tab_0= new QWidget();
    hLayout_pte_0 = new QHBoxLayout(tab_0);
    hLayout_pte_0->addWidget(pte_0);
    tW_result->addTab(tab_0, QString());
    tW_result->setTabText(0,"运行日志");
    //设置tab_1
    pte_1 = new QPlainTextEdit;
    tab_1= new QWidget();
    hLayout_pte_1 = new QHBoxLayout(tab_1);
    hLayout_pte_1->addWidget(pte_1);
    tW_result->addTab(tab_1, QString());
    tW_result->setTabText(1,"检测总览");


    hLayout_buttom = new QHBoxLayout;
    hLayout_buttom->addWidget(tW_result);
    gb_buttom = new QGroupBox;
    gb_buttom->setLayout(hLayout_buttom);



    vLayout = new QVBoxLayout;
    vLayout->addWidget(gb_up);
    vLayout->addWidget(gb_mid);
    vLayout->addWidget(gb_buttom);
    vLayout->setStretch(0,0);
    vLayout->setStretch(1,1);
    vLayout->setStretch(2,1);

    vLayout2 = new QVBoxLayout;
    pb_work=new QPushButton;
    pb_work->setText("开始执行");
    vLayout2->addWidget(view);
    vLayout2->addWidget(pb_work);
    vLayout2->setStretch(0,8);
    vLayout2->setStretch(1,3);

    layout->addLayout(vLayout2);
    layout->addLayout(vLayout);
    layout->setStretch(0,2);
    layout->setStretch(1,3);
    layout->setStretch(2,5);
    //////////////////////////////////////////////////////////////////////////


    widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("流程配置"));
    setUnifiedTitleAndToolBarOnMac(true);


    //当cbB_dispImg改变时，自动更新选择
    connect(cbB_dispImg,&QComboBox::currentIndexChanged,
            this,&m_Diagram::updateDisp);

    //当删除处理框时，在m_ItemManager中进行删除
    connect(this,&m_Diagram::itemRemove,
            m_itemManager,&m_ItemManager::removeItem);

}


void m_Diagram::buttonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    const int id = buttonGroup->id(button);
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertLine);
    } else {
        scene->setItemType(DiagramItem::DiagramType(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}


//删除处理框or连接线
void m_Diagram::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    selectedItems = scene->selectedItems();
    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == DiagramItem::Type)
            qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
        DiagramItem* diagramitem = qgraphicsitem_cast<DiagramItem *>(item);
        emit itemRemove(diagramitem);       //在itemManager中删除
        scene->removeItem(item);
        scene->removeItem(diagramitem->textDisp);
        delete item;
    }
}


void m_Diagram::pointerGroupClicked()
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}


// void m_Diagram::bringToFront()
// {
//     if (scene->selectedItems().isEmpty())
//         return;

//     QGraphicsItem *selectedItem = scene->selectedItems().first();
//     const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

//     qreal zValue = 0;
//     for (const QGraphicsItem *item : overlapItems) {
//         if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
//             zValue = item->zValue() + 0.1;
//     }
//     selectedItem->setZValue(zValue);
// }


//
// void m_Diagram::sendToBack()
// {
//     if (scene->selectedItems().isEmpty())
//         return;

//     QGraphicsItem *selectedItem = scene->selectedItems().first();
//     const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

//     qreal zValue = 0;
//     for (const QGraphicsItem *item : overlapItems) {
//         if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
//             zValue = item->zValue() - 0.1;
//     }
//     selectedItem->setZValue(zValue);
// }

void m_Diagram::itemInserted(DiagramItem *item)
{
    //pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

// void m_Diagram::textInserted(QGraphicsTextItem *)
// {
//     buttonGroup->button(InsertTextButton)->setChecked(false);
//     scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
// }

// void m_Diagram::currentFontChanged(const QFont &)
// {
//     handleFontChange();
// }

// void m_Diagram::fontSizeChanged(const QString &)
// {
//     handleFontChange();
// }

void m_Diagram::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}


// void m_Diagram::textColorChanged()
// {
//     textAction = qobject_cast<QAction *>(sender());
//     fontColorToolButton->setIcon(createColorToolButtonIcon(
//         ":/icon/images/linepointer.png",
//         qvariant_cast<QColor>(textAction->data())));
//     textButtonTriggered();
// }

void m_Diagram::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
        ":/icon/images/floodfill.png",
        qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}


void m_Diagram::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/icon/images/linecolor.png",
        qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

// void m_Diagram::textButtonTriggered()
// {
//     scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
// }

void m_Diagram::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void m_Diagram::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}


//在label中显示图像
void m_Diagram::dispImgInput(QPixmap imgInput)
{
    int imgH=imgInput.height();
    int imgW=imgInput.width();
    int LabelH=label_dispImg->size().height();
    int LabelW =label_dispImg->size().width();
    if(imgH>LabelH or imgW>LabelW){
        if( imgH/LabelH > imgW/LabelW )
            imgInput = imgInput.scaled(imgW*LabelH/imgH , LabelH);
        else
            imgInput = imgInput.scaled(LabelW , imgH*LabelW/imgW);
    }
    label_dispImg->setPixmap(imgInput);
    //加入image_Input
    bool hasImgInput=false;
    for(int i=0;i<cbB_dispImg->count();++i){
        if(cbB_dispImg->itemText(i)=="image_Input"){
            hasImgInput=true;
            break;
        }
    }
    if(hasImgInput==false)
        cbB_dispImg->addItem("image_Input");
}


//单击显示图像按钮
void m_Diagram::showImage()
{
    int ImgIndex=cbB_dispImg->currentIndex();
    cv::Mat img=m_imageManager->getImage(ImgIndex);
    std::string imgName=m_imageManager->getImgName(ImgIndex);
    cv::imshow(imgName,img);
}


//自动更新显示的图片
void m_Diagram::updateDisp()
{
    std::string imgDispName=cbB_dispImg->currentText().toStdString();
    cv::Mat img=m_imageManager->getImage(imgDispName);
    QPixmap imgdisp=cvMat2QPixmap(img);
    int imgH=imgdisp.height();
    int imgW=imgdisp.width();
    int LabelH =label_dispImg->size().height();
    int LabelW =label_dispImg->size().width();
    if(imgH>LabelH or imgW>LabelW){
        if( imgH/LabelH > imgW/LabelW )
            imgdisp = imgdisp.scaled(imgW*LabelH/imgH , LabelH);
        else
            imgdisp = imgdisp.scaled(LabelW , imgH*LabelW/imgW);
    }
    label_dispImg->setPixmap(imgdisp);
}






QPixmap cvMat2QPixmap(cv::Mat& mat)
{
    //CV_8UC1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar* pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return QPixmap::fromImage(image);
    }

    //CV_8UC3
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return QPixmap::fromImage(image.rgbSwapped());
    }
    else if (mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return QPixmap::fromImage(image.copy());
    }
    else
    {
        return QPixmap();
    }
}


// void m_Diagram::handleFontChange()
// {
//     QFont font = fontCombo->currentFont();
//     font.setPointSize(fontSizeCombo->currentText().toInt());
//     font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
//     font.setItalic(italicAction->isChecked());
//     font.setUnderline(underlineAction->isChecked());

//     scene->setFont(font);
// }

// void m_Diagram::itemSelected(QGraphicsItem *item)
// {
//     DiagramTextItem *textItem =
//         qgraphicsitem_cast<DiagramTextItem *>(item);

//     QFont font = textItem->font();
//     fontCombo->setCurrentFont(font);
//     fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
//     boldAction->setChecked(font.weight() == QFont::Bold);
//     italicAction->setChecked(font.italic());
//     underlineAction->setChecked(font.underline());
// }

// void m_Diagram::about()
// {
//     QMessageBox::about(this, tr("About Diagram Scene"),
//                        tr("The <b>Diagram Scene</b> example shows "
//                           "use of the graphics framework."));
// }

void m_Diagram::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &m_Diagram::buttonGroupClicked);
    //QGridLayout *layout = new QGridLayout;
    //createCellWidget(tr("条件"), DiagramItem::Conditional);
    //createCellWidget(tr("过程"), DiagramItem::Step);
    //createCellWidget(tr("输入/输出"), DiagramItem::Io)
    //layout->addWidget(createCellWidget(tr("条件"), DiagramItem::Conditional), 0, 0);
    //layout->addWidget(createCellWidget(tr("过程"), DiagramItem::Step),0, 1);
    //layout->addWidget(createCellWidget(tr("输入/输出"), DiagramItem::Io), 1, 0);
    //! [21]

    QToolButton *textButton = new QToolButton;          //使用连接线按钮
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    //textButton->setIcon(QIcon(QPixmap(":/icon/images/linepointer.png")));
    //textButton->setIconSize(QSize(50, 50));
    //QGridLayout *textLayout = new QGridLayout;
    //textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    //textLayout->addWidget(new QLabel(tr("连接")), 1, 0, Qt::AlignCenter);
    //QWidget *textWidget = new QWidget;
    //textWidget->setLayout(textLayout);
    //layout->addWidget(textWidget, 1, 1);

    //layout->setRowStretch(3, 10);
    //layout->setColumnStretch(2, 10);

    //QWidget *itemWidget = new QWidget;
    //itemWidget->setLayout(layout);

    //backgroundButtonGroup = new QButtonGroup(this);
    //connect(backgroundButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
    //this, &m_Diagram::backgroundButtonGroupClicked);

    // QGridLayout *backgroundLayout = new QGridLayout;
    // backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
    //                                                        ":/icon/images/background1.png"), 0, 0);
    // backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
    //                                                        ":/icon/images/background2.png"), 0, 1);
    // backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
    //                                                        ":/icon/images/background3.png"), 1, 0);
    // backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
    //                                                        ":/icon/images/background4.png"), 1, 1);

    // backgroundLayout->setRowStretch(2, 10);
    // backgroundLayout->setColumnStretch(2, 10);

    //QWidget *backgroundWidget = new QWidget;
    //backgroundWidget->setLayout(backgroundLayout);



    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    //toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    //toolBox->addItem(itemWidget, tr("操作"));
    //toolBox->addItem(backgroundWidget, tr("设置背景"));
}

void m_Diagram::createActions()
{

    // toFrontAction = new QAction(QIcon(":/icon/images/bringtofront.png"),
    //                             tr("Bring to &Front"), this);
    // toFrontAction->setShortcut(tr("Ctrl+F"));
    // toFrontAction->setStatusTip(tr("Bring item to front"));
    // connect(toFrontAction, &QAction::triggered, this, &m_Diagram::bringToFront);


    // sendBackAction = new QAction(QIcon(":/icon/images/sendtoback.png"), tr("Send to &Back"), this);
    // sendBackAction->setShortcut(tr("Ctrl+T"));
    // sendBackAction->setStatusTip(tr("Send item to back"));
    // connect(sendBackAction, &QAction::triggered, this, &m_Diagram::sendToBack);

    deleteAction = new QAction(QIcon(":/icon/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &m_Diagram::deleteItem);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // boldAction = new QAction(tr("Bold"), this);
    // boldAction->setCheckable(true);
    // QPixmap pixmap(":/icon/images/bold.png");
    // boldAction->setIcon(QIcon(pixmap));
    // boldAction->setShortcut(tr("Ctrl+B"));
    // connect(boldAction, &QAction::triggered, this, &m_Diagram::handleFontChange);

    // italicAction = new QAction(QIcon(":/icon/images/italic.png"), tr("Italic"), this);
    // italicAction->setCheckable(true);
    // italicAction->setShortcut(tr("Ctrl+I"));
    // connect(italicAction, &QAction::triggered, this, &m_Diagram::handleFontChange);

    // underlineAction = new QAction(QIcon(":/icon/images/underline.png"), tr("Underline"), this);
    // underlineAction->setCheckable(true);
    // underlineAction->setShortcut(tr("Ctrl+U"));
    // connect(underlineAction, &QAction::triggered, this, &m_Diagram::handleFontChange);

    // aboutAction = new QAction(tr("A&bout"), this);
    // aboutAction->setShortcut(tr("F1"));
    // connect(aboutAction, &QAction::triggered, this, &m_Diagram::about);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void m_Diagram::createMenus()
// {
//     fileMenu = menuBar()->addMenu(tr("&File"));
//     fileMenu->addAction(exitAction);

//     itemMenu = menuBar()->addMenu(tr("&Item"));
//     itemMenu->addAction(deleteAction);
//     itemMenu->addSeparator();
//     itemMenu->addAction(toFrontAction);
//     itemMenu->addAction(sendBackAction);

//     aboutMenu = menuBar()->addMenu(tr("&Help"));
//     aboutMenu->addAction(aboutAction);
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void m_Diagram::createToolbars()
{

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    //editToolBar->addAction(toFrontAction);
    //editToolBar->addAction(sendBackAction);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // fontCombo = new QFontComboBox();        //设置字体的comboBox
    // connect(fontCombo, &QFontComboBox::currentFontChanged,
    //         this, &m_Diagram::currentFontChanged);

    // fontSizeCombo = new QComboBox;          //设置字体大小的comboBox
    // fontSizeCombo->setEditable(true);
    // for (int i = 8; i < 30; i = i + 2)
    //     fontSizeCombo->addItem(QString().setNum(i));
    // QIntValidator *validator = new QIntValidator(2, 64, this);
    // fontSizeCombo->setValidator(validator);
    // connect(fontSizeCombo, &QComboBox::currentTextChanged,
    //         this, &m_Diagram::fontSizeChanged);

    // fontColorToolButton = new QToolButton;                  //设置流程图字体颜色按钮
    // fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    // fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    // textAction = fontColorToolButton->menu()->defaultAction();
    // fontColorToolButton->setIcon(createColorToolButtonIcon(":/icon/images/textpointer.png", Qt::black));
    // fontColorToolButton->setAutoFillBackground(true);
    // connect(fontColorToolButton, &QAbstractButton::clicked,
    //         this, &m_Diagram::textButtonTriggered);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fillColorToolButton = new QToolButton;          //设置框图背景颜色按钮
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
        ":/icon/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, &QAbstractButton::clicked,
            this, &m_Diagram::fillButtonTriggered);


    lineColorToolButton = new QToolButton;          //设置连接线颜色按钮
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/icon/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, &QAbstractButton::clicked,
            this, &m_Diagram::lineButtonTriggered);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // textToolBar = addToolBar(tr("Font"));
    // textToolBar->addWidget(fontCombo);
    // textToolBar->addWidget(fontSizeCombo);
    // textToolBar->addAction(boldAction);
    // textToolBar->addAction(italicAction);
    // textToolBar->addAction(underlineAction);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    colorToolBar = addToolBar(tr("Color"));
    //colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;       //鼠标指针按钮
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/icon/images/pointer.png"));

    QToolButton *linePointerButton = new QToolButton;   //画连接线按钮
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/icon/images/linepointer.png"));


    // //画Process按钮
    // QToolButton *ProcessButton = new QToolButton;
    // ProcessButton->setCheckable(true);
    // ProcessButton->setIcon(QIcon(":/icon/images/process.png"));
    // buttonGroup->addButton(ProcessButton,int(DiagramItem::Step));

    // //画Conditional按钮
    // QToolButton *ConditionalButton = new QToolButton;
    // ConditionalButton->setCheckable(true);
    // ConditionalButton->setIcon(QIcon(":/icon/images/conditional.png"));
    // buttonGroup->addButton(ConditionalButton,int(DiagramItem::Conditional));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    // pointerTypeGroup->addButton(ProcessButton, int(DiagramScene::Step));
    // pointerTypeGroup->addButton(ConditionalButton, int(DiagramScene::Conditional));

    //pointerTypeGroup中的button被点击时的connect
    connect(pointerTypeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &m_Diagram::pointerGroupClicked);

    //改变scene的缩放
    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("25%") <<tr("50%") << tr("75%") << tr("100%") << tr("125%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(1);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &m_Diagram::sceneScaleChanged);


    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    //pointerToolbar->addWidget(ProcessButton);
    //pointerToolbar->addWidget(ConditionalButton);
    pointerToolbar->addWidget(mycreatToolButton(DiagramItem::Conditional));
    pointerToolbar->addWidget(mycreatToolButton(DiagramItem::Step));
    pointerToolbar->addWidget(mycreatToolButton(DiagramItem::Io));
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

}



// QWidget *m_Diagram::createBackgroundCellWidget(const QString &text, const QString &image)
// {
//     QToolButton *button = new QToolButton;
//     button->setText(text);
//     button->setIcon(QIcon(image));
//     button->setIconSize(QSize(50, 50));
//     button->setCheckable(true);
//     backgroundButtonGroup->addButton(button);

//     QGridLayout *layout = new QGridLayout;
//     layout->addWidget(button, 0, 0, Qt::AlignHCenter);
//     layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

//     QWidget *widget = new QWidget;
//     widget->setLayout(layout);

//     return widget;
// }



QWidget *m_Diagram::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{

    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QToolButton* m_Diagram::mycreatToolButton(DiagramItem::DiagramType type)
{

    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());
    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));
    return button;
}


QMenu *m_Diagram::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}



QIcon m_Diagram::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}



QIcon m_Diagram::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

