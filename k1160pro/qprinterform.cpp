#include "qprinterform.h"
#include "ui_qprinterform.h"
#include "readxmlconfig.h"
#ifdef _MIPS_LINUX_ENV_
#include <QPainter>
#else
#include <QtPrintSupport>
#endif
#include <QSqlRecord>
#include <QDateTime>
#include <sys/stat.h>



QPrinterForm::QPrinterForm(QWidget *parent) :
    QWidget(parent),
    m_pDataFrom(NULL),
    pdataquery(NULL),
    strtable("method"),
    ui(new Ui::QPrinterForm)
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("/opt/Hanon/method");
    linstvalues.clear();
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    m_bpsd = true;
    m_bbsd = true;
    m_pDataFrom =  static_cast<QDataFrom*>(this->parent());
    ui->lineEdit->setText(m_ptc->toUnicode("海能仪器K1160全自动凯氏定氮仪实验报告"));
    ui->lineEdit_2->setText(m_ptc->toUnicode(""));
    ui->lineEdit_3->setText(m_ptc->toUnicode(""));
    connect(this,SIGNAL(emitfocus()),parent,SLOT(Upfocus()));
}

QPrinterForm::~QPrinterForm()
{
    delete ui;
}


void QPrinterForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("QWidget#QPrinterForm{image:url(:/images/bk/bk_printer.png)}""QPrinterForm{background-color:transparent;}");

    //edit
    ui->lineEdit->setGeometry(30,24,750, 43);
    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");

    ui->lineEdit_2->setGeometry(30, 79, 750, 43);
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");

    ui->lineEdit_3->setGeometry(30, 134, 750, 43);
    ui->lineEdit_3->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/bt_le_sobig.png);font-size:17px}");

    //bt
    ui->pushButton_back->setFlat(true);
    //ui->pushButton_back->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_back->setGeometry(505,250,144,48);
    ui->pushButton_back->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_back_big_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_back_big_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_back_big_press.png);}");

    ui->pushButton_start->setFlat(true);
    //ui->pushButton_start->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_start->setGeometry(652,250,144,48);
    ui->pushButton_start->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_start_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_start_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_start_press.png);}");

    //label
    m_pLbpsd = new QMLabel(this);
    //m_pLbpsd->setGeometry(35,197,39, 39);
    //m_pLbpsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");

    m_pLbbsd = new QMLabel(this);
    //m_pLbbsd->setGeometry(121,197,39, 39);
    m_pLbbsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
/*
    ui->lb_printer_psd->setGeometry(75, 200, 150, 30);
    ui->lb_printer_psd->setText(m_ptc->toUnicode("PSD"));
    ui->lb_printer_psd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_printer_bsd->setGeometry(161, 200, 150, 30);
    ui->lb_printer_bsd->setText(m_ptc->toUnicode("BSD"));
    ui->lb_printer_bsd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
*/
    ui->lb_printer_psd->hide();
    ui->lb_printer_bsd->hide();
    ReadXmlConfig xmlconfig;

    m_machinesetting = xmlconfig.readxml();
}

void QPrinterForm::InitSings()
{
    connect(m_pLbpsd, SIGNAL(clicked()), this, SLOT(psd()));
    connect(m_pLbbsd, SIGNAL(clicked()), this, SLOT(bsd()));

}

void QPrinterForm::psd()
{
    if(true == m_bpsd)
     {
        m_pLbpsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bpsd = false;
     }
     else
     {
        m_pLbpsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bpsd = true;
     }
}

void QPrinterForm::bsd()
{
    if(true == m_bbsd)
     {
        m_pLbbsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_press.png);}");
        m_bbsd = false;
     }
     else
     {
        m_pLbbsd->setStyleSheet("QLabel{background-color:transparent;}""QLabel{background-image: url(:/images/bt/bt_check_normal.png);}");
        m_bbsd = true;
     }
}

