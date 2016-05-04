#include "hnwordexpress.h"
#include "HNDefine.h"

HNWordExpress::HNWordExpress(QObject *parent) :
    QObject(parent),
    fmt(0), mainFmt(0),headerFmt(0),titleFmt(0), title2Fmt(0)
{
    //setup printer
    pr= new HNPrinter(QPrinter::HighResolution);
    pr->setFullPage(true);
    pr->setColorMode(QPrinter::Color);
    pr->setPaperSize(QPrinter::A4);
    pr->setOrientation(QPrinter::Portrait);
    pr->setOutputFormat(QPrinter::PdfFormat);

    //Font目标是打印纸上，所见即所得。
    //Pos目标不是纸上的，是屏幕上的，所以更换屏幕，必须更换DPI；
    //这个数值是迪文屏上的标准分辨率，打印机使用会失真；
    //迪文View 142,138 //PCView 96 //打印机View 1200
    //打印机分辨率1200不会失真，绘图必须进行坐标变换。
    //数值增大，DrawText可用空间减小甚至切掉一部分
#ifdef __MIPS_LINUX__
    //这是实验结果，和理论结果不符合。
    logicalDpiX = 136;
    logicalDpiY = 156;
#else
    logicalDpiX = 96;
    logicalDpiY = 96;
#endif

    QRect rect = pr->paperRect();
    sceneRect = QRectF(0.0, 0.0, logicalDpiX *rect.width()/pr->logicalDpiX(), logicalDpiY*rect.height()/pr->logicalDpiY());

#if 0
    //1200 9917,14033 printerRect 固定
    //116  958,1356 sceneRect
    //142  1113,1660 sceneRect
    pline() << pr->logicalDpiX() << pr->logicalDpiY();
    pline()  << logicalDpiX << logicalDpiY << pr->pageRect() << sceneRect;
    pline() << pr->paperRect(QPrinter::DevicePixel);
    pline() << pr->paperRect(QPrinter::Millimeter);
    pline() << pr->paperRect(QPrinter::Point);
    pline() << pr->paperRect(QPrinter::Inch);
    pline() << pr->paperRect(QPrinter::Pica);
    pline() << pr->paperRect(QPrinter::Didot);
    pline() << pr->paperRect(QPrinter::Cicero);
#endif

    m_mainFont = QApplication::font();
    if(mainFmt)
        delete mainFmt;
    mainFmt = new QFontMetrics(m_mainFont);
    m_titleFont= QApplication::font();
    m_titleFont.setPointSize(22);
    if(titleFmt)
        delete titleFmt;
    titleFmt = new QFontMetrics(m_titleFont);
    m_title2Font = QApplication::font();;
    m_title2Font.setPointSize(16);
    if(title2Fmt)
        delete title2Fmt;
    title2Fmt =new QFontMetrics(m_title2Font);

    setMargin();
    setHeaderSize();
    setFooterSize();

    setFont();
    setHeaderFont();
    setLineSpacing();

    setHeaderLine();
    setFooterLine();

    initWordExpress();
}

void HNWordExpress::setMargin(qreal left, qreal right, qreal top, qreal botoom)
{
    leftMargin=134.6;
    rightMargin=134.6;
    topMargin=177.7;
    bottomMargin=177.7;
}

QRectF HNWordExpress::margin()
{
    return QRectF(leftMargin, topMargin,
                  sceneRect.width()-leftMargin-rightMargin,
                  sceneRect.height()-topMargin-bottomMargin);
}

void HNWordExpress::setFont(QFont font)
{
    //normal font 11
    m_font = QApplication::font();
    if(fmt)
        delete fmt;
    fmt = new QFontMetrics(m_font);
}

void HNWordExpress::setLineSpacing(qreal spacing)
{
    //单倍行距
    mainHeight = mainFmt->height();
    titleHeight = titleFmt->height();
    title2Height = title2Fmt->height();
    headerHeight = headerFmt->height();

    mainSpacing = mainFmt->height() * 2;
    titleSpacing = titleFmt->height() * 2;
    title2Spacing = title2Fmt->height() * 2;
    headerSpacing = headerFmt->height() * 1;
}

