#include "qqtuserinfowidget.h"
#include "ui_qqtuserinfowidget.h"
#include "qqtmsgbox.h"
#include "qqtdefine.h"
#include "qqtgui-qt.h"

QQTUserInfoWidget::QQTUserInfoWidget(QWidget *parent) :
    QQTTableView(parent),
    ui(new Ui::QQTUserInfoWidget)
{
    ui->setupUi(this);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(false);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif

    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    setShowGrid(true);

    m_dg = new QQTUserInfoViewTextDelegate(this);
    setItemDelegateForColumn(Auth_Id, m_dg);

    m_model = new QQTTableModel(this, managerDB);
    m_model->setTable(TABLE_USERINFO);
    m_model->setRelation(Auth_Authrity, QSqlRelation(TABLE_AUTHORITY, "id", "Authority"));

    setModel(m_model);
    //setItemDelegate(new QSqlRelationalDelegate(this));

    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_mapper->setModel(m_model);
    m_mapper->setItemDelegate(new QSqlRelationalDelegate(this));

    connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentItemChanged(QModelIndex,QModelIndex)));
}

QQTUserInfoWidget::~QQTUserInfoWidget()
{
    delete ui;
}

void QQTUserInfoWidget::refresh()
{
    //model->setFilter(QString("Name = Library"));
    m_model->select();
    //显示默认登陆
    //setColumnHidden(Auth_Id, true);
    setColumnHidden(Auth_Name, false);
    setColumnHidden(Auth_Passwd, true);
    setColumnHidden(Auth_Authrity, false);
    setColumnHidden(Auth_Creater, true);
    setColumnHidden(Auth_CreateTime, true);
    setColumnHidden(Auth_Comment, true);
}

void QQTUserInfoWidget::selectUser(int id)
{
    selectRow(id);
    setFocus(Qt::MouseFocusReason);
}

void QQTUserInfoWidget::selectUser(QString userName)
{
    for(int i = 0; i < m_model->rowCount(); i++)
    {
        if(m_model->record(i).value(Auth_Name).toString() == userName)
        {
            selectUser(i);
            return;
        }
    }
}

QString QQTUserInfoWidget::currentUser()
{
    QModelIndex index = currentIndex();
    return m_model->record(index.row()).value(Auth_Name).toString();
}

QString QQTUserInfoWidget::currentUserAuthority()
{
    QModelIndex index = currentIndex();
    return m_model->record(index.row()).value(Auth_Authrity).toString();
}

QString QQTUserInfoWidget::currentUserPassword()
{
    QModelIndex index = currentIndex();
    return m_model->record(index.row()).value(Auth_Passwd).toString();
}

void QQTUserInfoWidget::setUserName(QString newName)
{
    QModelIndex index = currentIndex();
    m_model->setData(index, newName);
    m_model->submit();

    //xuanzhong
    selectUser(index.row());
}

void QQTUserInfoWidget::initLanguage()
{
    m_model->setHeaderData(Auth_Id, Qt::Horizontal, tr("DefaultLogin"));
    m_model->setHeaderData(Auth_Name, Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(Auth_Authrity, Qt::Horizontal, tr("Authority"));
}

void QQTUserInfoWidget::newUser(QString name, QString pwd, QString auth, QString comt)
{
    /*
    QString name = tr("New User");

    int count = 0;
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT COUNT(*) FROM User WHERE Name like '%%1%'").arg(name));
    if(query.next())
        count = query.record().value(0).toInt();
    query.finish();

    if(count > 0)
        name += QString(" (%1)").arg(count);
    */

    int row = 0;
    m_model->insertRow(row);
    m_model->setData(m_model->index(row, Auth_Name), name);
    m_model->setData(m_model->index(row, Auth_Passwd), pwd);
    if(auth == "Manager")
        m_model->setData(m_model->index(row, Auth_Authrity), 1);
    if(auth == "User")
        m_model->setData(m_model->index(row, Auth_Authrity), 2);
    m_model->setData(m_model->index(row, Auth_Creater), gUserName);
    m_model->setData(m_model->index(row, Auth_CreateTime), QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    m_model->setData(m_model->index(row, Auth_Comment), comt);
    m_model->submit();

    //初始化完成表格之后，选中db，激发changed消息，method和stage初始化才会成功。
    selectUser(name);
}

void QQTUserInfoWidget::delUser()
{
    QModelIndex index = currentIndex();
    m_model->removeRow(index.row());
    m_model->submit();
    selectUser(index.row()-1);
}

void QQTUserInfoWidget::updateMap()
{
    QModelIndex index = currentIndex();
    m_mapper->setCurrentModelIndex(index);
}

void QQTUserInfoWidget::saveMap()
{
    m_mapper->submit();
}

void QQTUserInfoWidget::currentItemChanged(QModelIndex cur, QModelIndex prev)
{
    if(cur.column() != Auth_Id)
        return;

    int dl = cur.data().toInt();

    QSettings set;
    int id = set.value("DefaultLogin").toInt();
    selectRow(id);
    set.setValue("DefaultLogin", dl);
    set.sync();

    selectRow(dl);
    pline() << id << dl;
    //update();
}


void QQTUserInfoViewTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QSettings set;
    QString id = set.value("DefaultLogin").toString();

    if(id == text)
        painter->drawImage(rect, QImage("://theme/basic/bk_sel.png"));
}