void QPrinterForm::on_pushButton_back_clicked()
{
    //emit emitfocus();

    this->close();
}
bool QPrinterForm::CreatPdfTatil(QString &message, QString &message1, QString &message2)
{
    QStringList title;
#ifdef _MIPS_LINUX_ENV_
    title.push_back(m_ptc->toUnicode("序号"));
    title.push_back(m_ptc->toUnicode("样品名称"));
    title.push_back(m_ptc->toUnicode("样品编号"));
    title.push_back(m_ptc->toUnicode("样品量"));
    title.push_back(m_ptc->toUnicode("结果"));
    title.push_back(m_ptc->toUnicode("单位"));
    title.push_back(m_ptc->toUnicode("测试人"));
    title.push_back(m_ptc->toUnicode("测试时间"));
#else
    title.push_back(QStringLiteral("序号"));
    title.push_back(QStringLiteral("样品名称"));
    title.push_back(QStringLiteral("样品编号"));
    title.push_back(QStringLiteral("样品量"));
    title.push_back(QStringLiteral("结果"));
    title.push_back(QStringLiteral("单位"));
    title.push_back(QStringLiteral("测试人"));
    title.push_back(QStringLiteral("测试时间"));
#endif

    linstvalues.clear();
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->cloesdatabase();
    QString strname = "mingcheng";
    QString str = linstvalues.at(0);
    linstvalues.clear();
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strname, str, 13);
        pdataquery->cloesdatabase();
    }

    QPrinter printer_html(QPrinter::HighResolution);
    printer_html.setColorMode(QPrinter::Color);
    printer_html.setFullPage(true);
    printer_html.setPageSize(QPrinter::A4);
    printer_html.setOrientation(QPrinter::Portrait);
    printer_html.setOutputFormat(QPrinter::PdfFormat);
    printer_html.setOutputFileName("/opt/Hanon/data.pdf");

    QString html;
    if(!message.isEmpty())
    {
        html += "<h3 align=\"center\">" + message + "</h3>";
    }

    if(!message1.isEmpty())
    {
        html += "<h3 align=\"center\">" + message1 + "</h3>";
    }


    if(!message2.isEmpty())
    {
        html += "<h3 align=\"center\">" + message2 + "</h3>";
    }


#ifdef _MIPS_LINUX_ENV_
    html += "<h4 align=\"left\">" + m_ptc->toUnicode("测试参数") + "</h4>";
    html += QString(m_ptc->toUnicode("硼酸 %1[mL]")).arg(linstvalues.at(3));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString(m_ptc->toUnicode("稀释水 %1[mL]")).arg(linstvalues.at(4));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString(m_ptc->toUnicode("碱液 %1[mL]")).arg(linstvalues.at(5));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += "<br />";
    html += "<br />";
    html += QString(m_ptc->toUnicode("蒸馏 %1[mL/S]")).arg(linstvalues.at(6));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString(m_ptc->toUnicode("滴定方式 %1[mL/S]")).arg(linstvalues.at(8));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString(m_ptc->toUnicode("加碱方式 %1[mL/S]")).arg(linstvalues.at(9));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += "<br />";
    html += "<br />";
    html += QString(m_ptc->toUnicode("蒸汽流量 %1%")).arg(linstvalues.at(10));
    html += "<br />";
    //html += QString("空白体积 %1[mL]         <th>滴定酸 %2[moL/L]</th>           <th>蛋白系数 %3</th>");
    html += "<br />";
    html += "<h4 align=\"left\">" + m_ptc->toUnicode("测试结果") + "</h4>";
    html += "<table width=\"1000\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;\" bordercolor=\"gray\">";
