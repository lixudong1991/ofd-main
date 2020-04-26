#include "PageTypes.h"


Page::Page():
   m_Area(nullptr)
{

}

Page::~Page()
{

}

QString Page::toString() const
{
    QString start="<ofd:Page xmlns:ofd=\"http://www.ofdspec.org\">",
            end= "</ofd:Page>";

    if(m_Area)
    {
        start.append("<ofd:Area>");
        start.append(m_Area->toString());
        start.append("</ofd:Area>");
    }
    for(int i=0;i<m_Template.size();i++)
    {
       start.append(m_Template[i]->toString());
    }
    QString tem="<ofd:PageRes>%1</ofd:PageRes>";
    for(int i=0;i<m_PageRes.size();i++)
    {
       start.append(tem.arg(m_PageRes[i]));
    }
    if(m_Content.size()>0){
        start.append("<ofd:Content>");
        for(int i=0;i<m_Content.size();i++)
        {
           start.append(m_Content[i]->toString());
        }
        start.append("</ofd:Content>");
    }
    if(m_Actions.size()>0)
    {
        start.append("<ofd:Actions>");
        for(int i=0;i<m_Actions.size();i++)
        {
           start.append(m_Actions[i]->toString());
        }
        start.append("</ofd:Actions>");
    }
    start.append(end);
    return start;
}

Template::Template():m_TemplateID(-1),m_ZOrder("Background")
{

}

Template::~Template()
{

}

QString Template::toString() const
{
    if(m_TemplateID>=0)
        return QString("<ofd:Template TemplateID=\"%1\" ZOrder=\"%2\"/>").arg(m_TemplateID).arg(m_ZOrder);
    return "";
}

Layer::Layer():CT_PageBlock(),m_Type("Body"),m_ID(-1)
{

}

Layer::~Layer()
{

}

QString Layer::toString() const
{
    if(m_ID>=0)
    {
        QString start="<ofd:Layer>",
                end= "</ofd:Layer>";

    }
    return "";
}


CT_PageBlock::CT_PageBlock()
{

}

CT_PageBlock::~CT_PageBlock()
{

}

QString CT_PageBlock::toString() const
{
    return "";
}

CT_Pattern::CT_Pattern():
    m_CellContent(nullptr)
{

}

CT_Pattern::~CT_Pattern()
{

}

QString CT_Pattern::toString() const
{
    return "";
}

Segment::Segment():m_Color(nullptr)
{

}

Segment::~Segment()
{

}

QString Segment::toString() const
{
    return "";
}

CT_AxialShd::CT_AxialShd()
{

}

CT_AxialShd::~CT_AxialShd()
{

}

QString CT_AxialShd::toString() const
{
    return "";
}

CT_RadialShd::CT_RadialShd()
{

}

CT_RadialShd::~CT_RadialShd()
{

}

QString CT_RadialShd::toString() const
{
    return "";
}

Point::Point():m_Color(nullptr)
{

}

Point::~Point()
{

}

QString Point::toString() const
{
    return "";
}

CT_GouraudShd::CT_GouraudShd():m_BackColor(nullptr)
{

}

CT_GouraudShd::~CT_GouraudShd()
{

}

QString CT_GouraudShd::toString() const
{
    return "";
}

CT_LaGouraudShd::CT_LaGouraudShd():m_BackColor(nullptr)
{

}

CT_LaGouraudShd::~CT_LaGouraudShd()
{

}

QString CT_LaGouraudShd::toString() const
{
    return "";
}

CT_Color::CT_Color():
    m_Pattern(nullptr), m_AxialShd(nullptr), m_RadialShd(nullptr), m_GouraudShd(nullptr), m_LaGouraudShd(nullptr)
{

}

CT_Color::~CT_Color()
{

}

QString CT_Color::toString() const
{
    return "";
}

Area::Area():m_Path(nullptr),m_Text(nullptr)
{

}

Area::~Area()
{

}

QString Area::toString() const
{
    return "";
}

CT_Clip::CT_Clip()
{

}

CT_Clip::~CT_Clip()
{

}

QString CT_Clip::toString() const
{
    return "";
}

CT_GraphicUnit::CT_GraphicUnit()
{

}

CT_GraphicUnit::~CT_GraphicUnit()
{

}

QString CT_GraphicUnit::toString() const
{
    return "";
}

CT_Path::CT_Path():
    m_StrokeColor(nullptr),m_FillColor(nullptr)
{

}

CT_Path::~CT_Path()
{

}

QString CT_Path::toString() const
{
    return "";
}

TextCode::TextCode()
{

}

TextCode::~TextCode()
{

}

QString TextCode::toString() const
{
    return "";
}

CT_Text::CT_Text():
     m_FillColor(nullptr),m_StrokeColor(nullptr)
{

}

CT_Text::~CT_Text()
{

}

QString CT_Text::toString() const
{
    return "";
}

CT_CGTransform::CT_CGTransform()
{

}

CT_CGTransform::~CT_CGTransform()
{

}

QString CT_CGTransform::toString() const
{
    return "";
}

Border::Border()
{

}

Border::~Border()
{

}

QString Border::toString() const
{
    return "";
}

CT_Image::CT_Image()
{

}

CT_Image::~CT_Image()
{

}

QString CT_Image::toString() const
{

    return "";
}

CT_Composite::CT_Composite()
{

}

CT_Composite::~CT_Composite()
{

}

QString CT_Composite::toString() const
{
    return "";
}

CellContent::CellContent()
{

}

CellContent::~CellContent()
{

}

QString CellContent::toString() const
{
    return "";
}

PageBlock::PageBlock()
{

}

PageBlock::~PageBlock()
{

}

QString PageBlock::toString() const
{
    return "";
}
