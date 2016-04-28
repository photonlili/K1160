#include "qdatafrom.h"
#include "ui_qdatafrom.h"
#include <QSqlDatabase>
#include <QMessageBox>
#ifdef _MIPS_LINUX_ENV_
#include <QPainter>
#else
#endif
#include <QSqlRecord>
#include "qmainscreen.h"
#include "qprinterform.h"


QDataFrom::QDataFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataFrom),
    strtable("data"),
    m_stronelinedata(""),
    m_querymodel(NULL),
    m_RemFileSize(0),
    m_bSendFileFalg(false),
    m_bDataDNOFalg(true),
    m_iIndex(0),
    m_iLen(0)
    //m_pPrinter(NULL)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");

  m_querymodel = new QSqlQueryModel(this);
  //  m_querymodel = new QSqlQueryCheckBoxModel(this);


    linstname.clear();
    linstvalues.clear();
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("/opt/Hanon/_Data");
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());
    m_pNetControl = pWidget->m_pNetControl;
    InitOCX();
    InitSings();
}

QDataFrom::~QDataFrom()
{
    delete ui;
}
void QDataFrom::Upfocus()
{
    ui->pb_data_pgup->setFocus();
}

void QDataFrom::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QDataFrom{image:url(:/images/bk/bk_clean.png)}""QDataFrom{background-color:transparent;}");

    //bt
    ui->pb_data_pgup->setFlat(true);
    ui->pb_data_pgup->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_pgup->setGeometry(94,558,108,44);
    ui->pb_data_pgup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");

    ui->pb_data_pgdn->setFlat(true);
    ui->pb_data_pgdn->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_pgdn->setGeometry(221,558,108,44);
    ui->pb_data_pgdn->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");

    ui->pb_data_printer->setFlat(true);
    ui->pb_data_printer->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_printer->setGeometry(348,558,108,44);
    ui->pb_data_printer->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_printer_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_printer_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_printer_press.png);}");

    ui->pb_data_delete->setFlat(true);
    //ui->pb_data_delete->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_delete->setGeometry(475,558,108,44);
    ui->pb_data_delete->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");

    ui->pb_data_export->setFlat(true);
    ui->pb_data_export->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_export->setGeometry(602,558,108,44);
    ui->pb_data_export->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_export_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_export_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_export_press.png);}");

    ui->pb_data_cloud->setFlat(true);
    ui->pb_data_cloud->setFocusPolicy(Qt::NoFocus);
    ui->pb_data_cloud->setGeometry(729,558,108,44);
    ui->pb_data_cloud->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_cloud_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_cloud_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_cloud_press.png);}");

    //lb
    ui->lb_clean_page->setGeometry(666, 525, 100, 24);
    ui->lb_clean_page->setFocusPolicy(Qt::NoFocus);
    ui->lb_clean_page->setText(m_ptc->toUnicode("00/00"));
    ui->lb_clean_page->setStyleSheet("QMLabel{background-color:transparent;}");

    //edit
    ui->le_clean_jump->setGeometry(821,525,58,24);
    ui->le_clean_jump->setFocusPolicy(Qt::NoFocus);
    ui->le_clean_jump->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/le_data_jump.png);}");

    //ui->le_clean_jump->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line.png);font-size:17px}");

    //m_ItemModel = new ListModel(this);
   //m_ItemModel->setColumnCount(9);
    //m_ItemModel->setRowCount(20);
    //m_ItemModel->setHorizontalHeaderLabels(QStringList()<< m_ptc->toUnicode("")<< m_ptc->toUnicode("序号") << m_ptc->toUnicode("样品名称") << m_ptc->toUnicode("样品编号") << m_ptc->toUnicode("样品量") << m_ptc->toUnicode("结果") << m_ptc->toUnicode("结果单位") << m_ptc->toUnicode("测试人") << m_ptc->toUnicode("测试时间"));

    //m_querymodel->setColumnCount(9);
    //m_querymodel->setRowCount(20);
    //m_querymodel->setHorizontalHeaderLabels(QStringList()<< m_ptc->toUnicode("")<< m_ptc->toUnicode("序号") << m_ptc->toUnicode("样品名称") << m_ptc->toUnicode("样品编号") << m_ptc->toUnicode("样品量") << m_ptc->toUnicode("结果") << m_ptc->toUnicode("结果单位") << m_ptc->toUnicode("测试人") << m_ptc->toUnicode("测试时间"));

    ui->tb_data->setAlternatingRowColors(true);
    ui->tb_data->setFocusPolicy(Qt::NoFocus);
    ui->tb_data->setGeometry(38, 41, 837, 474);
    //ui->tb_data->setStyleSheet("QTableView::item{background-color:rgb(255,255,255)}");//"QTableView::item{selection-background-color:rgb(255,149,13)}"

    /*ui->tb_data->verticalHeader()->hide();
    //ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_pici_param->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_data->setFrameShape(QFrame::NoFrame);
    ui->tb_data->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_data->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/opt/Hanon/_Data.db");
    if(!m_db.open()) return;

    ui->tb_data->setModel(m_querymodel);
    ui->tb_data->setSortingEnabled(false);

    m_icurrentpage = 1;
    m_itotalcount = GetTotalCount(strtable);
    m_itotalpage = GetPageCount();
    m_querymodel->setHeaderData(0,Qt::Horizontal, m_ptc->toUnicode("序号"));
    m_querymodel->setHeaderData(1,Qt::Horizontal, m_ptc->toUnicode("样品名称"));
    m_querymodel->setHeaderData(2,Qt::Horizontal, m_ptc->toUnicode("样品编号"));
    m_querymodel->setHeaderData(3,Qt::Horizontal, m_ptc->toUnicode("样品量"));
    m_querymodel->setHeaderData(4,Qt::Horizontal, m_ptc->toUnicode("结果"));
    m_querymodel->setHeaderData(5,Qt::Horizontal, m_ptc->toUnicode("结果单位"));
    m_querymodel->setHeaderData(6,Qt::Horizontal, m_ptc->toUnicode("测试人"));
    m_querymodel->setHeaderData(7,Qt::Horizontal, m_ptc->toUnicode("测试时间"));

    RecordQuery(0);
    ui->tb_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    //SetPageCount();
    UpdateStatus();

#ifdef _MIPS_LINUX_ENV_
    ui->tb_data->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_data->horizontalHeader()->setStretchLastSection(true);
#else
    ui->tb_data->horizontalHeader()->setStretchLastSection(true);
    ui->tb_data->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
/*
    ReadOnlyDelegate *preadonlydelegate = new ReadOnlyDelegate(this);
    TestDelegate *pTestDelegate = new TestDelegate(this);
    IDDelegate *pIDdelegate = new IDDelegate(this);
    //re *preadonlydelegate = new (this);
    ui->tb_data->setItemDelegateForColumn(0, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(1, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(2, preadonlydelegate);

    ui->tb_data->setItemDelegateForColumn(3, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(4, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(5, preadonlydelegate);

    ui->tb_data->setItemDelegateForColumn(6, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(7, preadonlydelegate);
    ui->tb_data->setItemDelegateForColumn(8, preadonlydelegate);
*/
}

