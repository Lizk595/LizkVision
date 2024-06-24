#ifndef OPERATORWIDGET_H
#define OPERATORWIDGET_H

//#include "imagemanager.h"
// #include "imagemanager.h"
#include <QWidget>
#include <QRegularExpression>
#include <QComboBox>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include "imagemanager.h"
#include "m_itemmanager.h"
#include "m_diagram.h"
namespace Ui {
class OperatorWidget;
}

class OperatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OperatorWidget(QWidget *parent = nullptr);
    ~OperatorWidget();


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


    void on_lineEdit_6_textChanged(const QString &arg1);

public slots:
    void recover(DiagramItem *item);

private:
    Ui::OperatorWidget *ui;

    void optInputImgInit(int& id,QComboBox* ComboBox);

    bool isOutputName(QString& name);

    void imgOutputError();

    void updateCombobox();

    int checkID();

signals:
    void addInputImgDisp(QString& imgName);

    void updateItem(QVariantList t1,QVariantList t2);
};

#endif // OPERATORWIDGET_H
