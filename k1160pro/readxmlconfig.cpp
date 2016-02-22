#include "readxmlconfig.h"

ReadXmlConfig::ReadXmlConfig()
{
    m_pFile = NULL;
    m_pDom = NULL;
/*
    QString strfilename = QString("config.xml");
    m_pFile = new QFile(strfilename);
    if(!m_pFile->open(QFile::ReadWrite ))
    {
        return;
    }

    m_pDom = new QDomDocument();

    if(!m_pDom->setContent(m_pFile))
    {
       m_pFile->close();
       return;
     }
 */
    m_ptc =  QTextCodec::codecForName("UTF-8");
}

ReadXmlConfig::~ReadXmlConfig()
{
    /*
    if(NULL != m_pFile)
    {
        delete m_pFile;
        m_pFile = NULL;
    }

    if(NULL != m_pDom)
    {
        delete m_pDom;
        m_pDom = NULL;
    }
    */
}

QString ReadXmlConfig::getValue(const QString &key, const QString &type)
{
  QString result = "";
  QDomNodeList nodelist = m_pDom->elementsByTagName(type);    /**< 读取类型节点集合 */

  for(int i=0; i<nodelist.count(); i++)
  {
    QDomNode node = nodelist.at(i);
    QDomNodeList itemlist = node.childNodes(); /**< 获取字节点集合 */

    for(int j=0; j<itemlist.count(); j++)
    {
      QDomNode mynode = itemlist.at(j);
      if(mynode.toElement().attribute("key") == key)
      { /**< 查找所需要的键值 */
        result = mynode.toElement().attribute("value");
        break;
      }
    }
  }
  return result;
}
MachineSetting ReadXmlConfig::readxml()
{
    MachineSetting ms;
    QDomDocument dom;
    QFile *file=new QFile("/opt/config.xml");
    if(file->open(QIODevice::ReadOnly))
      {
          dom.setContent(file);
      }

    QDomNodeList dingbiaoxishu = dom.elementsByTagName("dingbiaoxishu");
    ms.m_strfdingbiaoqishu = dingbiaoxishu.item(0).toElement().text();

    QDomNodeList zhusaibeng = dom.elementsByTagName("zhusaibeng");
    ms.m_strfzhusaibeng = zhusaibeng.item(0).toElement().text();

    QDomNodeList dayin = dom.elementsByTagName("dayin");
    ms.m_strbprinter = dayin.item(0).toElement().text();

    QDomNodeList zijian = dom.elementsByTagName("zijian");
    ms.m_strbzijian = zijian.item(0).toElement().text();

    QDomNodeList lengningshui = dom.elementsByTagName("lengningshui");
    ms.m_strblengningshui = lengningshui.item(0).toElement().text();

    QDomNodeList huansuan = dom.elementsByTagName("huansuan");
    ms.m_strbhuansuan = huansuan.item(0).toElement().text();

    QDomNodeList fangfaxishu = dom.elementsByTagName("fangfaxishu");
    ms.m_strffangfaxishu = fangfaxishu.item(0).toElement().text();
    return ms;
}

void ReadXmlConfig::writexml(MachineSetting *pmachinesetting)
{

    if(NULL == pmachinesetting)
    {
        return;
    }
    QString xmlName = "/opt/config.xml";
    QFile xmlfile(xmlName);

    if (!xmlfile.open(QFile::ReadWrite | QFile::Text))
    {
       return;
    }
    QDomDocument doc;
    QDomText text;
    QDomElement element;
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\'1.0\'");
    doc.appendChild(instruction);


    QDomElement general=doc.createElement("body");
    doc.appendChild(general);

    element=doc.createElement("dingbiaoxishu");
    text=doc.createTextNode(pmachinesetting->m_strfdingbiaoqishu);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("zhusaibeng");
    text=doc.createTextNode(pmachinesetting->m_strfzhusaibeng);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("dayin");
    text=doc.createTextNode(pmachinesetting->m_strbprinter);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("zijian");
    text=doc.createTextNode(pmachinesetting->m_strbzijian);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("lengningshui");
    text=doc.createTextNode(pmachinesetting->m_strblengningshui);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("huansuan");
    text=doc.createTextNode(pmachinesetting->m_strbhuansuan);
    element.appendChild(text);
    general.appendChild(element);

    element=doc.createElement("fangfaxishu");
    text=doc.createTextNode(pmachinesetting->m_strffangfaxishu);
    element.appendChild(text);
    general.appendChild(element);

    QTextStream out(&xmlfile);
    doc.save(out,4);
    xmlfile.close();
}
