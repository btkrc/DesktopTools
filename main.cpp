#include "DesktopTools.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    DesktopTools w;
    w.show();
    return a.exec();
}
