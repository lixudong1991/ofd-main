#include "OFDPage.h"
#include "OFDParser.h"
#include "UnitTool.h"
OFDPage::OFDPage(const QString &page,DocPassage *docpass,QWidget *parent) :
    QGraphicsView(parent)
{
    m_Passage=docpass;
    m_filepath=page;
    setWindowFlags(Qt::Widget);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundRole(QPalette::BrightText);
    setAutoFillBackground(true);
    initPage();
}

OFDPage::~OFDPage()
{

}

void OFDPage::initPage()
{
    m_page=OFDParser::getInstance()->getPage(m_filepath);
    if(!m_page)
        return;
    m_scene=new OFDScene(m_page,m_Passage);
    setScene(m_scene);
    ST_Box area;
    if(m_page->m_Area&&m_page->m_Area->m_PhysicalBox.isValid())
        area= m_page->m_Area->m_PhysicalBox;
    else
        area=m_Passage->m_document->m_CommonData->m_PageArea->m_PhysicalBox;

    setFixedSize(UnitTool::mmToPixel(area.width()),
                       UnitTool::mmToPixel(area.height()));   // 设置页面大小
    setSceneRect(0,0,
                       UnitTool::mmToPixel(area.width()),
                       UnitTool::mmToPixel(area.height()));
}
