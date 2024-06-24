#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/////////////////////////////
#include <QFileDialog>

#include <QPixmap>
#include <QMessageBox>
#include <QImage>
#include <QMimeData>
#include <QFile>
#include <QGraphicsItem>
#include "operatorwidget.h"
////////////////////////////
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private slots:

    void on_pushButton_3_clicked();

    void OperatorShowSlot(DiagramItem* item);

    void RUN();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow*                             ui;
    bool                                        isTracking=false;
    QPoint                                      moveOffset;
    OperatorWidget*                             ow;
    std::vector<QGraphicsItem*>                 all_itemEdited;
    m_Diagram*                                  myDiagram;

protected:

    virtual void dropEvent(QDropEvent *event) override;

    virtual void dragEnterEvent(QDragEnterEvent *event) override;

    bool dispimgInput(QString& imgPath);

    void update();

signals:

    void diagramDispInput(QPixmap pixmap);

    void addFun(int& algtId,QList<QString>& inputName, QList<QString>& OutputName, QVariantList& adjustableList);

    void newInput();
};


#endif // MAINWINDOW_H