void QDataFrom::InitSings()
{

}

int QDataFrom::GetTotalCount(QString &strTable)
{
    if(NULL != m_querymodel)
    {
        QString sql = QString("select * from ") + strTable;
        m_querymodel->setQuery(sql);
    }
    return m_querymodel->rowCount();
}


int QDataFrom::GetPageCount()
{
    return (m_itotalcount % m_epagecount == 0) ? (m_itotalcount / m_epagecount) : (m_itotalcount / m_epagecount + 1);
}

void QDataFrom::SetPageCount()
{
    QString szCurrentText = QString("%1/%2").arg(QString::number(m_icurrentpage)).arg(QString::number(m_itotalpage));
    ui->lb_clean_page->setText(szCurrentText);
}

void QDataFrom::RecordQuery(int ilimit)
{
    if(NULL != m_querymodel)
    {
        //QString sql = QString("select * from ") + strtable + QString(" limit ") + ilimit + QString(" , ") + m_epagecount;
       QString sql = QString("select * from %1 limit %2,%3").arg(strtable).arg(QString::number(ilimit)).arg(QString::number(m_epagecount));
        m_querymodel->setQuery(sql);
    }
}

void QDataFrom::on_pb_data_cloud_clicked()
{
/*
    if(true == pdataquery->opendatabase())
    {
        linstname.clear();
        linstvalues.clear();

        //linstname.append(m_ptc->toUnicode("id"));
        //linstname.append(m_ptc->toUnicode("xuhao"));
        linstname.append(m_ptc->toUnicode("yangpinmingcheng"));
        linstname.append(m_ptc->toUnicode("yangpinbianhao"));
        linstname.append(m_ptc->toUnicode("yangpinliang"));
        linstname.append(m_ptc->toUnicode("jieguo"));
        linstname.append(m_ptc->toUnicode("jieguodanwei"));
        linstname.append(m_ptc->toUnicode("ceshiren"));
        linstname.append(m_ptc->toUnicode("ceshishijian"));


       // linstvalues.append(m_ptc->toUnicode("1"));
        linstvalues.append(m_ptc->toUnicode("1"));
        linstvalues.append(m_ptc->toUnicode("001"));
        linstvalues.append(m_ptc->toUnicode("1.001"));
        linstvalues.append(m_ptc->toUnicode("14.001"));
        linstvalues.append(m_ptc->toUnicode("ml"));
        linstvalues.append(m_ptc->toUnicode("王栎旭"));
        linstvalues.append(m_ptc->toUnicode("2015.05.27"));
        pdataquery->insert(strtable, linstname, linstvalues);
    }
*/
    //RecordQuery(10);
    QMainScreen *pWidget = static_cast<QMainScreen *>(this->parent());

    if(true == pWidget->m_bwififlag)
    {
        if(true != m_bSendFileFalg)
        {

            if(false == m_pNetControl->m_bUserLogin)
            {
                QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户未登入，请检查wifi链接"), QMessageBox::Ok);
                return;
            }
            SendFileInfo();
        }
    }
    else
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("wifi未连接"), QMessageBox::Ok);
    }

 //   SendFileData();
}

