#include "DocumentTypes.h"

Document::Document():
  m_CommonData(nullptr),m_Permissions(nullptr),m_VPreferences(nullptr)
{

}

Document::~Document()
{

}

QString Document::toString() const
{
    QString start="<ofd:Document xmlns:ofd=\"http://www.ofdspec.org\">",
            end= "</ofd:Document>";
    if(m_CommonData)
    start.append(m_CommonData->toString());
    start.append("<ofd:Pages>");
    for(int i=0;i<m_Pages.size();i++)
    {
        start.append(m_Pages[i]->toString());
    }
    start.append("</ofd:Pages>");
    if(!m_Outlines.isEmpty())
    {
         start.append("<ofd:Outlines>");
         for(int i=0;i<m_Outlines.size();i++)
         {
            start.append(m_Outlines.at(i)->toString());
         }
         start.append("</ofd:Outlines>");
    }
    if(m_Permissions)
    start.append(m_Permissions->toString());
    if(!m_Actions.isEmpty())
    {
         start.append("<ofd:Actions>");
         for(int i=0;i<m_Actions.size();i++)
         {
            start.append(m_Actions.at(i)->toString());
         }
         start.append("</ofd:Actions>");
    }
    if(m_VPreferences)
    start.append(m_VPreferences->toString());
    if(!m_Bookmarks.isEmpty())
    {
         start.append("<ofd:Bookmarks>");
         for(int i=0;i<m_Bookmarks.size();i++)
         {
            start.append(m_Bookmarks.at(i)->toString());
         }
         start.append("</ofd:Bookmarks>");
    }
    if(!m_Attachments.isEmpty())
    {
        start.append("<ofd:Attachments>");
        start.append(m_Attachments);
        start.append("</ofd:Attachments>");
    }
    if(!m_CustomTags.isEmpty())
    {
        start.append("<ofd:CustomTags>");
        start.append(m_CustomTags);
        start.append("</ofd:CustomTags>");
    }
    if(!m_Annotations.isEmpty())
    {
        start.append("<ofd:Annotations>");
        start.append(m_Annotations);
        start.append("</ofd:Annotations>");
    }
    if(!m_Extensions.isEmpty())
    {
        start.append("<ofd:Extensions>");
        start.append(m_Extensions);
        start.append("</ofd:Extensions>");
    }
    start.append(end);
    return start;
}

CT_CommonData::CT_CommonData():m_PageArea(nullptr),m_DefaultCS(-1)
{

}
CT_CommonData::~CT_CommonData()
{

}
QString CT_CommonData::toString()const
{
    QString start="<ofd:CommonData><MaxUnitID>",
            end= "</ofd:CommonData>";
    start.append(QString::number(m_MaxUnitID));
    start.append("</ofd:MaxUnitID>");
    if(m_PageArea)
    {
         start.append("<ofd:PageArea>");
         start.append(m_PageArea->toString());
         start.append("</ofd:PageArea>");
    }

    if(!m_PublicRes.isEmpty())
    {
         QString tem="<ofd:PublicRes>%1</ofd:PublicRes>";
        for(int i=0;i<m_PublicRes.size();i++)
        {
           start.append(tem.arg(m_PublicRes.at(i)));
        }
    }
    if(!m_DocumentRes.isEmpty())
    {
         QString tem="<ofd:DocumentRes>%1</ofd:DocumentRes>";
        for(int i=0;i<m_DocumentRes.size();i++)
        {
           start.append(tem.arg(m_DocumentRes.at(i)));
        }
    }
    if(!m_TemplatePage.isEmpty())
    {
        for(int i=0;i<m_TemplatePage.size();i++)
        {
           start.append(m_TemplatePage.at(i)->toString());
        }
    }
    if(m_DefaultCS>=0)
    {
        start.append("<ofd:DefaultCS>");
        start.append(m_DefaultCS);
        start.append("</ofd:DefaultCS>");
    }
    start.append(end);
    return start;

}
CT_Page::CT_Page():m_ID(-1){}
CT_Page::~CT_Page(){}
QString CT_Page::toString() const
{
   QString tem="<ofd:Page ID=\"%1\" BaseLoc=\"%2\"/>";
   if(m_ID!=-1)
   {
        return tem.arg(m_ID).arg(m_BaseLoc);
   }
   return "";
}

CT_OutlineElem::CT_OutlineElem():m_Count(0),m_Expanded(true)
{

}

CT_OutlineElem::~CT_OutlineElem()
{

}

