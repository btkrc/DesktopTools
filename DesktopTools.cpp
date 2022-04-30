#include "DesktopTools.h"

DesktopTools::DesktopTools(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    iniUi();
    iniConnect();
}

/*��������*/
DesktopTools::~DesktopTools() {
    //
}

void DesktopTools::iniUi() {
 
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(QString("\
#DesktopToolsClass{\
border:none;}"));

    wrapper = new WrapperWidget();

    /*�ӿں�������ʼ��������*/
    wrapper->iniTitleBar(this);


}

void DesktopTools::iniConnect() {
    //
}


void DesktopTools::paintEvent(QPaintEvent *event) {
    QPainter mPainter(this);
    mPainter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(":/DesktopTools/Resources/1FR3114501-1.jpg"));
}


