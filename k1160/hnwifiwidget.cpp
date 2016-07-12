#include "hnwifiwidget.h"
#include "ui_hnwifiwidget.h"
#include "hnlinux.h"
#include "HNDefine.h"
#include "HNEthManager.h"
#include "hnmsgbox.h"


void HNWIFIIDTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
#if 0
    if (!rect.isValid())
        return;
    QStyleOptionViewItem opt(option);
    opt.rect = rect;
    opt.state = opt.state & ~QStyle::State_HasFocus;
    switch (state) {
    case Qt::Unchecked:
        opt.state |= QStyle::State_Off;
        break;
    case Qt::PartiallyChecked:
        opt.state |= QStyle::State_NoChange;
        break;
    case Qt::Checked:
            opt.state |= QStyle::State_On;
        break;
    }
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter);
#else
    QItemDelegate::drawCheck(painter, option, rect, state);
#endif
}

void HNWIFIIDTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if("COMPLETED" == text)
        painter->drawImage(rect, QImage("./skin/default/bk_sel.png"));
}

HNWIFIWidget::HNWIFIWidget(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNWIFIWidget)
{
    ui->setupUi(this);

    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clickWIFI()), Qt::QueuedConnection);
    m_pass = new HNPasswordDialog(this);

    m_pManager = HNEthManager::Instance(this);
    connect(m_pManager, SIGNAL(sigRefreshed()), this, SLOT(wifiRefreshed()));

    m_model = new HNStandardItemModel(this);
    m_model->setColumnCount(ESSID_MAX);
    setModel(m_model);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(true);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    dg = new HNWIFIIDTextDelegate(this);
    setItemDelegateForColumn(ESSID_STATUS, dg);
    for(int i = ESSID_TYPE; i < ESSID_MAX; i++)
        setColumnHidden(i, true);
    horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    setColumnWidth(ESSID_STATUS, 40);

}

HNWIFIWidget::~HNWIFIWidget()
{
    delete ui;
}


TWifi HNWIFIWidget::currentWifi()
{
    return m_pManager->currentWifi();
}


bool HNWIFIWidget::setCurrentWifi(QString bssid_mac, QString password)
{
    return m_pManager->setCurrentWifi(bssid_mac, password);
}

void HNWIFIWidget::wifiRefreshed()
{
    int row = 0;
    m_model->removeRows(row, m_model->rowCount());
    QList<TWifi>& list = m_pManager->wifiList();
    m_model->insertRows(row, list.size());
    for(QList<TWifi>::Iterator it = list.begin();
        it != list.end(); it++)
    {
        TWifi wifi = *(TWifi*)(&*it);
        for(int i = ESSID_STATUS; i < ESSID_MAX; i++)
            m_model->setData(m_model->index(row, i), wifi[i]);
        row++;
    }
    m_model->submit();
}

void HNWIFIWidget::clickWIFI()
{
    QString name = m_model->data(m_model->index(currentIndex().row(), ESSID_NAME)).toString();
    QString encryt = m_model->data(m_model->index(currentIndex().row(), ESSID_ENCRYP)).toString();
    QString type = m_model->data(m_model->index(currentIndex().row(), ESSID_TYPE)).toString();
    QString mac = m_model->data(m_model->index(currentIndex().row(), ESSID_BSSID)).toString();

    HNEthManager::Instance()->setRefresh(false);
    do
    {
        if("YES" == encryt)
        {
            m_pass->setWifiName(name);
            if(HNPasswordDialog::Rejected == m_pass->exec())
                break;
        }

        bool ok = setCurrentWifi(mac, m_pass->wifiPwd());

        pline() << ok;

        if(!ok)
        {
            HNMsgBox::warning(this, tr("Password error"));
            break;
        }

        pline() << name << encryt << m_pass->wifiPwd();
    }while(0);
    HNEthManager::Instance()->setRefresh();
}

