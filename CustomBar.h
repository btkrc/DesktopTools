#pragma once
#include <QtWidgets/QWidget>
#include "ui_CustomBar.h"
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxlayout>
#include <QEvent>
#include <QGridLayout>

/*标题栏*/
class CustomBar :
    public QWidget{
    Q_OBJECT
public:
    CustomBar(QWidget *parent = nullptr);
private:
    Ui::CustomBarClass ui;
    void iniUi();
    void iniConnect();

    QHBoxLayout *hLayout;
private slots:
    void onBtnCloseClicked();

signals:
    void btnCloseClicked();
    void doubleClicked();

protected:
    void paintEvent(QPaintEvent *event)override;

};



/*容器类*/
class WrapperWidget :
    public QWidget {
    Q_OBJECT
public:

    explicit WrapperWidget(QWidget *parent = nullptr);
    ~WrapperWidget();

    /*接口函数*/
    void iniTitleBar(QWidget *widget);

private:
    CustomBar *customBar;
    QGridLayout *tLayout;
    QPoint *currentWindowPos;

    void iniUi();
    void iniConnect();

private slots:
    /*CustomBar的关闭按钮事件*/
    void onBtnCloseClicked();

protected:
    /*监听CustomBar的事件*/
    bool eventFilter(QObject *obj, QEvent *event)override;


};