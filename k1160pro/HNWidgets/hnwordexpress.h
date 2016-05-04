#ifndef HNWORDEXPRESS_H
#define HNWORDEXPRESS_H

#include <QObject>
#include "hngui-qt.h"
#include "hnprinter.h"
#include "hngraphicsscene.h"

class HNWordExpress : public QObject
{
    Q_OBJECT
public:
    explicit HNWordExpress(QObject *parent = 0);

    void addText(const QString& text, QFont m_font = QFont(),
                 Qt::Alignment align = Qt::AlignHCenter, QPointF point= QPointF(0, 0));
    void addSignoffText(const QString& text, QFont m_font = QFont());
    void addTable(const QTableView* table, QPointF pos = QPointF(0, 0));

    int pageNum() { return pageSceneVector.size(); }
    HNGraphicsScene* getPage(int num);
    void exportPdf(const QString &pdf);
    void print();

    QRectF margin();
    void setMargin(qreal left = 0, qreal right = 0,
                   qreal top = 0, qreal botoom = 0);
    void setLineSpacing(qreal mainSpacing = 0);
    void setHeaderSize(qreal size = 0);
    void setFooterSize(qreal size = 0);

    QFont font() { return m_font; }
    void setFont(QFont m_font = QFont());
    void setHeaderFont(QFont m_font = QFont());
    QFont mainFont() { return m_mainFont; }
    QFont titleFont() { return m_titleFont; }
    QFont title2Font() { return m_title2Font; }
    QFont headerFont() { return m_headerFont; }
    void setHeaderLine(bool show = false);
    void setFooterLine(bool show = false);
    void setHeaderText(const QString &text, QFont m_font = QFont(),
                       Qt::Alignment align = Qt::AlignHCenter);
    void setFooterText(const QString& text, QFont m_font = QFont(),
                       Qt::Alignment align = Qt::AlignHCenter);
    /**
     * @brief initWordExpress 初始化纸张，第一张空白纸
     */
    void initWordExpress();

protected:
    virtual void adjustdy(qreal dy0);
    virtual void createFrame();
    virtual void paintPageHeader();
    virtual void paintPageFooter();
signals:

public slots:

private:
    //输出
    HNPrinter* pr;
    //对页面元素高度不能迅速统计的场景
    QVector<HNGraphicsScene*> pageSceneVector;
    HNGraphicsScene* pageScene;

    //页面元素
    int logicalDpiX;
    int logicalDpiY;
    QRectF sceneRect;

    qreal xpos, xpos2, ypos, ypos2;
    qreal dx, dy;

    qreal leftMargin;
    qreal rightMargin;
    qreal topMargin;
    qreal bottomMargin;

    qreal mainHeight;
    qreal titleHeight;
    qreal title2Height;
    qreal headerHeight;
    qreal mainSpacing;
    qreal titleSpacing;
    qreal title2Spacing;
    qreal headerSpacing;

    //页眉
    qreal headerSize;
    QFont m_headerFont;
    QFontMetrics *headerFmt;
    QString headerText;
    //页脚
    qreal footerSize;
    QString footerStdText;
    QString footerText;
    //标题
    QFont m_titleFont;
    QFontMetrics *titleFmt;
    //二号标题
    QFont m_title2Font;
    QFontMetrics *title2Fmt;
    //正文
    QFont m_mainFont;
    QFontMetrics *mainFmt;
    //使用中
    QFont m_font;
    QFontMetrics *fmt;
};

#endif // HNWORDEXPRESS_H
