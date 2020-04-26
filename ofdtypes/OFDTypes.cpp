#include "OFDTypes.h"

OFD::OFD():m_Version("1.0"),m_DocType("OFD")
{

}

OFD::~OFD()
{

}

QString OFD::toString() const
{
    QString start="<ofd:OFD DocType=\"OFD\" Version=\"1.0\" xmlns:ofd=\"http://www.ofdspec.org\">",
            end= "</ofd:OFD>";
    for(int i=0;i<m_DocBody.size();i++)
    {
        start.append(m_DocBody.at(i)->toString());
    }
    start.append(end);
    return start;
}

DocBody::DocBody():m_DocInfo(nullptr),m_Signatures("")
{

}

DocBody::~DocBody()
{

}

QString DocBody::toString() const
{
    QString start="<ofd:DocBody>",
            end= "</ofd:DocBody>";
    start.append(m_DocInfo->toString());
    start.append("<ofd:DocRoot>");
    start.append(m_DocRoot);
    start.append("</ofd:DocRoot>");
    if(!m_Versions.isEmpty())
    {
        start.append("<ofd:Versions>");
        for(int i=0;i<m_Versions.size();i++)
        {
             start.append(m_Versions.at(i)->toString());
        }
        start.append("</ofd:Versions>");
    }
    if(!m_Signatures.isEmpty())
    {
        start.append("<ofd:Signatures>");
        start.append(m_Signatures);
        start.append("</ofd:Signatures>");
    }
    start.append(end);
    return start;
}

CT_DocInfo::CT_DocInfo():m_DocUsage("Normal")
{

}

CT_DocInfo::~CT_DocInfo()
{

}

QString CT_DocInfo::toString() const
{
    QString start="<ofd:DocInfo>",
            end= "</ofd:DocInfo>";
   start.append("<ofd:DocID>");
   start.append(m_DocID);
   start.append("</ofd:DocID>");
   if(!m_Title.isEmpty())
   {
       start.append("<ofd:Title>");
       start.append(m_Title);
       start.append("</ofd:Title>");
   }
   if(!m_Author.isEmpty())
   {
       start.append("<ofd:Author>");
       start.append(m_Author);
       start.append("</ofd:Author>");
   }
   if(!m_Subject.isEmpty())
   {
       start.append("<ofd:Subject>");
       start.append(m_Subject);
       start.append("</ofd:Subject>");
   }
   if(!m_Abstract.isEmpty())
   {
       start.append("<ofd:Abstract>");
       start.append(m_Abstract);
       start.append("</ofd:Abstract>");
   }
   if(!m_CreationDate.isEmpty())
   {
       start.append("<ofd:CreationDate>");
       start.append(m_CreationDate);
       start.append("</ofd:CreationDate>");
   }
   if(!m_ModDate.isEmpty())
   {
       start.append("<ofd:ModDate>");
       start.append(m_ModDate);
       start.append("</ofd:ModDate>");
   }
   if(!m_DocUsage.isEmpty())
   {
       start.append("<ofd:DocUsage>");
       start.append(m_DocUsage);
       start.append("</ofd:DocUsage>");
   }
   if(!m_Cover.isEmpty())
   {
       start.append("<ofd:Cover>");
       start.append(m_Cover);
       start.append("</ofd:Cover>");
   }
   if(!m_Keywords.isEmpty())
   {
       start.append("<ofd:Keywords>");
       QString tem="<ofd:Keyword>%1</ofd:Keyword>";
       for(int i=0;i<m_Keywords.size();i++)
       {
            start.append(tem.arg(m_Keywords.at(i)));
       }
       start.append("</ofd:Keywords>");
   }
   if(!m_Creator.isEmpty())
   {
       start.append("<ofd:Creator>");
       start.append(m_Creator);
       start.append("</ofd:Creator>");
   }
   if(!m_CreatorVersion.isEmpty())
   {
       start.append("<ofd:CreatorVersion>");
       start.append(m_CreatorVersion);
       start.append("</ofd:CreatorVersion>");
   }
   if(!m_CustomDatas.isEmpty())
   {
       start.append("<ofd:CustomDatas>");
       for(int i=0;i<m_CustomDatas.size();i++)
       {
           start.append(m_CustomDatas.at(i)->toString());
       }
       start.append("</ofd:CustomDatas>");
   }
   start.append(end);
   return start;
}
CustomData::CustomData()
{

}

CustomData::~CustomData()
{

}

QString CustomData::toString() const
{
    QString start="<ofd:CustomData Name=\"%1\">%2</ofd:CustomData>";
    if(!m_Name.isEmpty()&&!m_Value.isEmpty())
    {
      return start.arg(m_Name).arg(m_Value);
    }
    return "";
}

Version::Version():m_Current(false)
{

}

Version::~Version()
{

}

QString Version::toString() const
{
    QString start="<ofd:Version ID=\"%1\" Index=\"%2\" BaseLoc=\"%3\" ",
            end= "/>";
    start=start.arg(m_ID).arg(m_Index).arg(m_BaseLoc);
    if(m_Current)
       start.append("Current=\"true\"");
    else
       start.append("Current=\"false\"");
    start.append(end);
    return start;
}

