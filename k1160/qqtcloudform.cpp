#include "qqtcloudform.h"
#include "qqtmsgbox.h"

QQTCloudForm::QQTCloudForm(QWidget *parent) :
    QWidget(parent)
{
    btnBack = new QQTPushButton(this);
    btnDelete = new QQTPushButton(this);
    btnSync = new QQTPushButton(this);
    //btnRefresh = new QQTPushButton(this);

    labelTitle = new QLabel(this);
    treeWidget = new QQTTreeWidget(this);
    m_pdlg =  new QQTProgressDialog(this);
    localDlg = new QQTLocalDBDialog(this);


    m_fs = treeWidget->fileSystem();

    connect(m_fs, SIGNAL(status(int)), this, SLOT(status(int)));
    connect(m_pdlg, SIGNAL(rejected()), this, SLOT(cancel()));

    connect(btnDelete, SIGNAL(clicked()), this, SLOT(DeleteCloudItem()));
    connect(btnBack, SIGNAL(clicked()), this, SLOT(UpDB()));
    connect(btnSync, SIGNAL(clicked()), this, SLOT(DownDB()));


    InitOCX();

}

void QQTCloudForm::queryRoot()
{
    treeWidget->query("htp://");
}

void QQTCloudForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QQTCloudForm{image:url(./skin/default/bk_net.png)}""QQTCloudForm{background-color:transparent;}");

    int btnH = 44;
    int btnW = 108;
    int btnX = 94;
    int btnXS = btnW + 148;
    int btnY = 588;

    btnSync->setFlat(true);
    btnSync->setFocusPolicy(Qt::NoFocus);
    btnSync->setGeometry(btnX + btnXS * 0, btnY,108,44);
    //btnBack->setStyleSheet("QPushButton{background-color:transparent;background-image: url(./skin/default/bt_down_normal.png)}""QPushButton:hover{background-image: url(./skin/default/bt_down_normal.png);}""QPushButton:pressed{background-image: url(./skin/default/bt_down_press.png);}");
    btnSync->iconTable().initNormal("./skin/default/bt_down_normal.png",
                                    "./skin/default/bt_down_press.png");

    btnDelete->setFlat(true);
    btnDelete->setFocusPolicy(Qt::NoFocus);
    btnDelete->setGeometry(btnX + btnXS * 1, btnY,108,44);
    //btnBack->setStyleSheet("QPushButton{background-color:transparent;background-image: url(./skin/default/bt_down_normal.png)}""QPushButton:hover{background-image: url(./skin/default/bt_down_normal.png);}""QPushButton:pressed{background-image: url(./skin/default/bt_down_press.png);}");
    btnDelete->iconTable().initNormal("./skin/default/bt_delete_normal.png",
                                      "./skin/default/bt_delete_press.png");

    btnBack ->setFlat(true);
    btnBack->setFocusPolicy(Qt::NoFocus);
    btnBack->setGeometry(btnX + btnXS * 2, btnY,108,44);
    //btnBack->setStyleSheet("QPushButton{background-color:transparent;background-image: url(./skin/default/bt_down_normal.png)}""QPushButton:hover{background-image: url(./skin/default/bt_down_normal.png);}""QPushButton:pressed{background-image: url(./skin/default/bt_down_press.png);}");
    btnBack->iconTable().initNormal("./skin/default/bt_cloud_normal.png",
                                    "./skin/default/bt_cloud_press.png");

    labelTitle->setGeometry(28,5,111,36);
    labelTitle->setText("云服务");
    labelTitle->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    treeWidget->setGeometry(38, 41, 837, 526);

}

void QQTCloudForm::DeleteCloudItem()
{
    QModelIndex curIndex = treeWidget->currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!parIndex.isValid())
    {
        QQTMsgBox::warning(this, "请选择文件");
        return;
    }

    int ret = QQTMsgBox::question(this, "确认删除此备份文件？");
    if(ret == QQTMsgBox::Rejected)
        return;

    treeWidget->removeRow();
}

void QQTCloudForm::UpDB()
{
    if(!m_fs->isOpen())
    {
        QQTMsgBox::warning(this, "当前云用户不在线，请重新切入页面连接");
        return;
    }

    localDlg->query();
    int ret = localDlg->exec();
    if(ret == QQTLocalDBDialog::Rejected)
        return;

    QString path, name ;
    localDlg->selectedItem(path, name);
    pline() << path << name;

    QQTTreeModel* m_model = (QQTTreeModel*)treeWidget->model();

    QModelIndex curIndex = treeWidget->currentIndex();
    QModelIndex parIndex = curIndex.parent();


    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString tmpName = time + "_" + name;
    QList<QStandardItem*> il = m_model->findItems(tmpName, Qt::MatchContains, FILE_NAME);

    int count = il.size() + 1;

    m_localfile = path + "/" + name;

    QString cloudPath;
    if(path.contains("Data"))
        cloudPath = "Data";
    else if(path.contains("Method"))
        cloudPath = "Method";

    m_cloudfile = cloudPath + "/" + QString("N%1-").arg(count) + time + "_" + name;

    m_srcPath = QString("%1%2").arg("local://").arg(m_localfile);

    QString dstPath = QString("%1%2").arg("htp://").arg(m_cloudfile);

    m_pdlg->setContent("正在备份......");
    m_pdlg->show();

    pline() << m_srcPath << dstPath ;
    pline() << m_cloudfile << m_localfile;
    m_fs->copy(m_srcPath, "local://tmp_up");
    m_fs->copy("local://tmp_up", dstPath);

}

void QQTCloudForm::DownDB()
{
    QQTTreeModel* m_model = (QQTTreeModel*)treeWidget->model();

    QModelIndex curIndex = treeWidget->currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!parIndex.isValid())
    {
        QQTMsgBox::warning(this, "请选择文件");
        return;
    }

    int ret = QQTMsgBox::question(this, "同步此文件将覆盖本地数据库，确认操作？");
    if(ret == QQTMsgBox::Rejected)
        return;

    QString path  = m_model->data(m_model->index(curIndex.row(), FILE_PATH, parIndex)).toString();
    QString file  = m_model->data(m_model->index(curIndex.row(), FILE_NAME, parIndex)).toString();

    QStringList fl = file.split("_");

    m_localfile = QString("db%1/%2").arg(path).arg(fl.at(1));

    m_cloudfile = path + "/" + file;


    m_srcPath = QString("%1%2").arg("htp://").arg(m_cloudfile);

    m_pdlg->setContent("正在同步......");
    m_pdlg->show();

    pline() << m_srcPath << m_cloudfile << m_localfile;
    m_fs->copy(m_srcPath, "local://tmp_down");

}

void QQTCloudForm::status(int arg1)
{
    m_pdlg->setValue(arg1);
    if(arg1 == 100)
    {
        m_pdlg->accept();;

        if(m_srcPath.contains("htp"))
        {
            pline() << "down ok" << m_localfile;
            //down
            system(QString("mv -f tmp_down %1")
                   .arg(m_localfile)
                   .toAscii().data());
            system(QString("rm -f tmp_down")
                   .toAscii().data());
            emit downSucc();
        }
        else
        {
            pline() << "up ok" << m_cloudfile;
            system(QString("rm -f tmp_up")
                   .toAscii().data());
        }

    }
}

void QQTCloudForm::cancel()
{
    m_fs->cancel();
    //clear
    if(m_srcPath.contains("htp"))
        system("rm -f tmp_down");
    else
        system("rm -f tmp_up");
}

