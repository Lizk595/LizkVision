#ifndef M_DIAGRAM_H
#define M_DIAGRAM_H

//#include "diagramitem.h"
#include "imagemanager.h"
#include "diagramscene.h"
#include "m_algroithmfun.h"
#include "m_process.h"
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QtWidgets>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE


QPixmap cvMat2QPixmap(cv::Mat& mat);

//! [0]
class m_Diagram : public QMainWindow
{
    Q_OBJECT

public:
    //! [0]
    m_Diagram();

private slots:
    void buttonGroupClicked(QAbstractButton *button);
    void deleteItem();
    void pointerGroupClicked();
    //void bringToFront();
    //void sendToBack();
    void itemInserted(DiagramItem *item);
    //void textInserted(QGraphicsTextItem *item);
    //void currentFontChanged(const QFont &font);
    //void fontSizeChanged(const QString &size);
    void sceneScaleChanged(const QString &scale);
    //void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    //void textButtonTriggered();
    void fillButtonTriggered();
    void lineButtonTriggered();

    //void handleFontChange();
    //void itemSelected(QGraphicsItem *item);
    //void about();
public slots:
    void dispImgInput(QPixmap imgInput);
    void showImage();
    void updateDisp();


public:
    DiagramScene *scene;
    QComboBox* cbB_dispImg;
    QPushButton* pb_work;
    QPushButton* pb_dispImg;

signals:
    void itemRemove(DiagramItem*);
private:
    void createToolBox();
    void createActions();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //void createMenus();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void createToolbars();
    //QWidget *createBackgroundCellWidget(const QString &text,const QString &image);
    QWidget *createCellWidget(const QString &text,
                              DiagramItem::DiagramType type);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);
    QToolButton* mycreatToolButton(DiagramItem::DiagramType type);


    QGraphicsView *view;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    // QAction *toFrontAction;
    // QAction *sendBackAction;
    QAction *aboutAction;


    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;
    QToolBar *myToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;

    QPushButton* pb_saveImg;
    QHBoxLayout* hLayout_up;
    QGroupBox* gb_up;
    QLabel* label_dispImg;
    QVBoxLayout* vLayout_mid;
    QGroupBox* gb_mid;
    QTabWidget* tW_result;
    QPlainTextEdit* pte_0;
    QWidget* tab_0;
    QHBoxLayout* hLayout_pte_0;
    QPlainTextEdit* pte_1;
    QWidget* tab_1;
    QHBoxLayout* hLayout_pte_1;
    QHBoxLayout* hLayout_buttom;
    QGroupBox* gb_buttom;
    QVBoxLayout* vLayout;
    QVBoxLayout* vLayout2;
    QWidget *widget;
    QHBoxLayout *layout;
};
//! [0]

#endif // M_DIAGRAM_H
