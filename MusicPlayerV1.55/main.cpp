#include "playerlogic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerLogic w;
    w.showMainWidget();

    QFile skinFile(":/skins/icons/skins.css");
    if(skinFile.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(skinFile.readAll());
        skinFile.close();
    }

    return a.exec();
}
