#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DesktopTools.h"
#include <QStyle>
#include "CustomBar.h"
#include <QGridLayout>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QEvent>
#include <QPoint>

class DesktopTools : public QMainWindow{
    Q_OBJECT

public:
    DesktopTools(QWidget *parent = Q_NULLPTR);
    ~DesktopTools();

private:
    Ui::DesktopToolsClass ui;

    WrapperWidget *wrapper;

    void iniUi();
    void iniConnect();


protected:
    /*ÖØÐ´»æÍ¼ÊÂ¼þ*/
    void paintEvent(QPaintEvent *event)override;

};
