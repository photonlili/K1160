#include "hnreport.h"

HNReport::HNReport(QObject *parent) :
    HNWordExpress(parent)
{
}

void HNReport::createSampleReport(const QString &head, const QString &foot, const QString &title, const QTableView *table)
{
    initWordExpress();
    setHeaderText(head);
    setFooterText(foot);
    addText(title, titleFont());
    //addText("");
    addText("试验结果", title2Font(), Qt::AlignLeft);
    //addText("");
    addTable(table);
    addSignoffText("打印人:___________");
}

void HNReport::GenerateComplexReport()
{
}


HNReport *HNReportInstance(QObject *parent)
{
    static HNReport* r = new HNReport(parent);
    return r;
}

