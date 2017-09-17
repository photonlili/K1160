#include "qqtapp.h"
#include "qqtgui-qt.h"
#include "version.h"
#include "qqtdefine.h"
#include "qqtgui.h"
#include "qqtwindow.h"

int main(int argc, char *argv[])
{
    QQTApp a(argc, argv);

    QQTWindow w;
    w.show();

    return a.exec();
}
