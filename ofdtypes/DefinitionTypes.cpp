#include "DefinitionTypes.h"

CT_PageArea::CT_PageArea()
{

}

CT_PageArea::~CT_PageArea()
{

}

QString CT_PageArea::toString() const
{
    QString start="<ofd:PhysicalBox>%1 %2 %3 %4</ofd:PhysicalBox>";
    start= start.arg(m_PhysicalBox.x()).arg(m_PhysicalBox.y()).arg(m_PhysicalBox.width()).arg(m_PhysicalBox.height());
    if(m_ApplicationBox.isValid())
        start.append(QString("<ofd:ApplicationBox>%1 %2 %3 %4</ofd:ApplicationBox>").arg(m_ApplicationBox.x()).arg(m_ApplicationBox.y()).arg(m_ApplicationBox.width()).arg(m_ApplicationBox.height()));
    if(m_ContentBox.isValid())
        start.append(QString("<ofd:ContentBox>%1 %2 %3 %4</ofd:ContentBox>").arg(m_ContentBox.x()).arg(m_ContentBox.y()).arg(m_ContentBox.width()).arg(m_ContentBox.height()));
    if(m_BleedBox.isValid())
       start.append(QString("<ofd:BleedBox>%1 %2 %3 %4</ofd:BleedBox>").arg(m_BleedBox.x()).arg(m_BleedBox.y()).arg(m_BleedBox.width()).arg(m_BleedBox.height()));
    return start;
}

CT_Region::CT_Region()
{

}

CT_Region::~CT_Region()
{

}

QString CT_Region::toString() const
{
    return "";
}

CT_Action::CT_Action():m_Region(nullptr),m_URI(nullptr),m_GotoA(nullptr),m_Sound(nullptr),
    m_Movie(nullptr)
{

}

CT_Action::~CT_Action()
{

}

QString CT_Action::toString() const
{
   // if()
    return "";
}

CT_Dest::CT_Dest():m_PageID(-1),m_Left(0),m_Top(0),m_Right(0),m_Bottom(0),m_Zoom(0)
{

}

CT_Dest::~CT_Dest()
{

}

QString CT_Dest::toString() const
{
    if(m_PageID<=0)
        return "";
    QString start="<ofd:Dest Type=\"%1\" PageID=\"%2\" ",
    end="/>";
    start=start.arg(m_Type).arg(m_PageID);
    if(m_Left>0)
    start.append(QString("Left=\"%1\" ").arg(m_Left));
    if(m_Top>0)
    start.append(QString("Top=\"%1\" ").arg(m_Top));
    if(m_Right>0)
    start.append(QString("Right=\"%1\" ").arg(m_Right));
    if(m_Bottom>0)
    start.append(QString("Bottom=\"%1\" ").arg(m_Bottom));
    if(m_Zoom>0)
    start.append(QString("Zoom=\"%1\" ").arg(m_Zoom));
    return start.append(end);
}

Movie::Movie()
{

}

Movie::~Movie()
{

}

QString Movie::toString() const
{
     return "";
}

Sound::Sound()
{

}

Sound::~Sound()
{

}

QString Sound::toString() const
{
    return "";
}

GotoA::GotoA()
{

}

GotoA::~GotoA()
{

}

QString GotoA::toString() const
{
     return "";
}

URI::URI()
{

}

URI::~URI()
{

}

QString URI::toString() const
{
     return "";
}
