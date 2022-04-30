#include "CustomBar.h"



CustomBar::CustomBar(QWidget *parent) :QWidget(parent) {
    ui.setupUi(this);
    iniUi();
    iniConnect();
}

void CustomBar::iniUi() {
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowOpacity(0.5);
    setStyleSheet(QString("#CustomBarClass{\
background-color:rgba(0,0,0,0.5);\
border:none;}\
QPushButton{\
border:none;\
background-color:pink;\
}\
QPushButton::hover{\
background-color:red;}\
#mTitleLabel{color:white;}\
"));
    ui.btnClose->setFixedSize(32, 32);
    ui.mTitleLabel->setText(QString(QStringLiteral("自定义标题栏示例  ...btkrc1nx")));

    setAttribute(Qt::WA_StyledBackground);

    this->setMinimumHeight(40);

    hLayout = new QHBoxLayout(this);

    hLayout->addWidget(ui.mTitleLabel);
    hLayout->addWidget(ui.btnClose);

}

void CustomBar::iniConnect() {
    QObject::connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));
}

void CustomBar::paintEvent(QPaintEvent *event) {
    return QWidget::paintEvent(event);
}


/*slots*/

/*发射信号，在主类中处理。*/
void CustomBar::onBtnCloseClicked() {
    emit btnCloseClicked();
}

/*slots end*/


/*容器类*/
WrapperWidget::WrapperWidget(QWidget *parent) :QWidget(parent) {
    iniUi();
    iniConnect();
}

WrapperWidget::~WrapperWidget(){
    delete currentWindowPos;
}

/*接口，将窗口添加到容器中*/
void WrapperWidget::iniTitleBar(QWidget *widget) {
    tLayout->addWidget(widget, 1, 0, 1, 1);
    /*将主窗口添加到容器中*/
    widget->setParent(this);

    this->show();
}


void WrapperWidget::onBtnCloseClicked() {
    this->close();
}

/*初始化UI*/
void WrapperWidget::iniUi(){
    currentWindowPos = new QPoint();




    setWindowFlags(Qt::FramelessWindowHint);

    /*initialize size*/
    resize(600, 400);
    setAttribute(Qt::WA_TranslucentBackground);


    customBar = new CustomBar(this);
    customBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    /*注册CustomBar的事件监听器到此容器*/
    customBar->installEventFilter(this);

    customBar->setParent(this);


    /*栅格布局，将标题和主窗口添加到容器中*/
    tLayout = new QGridLayout(this);
    tLayout->setSpacing(0);
    tLayout->setContentsMargins(0, 0, 0, 0);
    tLayout->addWidget(customBar, 0, 0, 1, 1);
}

void WrapperWidget::iniConnect(){
    QObject::connect(customBar, SIGNAL(btnCloseClicked()), this, SLOT(onBtnCloseClicked()));
}

bool WrapperWidget::eventFilter(QObject *obj, QEvent *event) {
    if (obj == customBar) {
        switch (event->type()) {
            /*标题栏鼠标双击*/
        case QEvent::MouseButtonDblClick: {

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            /*鼠标左键双击全屏显示*/
            if (mouseEvent->buttons() & Qt::LeftButton) {
                if (Qt::WindowMaximized == this->windowState()) {
                    this->showNormal();
                }
                else {
                    this->showMaximized();
                }
            }
            return true;
        }
        case QEvent::MouseButtonPress: {
            /*强制转换类型*/
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            /*保存当前窗口相对坐标*/
            *currentWindowPos = mouseEvent->pos();
            return true;
        }
        case QEvent::MouseMove: {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->buttons() & Qt::LeftButton) {
                this->move(mouseEvent->globalPos() - *currentWindowPos);
                return true;
            }
            else
                return false;
        }
        default: {
            return false;
        }
        }
    }
    else {//将未处理的事件传给基类
        return QWidget::eventFilter(obj, event);
    }
}