#else
    html += "<h4 align=\"left\">" + QStringLiteral("测试参数") + "</h4>";
    html += QString("硼酸 %1[mL]").arg(linstvalues.at(3));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString("稀释水 %1[mL]").arg(linstvalues.at(4));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString("碱液 %1[mL]").arg(linstvalues.at(5));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += "<br />";
    html += "<br />";
    html += QString("蒸馏 %1[mL/S]").arg(linstvalues.at(6));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString("滴定方式 %1[mL/S]").arg(linstvalues.at(8));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += QString("加碱方式 %1[mL/S]").arg(linstvalues.at(9));
    html += "<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
    html += "<br />";
    html += "<br />";
    html += QString("蒸汽流量 %1%").arg(linstvalues.at(10));
    html += "<br />";
    //html += QString("空白体积 %1[mL]         <th>滴定酸 %2[moL/L]</th>           <th>蛋白系数 %3</th>");
    html += "<br />";
    html += "<h4 align=\"left\">" + QStringLiteral("测试结果") + "</h4>";
    html += "<table width=\"680\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;\" bordercolor=\"gray\">";
#endif
       html += "<tr style=\"background-color:gray\">";
    //html += "<tr>";
    for(int i = 0; i < title.count(); i++)
    {
        html += QString("<th>%1</th>").arg(title.at(i));
    }
    html += "</tr>";

    for(int j = 0; j < 20; j++)
    {
        html += "<tr>";
        QSqlRecord strRecord= m_pDataFrom->m_querymodel->record(j);
        html += QString("<td>%1</td>").arg(strRecord.value(0).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(1).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(2).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(3).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(4).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(5).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(6).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(7).toString());
        html += "</tr>";
    }

    html += "</table>";

    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";

#ifdef _MIPS_LINUX_ENV_
    html += "<h6 align=\"right\">" + m_ptc->toUnicode("打印人:__________打印时间:__________") + "</h6>";
#else
    html += "<h6 align=\"right\">" + QStringLiteral("打印人:__________打印时间:__________") + "</h6>";
#endif

    QTextDocument text_document;
    text_document.setHtml(html);
    text_document.print(&printer_html);
    text_document.end();
    return true;
}

bool QPrinterForm::CreatPdf(QString &message, QString &message1, QString &message2)
{
    QStringList title;
#ifdef _MIPS_LINUX_ENV_
    title.push_back(m_ptc->toUnicode("序号"));
    title.push_back(m_ptc->toUnicode("样品名称"));
    title.push_back(m_ptc->toUnicode("样品编号"));
    title.push_back(m_ptc->toUnicode("样品量"));
    title.push_back(m_ptc->toUnicode("结果"));
    title.push_back(m_ptc->toUnicode("单位"));
    title.push_back(m_ptc->toUnicode("测试人"));
    title.push_back(m_ptc->toUnicode("测试时间"));
#else
    title.push_back(QStringLiteral("序号"));
    title.push_back(QStringLiteral("样品名称"));
    title.push_back(QStringLiteral("样品编号"));
    title.push_back(QStringLiteral("样品量"));
    title.push_back(QStringLiteral("结果"));
    title.push_back(QStringLiteral("单位"));
    title.push_back(QStringLiteral("测试人"));
    title.push_back(QStringLiteral("测试时间"));
#endif

    QPrinter printer_html(QPrinter::HighResolution);
    printer_html.setColorMode(QPrinter::Color);
    printer_html.setFullPage(true);
    printer_html.setPageSize(QPrinter::A4);
    printer_html.setOrientation(QPrinter::Portrait);
    printer_html.setOutputFormat(QPrinter::PdfFormat);
    printer_html.setOutputFileName("/opt/Hanon/data.pdf");

    QString html;
    if(!message.isEmpty())
    {
        html += "<h3 align=\"center\">" + message + "</h3>";
    }

    if(!message1.isEmpty())
    {
        html += "<h3 align=\"center\">" + message1 + "</h3>";
    }


    if(!message2.isEmpty())
    {
        html += "<h3 align=\"center\">" + message2 + "</h3>";
    }
#ifdef _MIPS_LINUX_ENV_
    html += "<h4 align=\"left\">" + m_ptc->toUnicode("测试结果") + "</h4>";
    html += "<table width=\"1000\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;\" bordercolor=\"gray\">";
#else
    html += "<h4 align=\"left\">" + QStringLiteral("测试结果") + "</h4>";
    html += "<table width=\"680\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;\" bordercolor=\"gray\">";
#endif
       html += "<tr style=\"background-color:gray\">";
    //html += "<tr>";
    for(int i = 0; i < title.count(); i++)
    {
        html += QString("<th>%1</th>").arg(title.at(i));
    }
    html += "</tr>";

    for(int j = 0; j < 20; j++)
    {
        html += "<tr>";
        QSqlRecord strRecord= m_pDataFrom->m_querymodel->record(j);
        html += QString("<td>%1</td>").arg(strRecord.value(0).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(1).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(2).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(3).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(4).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(5).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(6).toString());
        html += QString("<td>%1</td>").arg(strRecord.value(7).toString());
        html += "</tr>";
    }

    html += "</table>";

    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";
    html += "<br />";

#ifdef _MIPS_LINUX_ENV_
    html += "<h6 align=\"right\">" + m_ptc->toUnicode("打印人:__________打印时间:__________") + "</h6>";
#else
    html += "<h6 align=\"right\">" + QStringLiteral("打印人:__________打印时间:__________") + "</h6>";
#endif

    QTextDocument text_document;
    text_document.setHtml(html);
    text_document.print(&printer_html);
    text_document.end();
    return true;
}