QString CT_OutlineElem::toString() const
{
    if(m_Title.isEmpty())
        return "";
   QString start="<ofd:OutlineElem Title=\"%1\" Count=\"%2\" Expanded=\"%3\">",
            end= "</ofd:OutlineElem>";
   start= start.arg(m_Title).arg(m_Count).arg(BtoS(m_Expanded));
   if(!m_Actions.isEmpty())
   {
        start.append("<ofd:Actions>");
        for(int i=0;i<m_Actions.size();i++)
        {
            start.append(m_Actions.at(i)->toString());
        }
        start.append("</ofd:Actions>");
   }
   start.append(end);
   return start;
}


CT_Permission::CT_Permission():
m_Edit(true),m_Annot(true),m_Export(true),m_Signature(true),
m_Watermark(true),m_PrintScreen(true),m_Print(nullptr),m_ValidPeriod(nullptr)
{

}

CT_Permission::~CT_Permission()
{

}

QString CT_Permission::toString() const
{
    QString start="<ofd:Permission>"
                  "<ofd:Edit>%1</ofd:Edit>"
                  "<ofd:Annot>%2</ofd:Annot>"
                  "<ofd:Export>%3</ofd:Export>"
                  "<ofd:Signature>%4</ofd:Signature>"
                  "<ofd:Watermark>%5</ofd:Watermark>"
                  "<ofd:PrintScreen>%6</ofd:PrintScreen>"
                  "%7%8"
                  "</ofd:Permission>";

    return start.arg(BtoS(m_Edit)).arg(BtoS(m_Annot)).arg(BtoS(m_Export)).arg(BtoS(m_Signature))
            .arg(BtoS(m_Watermark)).arg(BtoS(m_PrintScreen)).arg(m_Print->toString()).arg(m_ValidPeriod->toString());
}

Print::Print():m_Printable(true),m_Copies(-1)
{

}

Print::~Print()
{

}

QString Print::toString() const
{
    return QString("<ofd:Print Copies=\"%1\" Printable=\"%2\"/>").arg(m_Copies).arg(BtoS(m_Printable));
}

ValidPeriod::ValidPeriod()
{

}

ValidPeriod::~ValidPeriod()
{

}

QString ValidPeriod::toString() const
{
     if(m_StartDate.isEmpty()&&m_EndDate.isEmpty())
     return "";
     return QString("<ofd:ValidPeriod StartDate=\"%1\" EndDate=\"%2\"/>").arg(m_StartDate).arg(m_EndDate);
}

CT_VPreferences::CT_VPreferences():m_PageMode("None"),m_PageLayout("OneColumn"),m_TabDisplay("DocTitle"),
m_HideToolbar(false),m_HideMenubar(false),m_HideWindowUI(false),m_ZoomMode("Default"),m_Zoom(0.0)
{

}

CT_VPreferences::~CT_VPreferences()
{

}

QString CT_VPreferences::toString() const
{
    QString start="<ofd:VPreferences>"
            "<ofd:PageMode>%1</ofd:PageMode>"
            "<ofd:PageLayout>%2</ofd:PageLayout>"
            "<ofd:TabDisplay>%3</ofd:TabDisplay>"
            "<ofd:HideToolbar>%4</ofd:HideToolbar>"
            "<ofd:HideMenubar>%5</ofd:HideMenubar>"
            "<ofd:HideWindowUI>%6</ofd:HideWindowUI>"
            "<ofd:ZoomMode>%7</ofd:ZoomMode>"
            "<ofd:Zoom>%8</ofd:Zoom>"
            "</ofd:VPreferences>";

    return start.arg(m_PageMode).arg(m_PageLayout).arg(m_TabDisplay).arg(m_HideToolbar).arg(m_HideMenubar)
            .arg(m_HideWindowUI).arg(m_ZoomMode).arg(m_Zoom);
}


CT_TemplatePage::CT_TemplatePage():m_ID(-1)
{

}

CT_TemplatePage::~CT_TemplatePage()
{

}

QString CT_TemplatePage::toString() const
{
    QString start="<ofd:TemplatePage ID=\"%1\" BaseLoc=\"%2\" ",
    end="/>";
    start=start.arg(m_ID).arg(m_BaseLoc);
    if(!m_Name.isEmpty())
    {
        start.append(QString("Name=\"%1\" ").arg(m_Name));
    }
    if(!m_ZOrder.isEmpty())
    {
        start.append(QString("ZOrder=\"%1\" ").arg(m_ZOrder));
    }
    start.append(end);
    if(m_ID>=0)
    {
        return start;
    }
    return "";
}


CT_Bookmark::CT_Bookmark():m_Dest(nullptr)
{

}

CT_Bookmark::~CT_Bookmark()
{

}

QString CT_Bookmark::toString() const
{
    QString start="<ofd:Bookmark Name=\"%1\">",
    end="</ofd:Bookmark>";
    start=start.arg(m_Name);
    return start.append(m_Dest->toString()).append(end);
}
