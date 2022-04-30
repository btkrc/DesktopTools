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
    ui.mTitleLabel->setText(QString(QStringLiteral("�Զ��������ʾ��  ...btkrc1nx")));

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

/*�����źţ��������д���*/
void CustomBar::onBtnCloseClicked() {
    emit btnCloseClicked();
}

/*slots end*/


/*������*/
WrapperWidget::WrapperWidget(QWidget *parent) :QWidget(parent) {
    iniUi();
    iniConnect();
}

WrapperWidget::~WrapperWidget(){
    delete currentWindowPos;
}

/*�ӿڣ���������ӵ�������*/
void WrapperWidget::iniTitleBar(QWidget *widget) {
    tLayout->addWidget(widget, 1, 0, 1, 1);
    /*����������ӵ�������*/
    widget->setParent(this);

    this->show();
}


void WrapperWidget::onBtnCloseClicked() {
    this->close();
}

/*��ʼ��UI*/
void WrapperWidget::iniUi(){
    currentWindowPos = new QPoint();




    setWindowFlags(Qt::FramelessWindowHint);

    /*initialize size*/
    resize(600, 400);
    setAttribute(Qt::WA_TranslucentBackground);


    customBar = new CustomBar(this);
    customBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    /*ע��CustomBar���¼���������������*/
    customBar->installEventFilter(this);

    customBar->setParent(this);


    /*դ�񲼾֣����������������ӵ�������*/
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
            /*���������˫��*/
        case QEvent::MouseButtonDblClick: {

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            /*������˫��ȫ����ʾ*/
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
            /*ǿ��ת������*/
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            /*���浱ǰ�����������*/
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
    else {//��δ������¼���������
        return QWidget::eventFilter(obj, event);
    }
}
