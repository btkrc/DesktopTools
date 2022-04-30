#pragma once
#include <QtWidgets/QWidget>
#include "ui_CustomBar.h"
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxlayout>
#include <QEvent>
#include <QGridLayout>

/*������*/
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



/*������*/
class WrapperWidget :
    public QWidget {
    Q_OBJECT
public:

    explicit WrapperWidget(QWidget *parent = nullptr);
    ~WrapperWidget();

    /*�ӿں���*/
    void iniTitleBar(QWidget *widget);

private:
    CustomBar *customBar;
    QGridLayout *tLayout;
    QPoint *currentWindowPos;

    void iniUi();
    void iniConnect();

private slots:
    /*CustomBar�Ĺرհ�ť�¼�*/
    void onBtnCloseClicked();

protected:
    /*����CustomBar���¼�*/
    bool eventFilter(QObject *obj, QEvent *event)override;


};