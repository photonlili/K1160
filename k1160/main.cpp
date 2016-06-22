#include "hnapp.h"
#include "hngui-qt.h"
#include "version.h"
#include "HNDefine.h"
#include "hngui.h"

int main(int argc, char *argv[])
{
    HNApp a(argc, argv);

    return a.exec();
}