void QDataFrom::on_pb_data_pgdn_clicked()
{
    int limitIndex = m_icurrentpage * m_epagecount;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/opt/Hanon/_Data.db");
    if(!m_db.open()) return;
    RecordQuery(limitIndex);
    m_icurrentpage += 1;
    m_db.close();
    UpdateStatus();

}

void QDataFrom::on_pb_data_pgup_clicked()
{
    int limitIndex = (m_icurrentpage - 2) * m_epagecount;
     m_db = QSqlDatabase::addDatabase("QSQLITE");
     m_db.setDatabaseName("/opt/Hanon/_Data.db");
    if(!m_db.open()) return;
    RecordQuery(limitIndex);
    m_icurrentpage -= 1;
    m_db.close();
    UpdateStatus();
}


void QDataFrom::UpdateStatus()
{
    //QString szCurrentText = QString("%1/%2").arg(QString::number(m_icurrentpage)).arg(QString::number(m_itotalpage));
    //ui->lb_clean_page->setText(szCurrentText);
    SetPageCount();
    if(1 == m_icurrentpage)
    {
        ui->pb_data_pgup->setEnabled(false);
        ui->pb_data_pgdn->setEnabled(true);
    }
    else if(m_icurrentpage == m_itotalpage)
    {
        ui->pb_data_pgup->setEnabled(true);
        ui->pb_data_pgdn->setEnabled(false);
    }
    else
    {
        ui->pb_data_pgup->setEnabled(true);
        ui->pb_data_pgdn->setEnabled(true);
    }

}

void QDataFrom::on_le_clean_jump_textEdited(const QString &arg1)
{
    //得到输入字符串
    QString szText = arg1;
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
     {
        QMessageBox::information(this, tr("提示"), tr("请输入数字"));
        return;
     }
      //是否为空
      if(szText.isEmpty())
      {
         QMessageBox::information(this, tr("提示"), tr("请输入跳转页面"));
         return;
      }
      //得到页数
      int pageIndex = szText.toInt();
      //判断是否有指定页
      if(pageIndex > m_itotalpage || pageIndex < 1)
      {
        QMessageBox::information(this, tr("提示"), tr("没有指定的页面，请重新输入"));
           return;
      }
      //得到查询起始行号
      int limitIndex = (pageIndex-1) * m_epagecount;
      m_db = QSqlDatabase::addDatabase("QSQLITE");
      m_db.setDatabaseName("/opt/Hanon/_Data.db");
     if(!m_db.open()) return;
      //记录查询
      RecordQuery(limitIndex);
      m_db.close();
      //设置当前页
      m_icurrentpage = pageIndex;
      //刷新状态
      UpdateStatus();
}