void QPrinterForm::on_pushButton_start_clicked()
{
    QString str1 = "";
    QString str2 = "";
    QString str3 = "";

    str1 = ui->lineEdit->text();
    str2 = ui->lineEdit_2->text();
    str3 = ui->lineEdit_3->text();

   QString str =  m_machinesetting.m_strbprinter;

   int iFlag = str.toInt();

   if(0 == iFlag)
   {
       if(true == CreatPdf(str1, str2, str3))
       {
           bool bflag = true;
           int i = 0;
           while (bflag) {

               if(5000 == i)
               {
                  bflag = false;
               }
               i++;
           }

            system("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600x600 -sDEVICE=pbmraw -sOutputFile=data.pbm /opt/Hanon/data.pdf \
                  && foo2zjs -z3 -p9 -r600x600 data.pbm > /dev/usb/lp0");

       }
   }
   else
   {
       if(true == CreatPdfTatil(str1, str2, str3))
       {
           bool bflag = true;
           int i = 0;
           while (bflag) {

               if(5000 == i)
               {
                  bflag = false;
               }
               i++;
           }

            system("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600x600 -sDEVICE=pbmraw -sOutputFile=data.pbm /opt/Hanon/data.pdf \
                  && foo2zjs -z3 -p9 -r600x600 data.pbm > /dev/usb/lp0");

       }
   }



    /*
    QString str1 = "";
    QString str2 = "";
    QString str3 = "";
    QString strMessage = "";
    str1 = ui->lineEdit->text();
    str2 = ui->lineEdit_2->text();
    str3 = ui->lineEdit_3->text();

    if((str1.isEmpty()) && (str2.isEmpty())&&(str3.isEmpty()))
    {
        if(true == CreatPdf(str1, str2, str3))
        {

             system("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600x600 -sDEVICE=pbmraw -sOutputFile=data.pbm /opt/Hanon/data.pdf \
                   && foo2zjs -z3 -p9 -r600x600 data.pbm > /dev/usb/lp0");

        }
    }

    if(!str1.isEmpty())
    {
        strMessage += str1;
    }

    if(!str2.isEmpty())
    {
         strMessage += str2;
    }

    if(!str3.isEmpty())
    {
         strMessage += str3;
    }

    if(false == m_bpsd)
    {

    }

    if(false == m_bbsd)
    {

    }

    if(true == CreatPdf(str1, str2, str3))
    {

        system("gs -q -dBATCH -dSAFER -dQUIET -dNOPAUSE -sPAPERSIZE=a4 -r600x600 -sDEVICE=pbmraw -sOutputFile=data.pbm /opt/Hanon/data.pdf \
               && foo2zjs -z3 -p9 -r600x600 data.pbm > /dev/usb/lp0");

    }
    */
}