void HNWordExpress::addText(const QString &text, QFont font, Qt::Alignment align, QPointF point)
{
    QFontMetrics fmt = QFontMetrics(font);
    int spacing = fmt.height() * 2;
    int height = fmt.height();
    int width=fmt.width(text);

    pline() << font.pointSize() << fmt.height();

    adjustdy(height + spacing);

    HNGraphicsTextItem* item = pageScene->addText(text, font);

    if(align & Qt::AlignLeft)
        item->moveBy(dx, dy+height);
    else if(align & Qt::AlignRight)
        item->moveBy(xpos2 - width, dy+height);
    else if(align & Qt::AlignHCenter)
        item->moveBy((pageScene->width()/2)-(width/2), dy+height);
    dy += height + spacing;
}

void HNWordExpress::addSignoffText(const QString &text, QFont font)
{
    adjustdy(mainHeight + mainSpacing);

    int ddy = dy;

    dy = ypos2 - ( (mainHeight + mainSpacing) * 2 );

    addText(text, m_mainFont, Qt::AlignRight);

    dy = ddy;
}

void HNWordExpress::addTable(const QTableView *table, QPointF pos)
{
    const QTableView *tableView = table;
    QAbstractItemModel* model = tableView->model();
    QFont tableFont = tableView->font();
    QFontMetrics tableFmt = QFontMetrics(tableFont);

    int tableRowHeight = tableView->horizontalHeader()->height();
    adjustdy(tableRowHeight);
    for (int i=0; i<model->columnCount(); i++) {
        int logicalIndex=tableView->horizontalHeader()->logicalIndex(i);
        int actColSize= tableView->columnWidth(logicalIndex);

        QPen pen(Qt::gray, 0.1);
        QBrush brush(QColor(255, 250, 250));
        //QBrush brush(tableView->horizontalHeader()->palette().background());
        pageScene->addRect(dx,dy, actColSize,tableRowHeight, pen, brush);

        QString txt = model->headerData(logicalIndex,Qt::Horizontal,Qt::DisplayRole).toString();
        txt = tableFmt.elidedText(txt, Qt::ElideRight, actColSize-2);
        HNGraphicsTextItem *item = pageScene->addText(txt, tableFont);
        item->moveBy(dx, dy);
        dx += actColSize;
    }
    dy += tableRowHeight;

    //Table rows
    QPen pen(Qt::gray, 0.1);
    QBrush brush(Qt::gray, Qt::SolidPattern);
    int row = 0;
    for (;;) {
        if (row >= model->rowCount()) {
            break;
        }

        tableRowHeight = tableView->rowHeight(row);
        adjustdy(tableRowHeight);
        for (int j=0; j<model->columnCount(); j++) {
            int logicalIndex=tableView->horizontalHeader()->logicalIndex(j);
            int actColSize=tableView->columnWidth(logicalIndex);

            QPen pen(Qt::gray, 0.1);
            QBrush brush(tableView->palette().window());
            bool balt = tableView->alternatingRowColors();
            if(balt)
            {
                int modulo= row % 2;
                if (modulo != 0) {
                    //rectangle grey
                    pageScene->addRect(dx,dy,actColSize,tableRowHeight, pen, brush);
                }
                else
                {
                    pageScene->addRect(dx,dy,actColSize,tableRowHeight, pen);
                }
            }
            else
            {
                pageScene->addRect(dx,dy,actColSize,tableRowHeight, pen);
            }

            QString txt = model->data(model->index(row,logicalIndex)).toString();
            txt=tableFmt.elidedText(txt,Qt::ElideRight,actColSize-2);
            HNGraphicsTextItem *item = pageScene->addText(txt, tableFont);
            item->moveBy(dx,dy);

            dx+=actColSize;
        }
        row++;
        dy += tableRowHeight;
        dx = xpos;
    }
}

