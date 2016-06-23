#include "hnapp.h"
#include "hngui-qt.h"
#include "version.h"
#include "HNDefine.h"
#include "hngui.h"
#include "hnwindow.h"

int main(int argc, char *argv[])
{
    HNApp a(argc, argv);

    HNWindow w;
    w.show();

    return a.exec();
}
