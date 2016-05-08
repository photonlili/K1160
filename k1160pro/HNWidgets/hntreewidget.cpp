#include "hntreewidget.h"
#include "ui_hntreewidget.h"

HNTreeWidget::HNTreeWidget(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::HNTreeWidget)
{
    ui->setupUi(this);

    QUuid uuid;
    setObjectName(uuid.toString());

    m_fs = new HNFileSystem(this);
    m_model = new HNTreeModel(this, m_fs);
    setModel(m_model);

    QFont cloudFont = qApp->font();
    cloudFont.setPointSize(16);
    setFont(cloudFont);

    setEditTriggers(NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    //setColumnHidden(1, true);
    //setColumnHidden(2, true);
    //setColumnHidden(3, true);

    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));
}

HNTreeWidget::~HNTreeWidget()
{
    delete ui;
}

void HNTreeWidget::query(QString path)
{
    QString file;
    m_fs->parse(path, m_prot, file);
    m_model->query(path);
}

void HNTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!curIndex.isValid())
        return;

    //根据是否文件夹进行判断
    if(!parIndex.isValid())
    {
        QString path = m_model->index(curIndex.row(), 1).data().toString();
        pline() << m_prot << path;
        query(QString("%1%2").arg(m_prot).arg(path));
    }
    expand(curIndex);
}