void QDataFrom::on_pb_data_export_clicked()
{

    QPrinter printerText;
    printerText.setOutputFormat(QPrinter::PdfFormat);

#ifdef _MIPS_LINUX_ENV_
     printerText.setOutputFileName("/opt/Hanon/data.pdf");
     //printerText.setOutputFileName("/mnt/usb_sda1/data.pdf");
#else
     printerText.setOutputFileName("/opt/Hanon/data.pdf");
#endif

#ifdef _MIPS_LINUX_ENV_
     QFontDatabase db;
     int fontId = db.addApplicationFont("/usr/lib/fonts/wenquanyi.ttf");
     QString wenquanyi = db.applicationFontFamilies ( fontId ).at(0);
     QFont font(wenquanyi,11);
#else
     QFontDatabase db;
     int fontId = db.addApplicationFont("/usr/lib/fonts/wenquanyi.ttf");
     QString wenquanyi = db.applicationFontFamilies ( fontId ).at(0);
     QFont font(wenquanyi,11);
#endif


    QPainter painterText;
    painterText.setFont(font);
    painterText.begin(&printerText);
    //QDateTime current_date_time = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");

    QPoint point(10, 10);
    int irow = m_querymodel->rowCount();


    for(int i = 0; i < irow; i++)
    {
        QSqlRecord strRecord= m_querymodel->record(i);
        //QString message = strRecord.value(0).toString();
        QString message = QString("       %1   %2               %3               %4               %5               %6               %7              %8").arg(QString::number(i)).arg(strRecord.value(0).toString()).arg(strRecord.value(1).toString()).arg(strRecord.value(02).toString()).arg(strRecord.value(3).toString()).arg(strRecord.value(4).toString()).arg(strRecord.value(5).toString()).arg(strRecord.value(06).toString());
        int y = point.y();
        point.setY(y + 40);
        painterText.drawText(point, message);
        message.clear();
    }

    //printer_text.newPage();  //生成新的一页，可继续插入
    painterText.end();

}

void QDataFrom::on_pb_data_delete_clicked()
{
    QMessageBox::StandardButton rb  = QMessageBox::question(this, m_ptc->toUnicode(""), m_ptc->toUnicode("是否删除数据"), QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        if(true == pdataquery->opendatabase())
        {
           QString strname = "id";
           QString sql = QString("delete from ") + strtable + QString(" where ") + strname + QString("='") + m_stronelinedata + QString("'");
           //QString sql = QString("select * from %1 limit %2,%3").arg(strtable).arg(QString::number(ilimit)).arg(QString::number(m_epagecount));
           m_querymodel->setQuery(sql);
           m_db = QSqlDatabase::addDatabase("QSQLITE");
           m_db.setDatabaseName("/opt/Hanon/_Data.db");
           if(!m_db.open()) return;
           RecordQuery(0);
           UpdateStatus();
           //SetSuyuan();
        }
    }

    if(rb == QMessageBox::No)
    {
        return;
    }


}

void QDataFrom::on_tb_data_clicked(const QModelIndex &index)
{
    QModelIndexList modellist = ui->tb_data->selectionModel()->selectedRows();
    m_stronelinedata = modellist[0].data().toString();
}

void QDataFrom::SetSuyuan()
{
    linstname.clear();
    linstvalues.clear();

    linstname.append("shiyanmingcheng");
    linstname.append("shanchushijian");
    linstname.append("shanchuren");

    linstvalues.append(m_stronelinedata);

    QDateTime dt = QDateTime::currentDateTime();

    QString strData =  dt.toString("yyyy-MM-dd hh:mm:ss ddd");

    linstvalues.append(strData);

    QMainScreen *p = (QMainScreen *) this->parent();
    QString strname =  p->GetUserName();

    linstvalues.append(strname);
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("/opt/Hanon/suyuan");

    QString str = "suyuan";
    if(true == pdataquery->opendatabase())
    {
        pdataquery->insert(str, linstname, linstvalues);
        pdataquery->cloesdatabase();
    }
}