void HNWordExpress::exportPdf(const QString &pdf)
{
    // setup printer
    pr->setOutputFileName(pdf);

    // print pdf
    QPainter p(pr);

    HNGraphicsScene* pageScene = 0;
    foreach (pageScene, pageSceneVector) {

        pageScene->render(&p, pr->paperRect(), sceneRect);

        if(pageScene != pageSceneVector.last())
            pr->newPage();
    }
}

HNGraphicsScene *HNWordExpress::getPage(int num)
{
    if(num < 1 || num > pageSceneVector.size())
        return NULL;
    return pageSceneVector.at(num-1);
}

void HNWordExpress::print()
{
    pr->print();
}

void HNWordExpress::setHeaderFont(QFont font)
{
    //header font
    m_headerFont = QApplication::font();;
    m_headerFont.setPointSize(9);
    if(headerFmt)
        delete headerFmt;
    headerFmt =new QFontMetrics(m_headerFont);
}

void HNWordExpress::setHeaderSize(qreal size)
{
    headerSize=70;
}

void HNWordExpress::setHeaderLine(bool show)
{

}

void HNWordExpress::setHeaderText(const QString &text, QFont font, Qt::Alignment align)
{
    headerText = text;
    paintPageHeader();
}

void HNWordExpress::setFooterSize(qreal size)
{
    footerSize=70;
}

void HNWordExpress::setFooterLine(bool show)
{

}

void HNWordExpress::setFooterText(const QString &text, QFont font, Qt::Alignment align)
{
    footerText = text;
    paintPageFooter();
}

void HNWordExpress::initWordExpress()
{
    while ( ! pageSceneVector.isEmpty() ) {
        HNGraphicsScene* pageScene = pageSceneVector.first();
        pageScene->clear();
        delete pageScene;
        pageSceneVector.remove(0);
    }
    headerText = "";
    footerText = "";
    createFrame();
}

void HNWordExpress::adjustdy(qreal dy0)
{
    dx = xpos;
    if(dy + dy0 < ypos2)
        return;
    createFrame();
}


void HNWordExpress::createFrame()
{
    xpos = leftMargin;
    xpos2 = sceneRect.width() - rightMargin;
    ypos = topMargin;
    ypos2 = sceneRect.height() - bottomMargin;
    dx = xpos;
    dy = ypos;

    pageScene = new HNGraphicsScene(sceneRect);
    pageSceneVector.append(pageScene);
    paintPageHeader();
    paintPageFooter();
}

void HNWordExpress::paintPageHeader()
{
    // Page header
    if (headerText.isEmpty())
        return;

    int sx = xpos;
    int sy = ypos-headerSize;
    //页眉
    HNGraphicsTextItem *headerItem = pageScene->addText(headerText, m_headerFont);
    headerItem->moveBy(sx, sy);

    //std text
    QString date=QDate::currentDate().toString(QLocale().dateFormat());
    QString time=QTime::currentTime().toString(QLocale().timeFormat(QLocale::ShortFormat));
    QString headerStdText;
    headerStdText = date+"  "+time;
    HNGraphicsTextItem *item = pageScene->addText(headerStdText, m_headerFont);
    item->moveBy(xpos2 - headerFmt->width(headerStdText), sy);

    sy += headerItem->boundingRect().height();

    //line
    pageScene->addLine(xpos, sy, xpos2, sy, QPen(Qt::black, 1.0));
}

void HNWordExpress::paintPageFooter()
{
    if (footerText.isEmpty())
        return;

    // footer
    int sx = xpos;

    QString footerStdText = tr("第 ") + QString::number(pageSceneVector.size()) + tr(" 页");
    HNGraphicsTextItem *item=pageScene->addText(footerStdText, m_headerFont);
    int height = item->boundingRect().height();
    int sy = ypos2 + footerSize - height;
    item->moveBy(xpos2 - headerFmt->width(footerStdText), sy);

    pageScene->addLine(xpos, sy, xpos2, sy, QPen(Qt::black, 1.0));

    HNGraphicsTextItem *footerItem=pageScene->addText(footerText, m_headerFont);
    footerItem->moveBy(xpos, sy);
}