void QDataFrom::SendFileInfo()
{
    QByteArray by;
    int iFileSize = 0;
    m_strFileList.append("/opt/Hanon/_Data.db");
    //m_strFileList= QFileDialog::getOpenFileNames( 0, "Select File(s)", QDir::homePath());
    QString strName = m_strFileList.at(0);

    int index = strName.lastIndexOf('\/');
    strName = strName.mid(index+1);
    QDateTime dt = QDateTime::currentDateTime();

    QString strTime =  dt.toString("yyyy-MM-dd hh:mm:ss");
    strName = "_Data_" + strTime + "_.db";
    QFile File(m_strFileList.at(0));
    iFileSize = File.size();
    by.clear();
    QString strData = "";
    strData = QString(NETCOMMANDDATASENDFILEINFO).arg("002").arg(strName).arg("TRUE").arg(iFileSize);
    by.append(strData);
    m_pNetControl->PackAndSendData(by,COMMANDSENDFILEINFO);
}

void QDataFrom::StartSendFile()
{
    QByteArray byTemp;
    QByteArray by;
    QString strNum = "";
    int TRANS_BYTES = 1024;
    int iAddress = 0;
    int iLen = 0;
    if(m_File.isOpen())
        m_File.close();

    int i = 0;
    QString strName = m_strFileList.at(0);
    m_File.setFileName(strName);

    for(int i = 0; i < 4; i++)
    {
        by.append(m_pNetControl->m_CommandFileID.at(i));
    }
    qDebug() << "StartSendFile";
    if(true == m_File.open(QIODevice::ReadOnly))
    {
        m_bSendFileFalg = true;
        m_RemFileSize = m_File.size() - m_RemFileSize;
       //while(m_RemFileSize > 0)
        {
            if(true == m_bDataDNOFalg)
            {
                m_bDataDNOFalg = false;
                by.clear();
                byTemp.clear();
                by.append(m_pNetControl->m_CommandFileID);
                by.append(m_pNetControl->GetDNOAndAddress(m_iIndex));
                by.append(m_pNetControl->GetDNOAndAddress(m_iLen));
                m_File.seek(m_File.size() - m_RemFileSize);
                byTemp = m_File.read(TRANS_BYTES);
                iLen = byTemp.size();
                by.append(m_pNetControl->GetDataLen(iLen));
                by.append(byTemp);
                m_iLen += iLen;
                m_RemFileSize -= TRANS_BYTES;
                m_iIndex++;
               m_pNetControl->PackAndSendData(by,COMMANDSENDFILEDATA);
            }
        }
        //m_bSendFileFalg = false;
    }
}

void QDataFrom::Senddata()
{
    QByteArray by;
    QByteArray byTemp;
    int TRANS_BYTES = 1024;
    int iLen = 0;
    qDebug() << "Senddata";
    if(true == m_bDataDNOFalg)
    {
        m_bDataDNOFalg = false;
        by.clear();
        byTemp.clear();
        by.append(m_pNetControl->m_CommandFileID);
        by.append(m_pNetControl->GetDNOAndAddress(m_iIndex));
        by.append(m_pNetControl->GetDNOAndAddress(m_iLen));
        m_File.seek(m_File.size() - m_RemFileSize);
        byTemp = m_File.read(TRANS_BYTES);
        iLen = byTemp.size();
        by.append(m_pNetControl->GetDataLen(iLen));
        by.append(byTemp);
        m_iLen += iLen;
        m_RemFileSize -= TRANS_BYTES;
        m_iIndex++;
       m_pNetControl->PackAndSendData(by,COMMANDSENDFILEDATA);
    }
}

void QDataFrom::on_le_clean_jump_textChanged(const QString &arg1)
{

}

void QDataFrom::on_pb_data_printer_clicked()
{
    QPrinterForm    *m_pPrinter = NULL;
    if(NULL == m_pPrinter)
    {
        m_pPrinter = new QPrinterForm(this);
    }
    else
    {
        delete m_pPrinter;
        m_pPrinter = NULL;
        m_pPrinter = new QPrinterForm(this);
    }
    m_pPrinter->setGeometry(50, 80, 805,325);
    m_pPrinter->show();

    /*
    system("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600x600 -sDEVICE=pbmraw -sOutputFile=Output.pbm Output.pdf \
           && foo2zjs -z3 -p9 -r600x600 Output.pbm > /dev/usb/lp0");
    */
}
