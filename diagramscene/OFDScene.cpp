#include "OFDScene.h"
#include "diagramtextitem.h"
#include "diagrampathitem.h"
#include "diagramimageitem.h"
OFDScene::OFDScene(Page *page,DocPassage *docpass,QObject *parent) :
   QGraphicsScene(parent),m_page(page),m_DocPass(docpass)
{
    initLayer();
}

OFDScene::~OFDScene()
{

}

void OFDScene::initLayer()
{
    QVector<CT_Text*> &texts=m_page->m_Content[0]->m_TextObject;
    for(int i=0;i<texts.size();i++)
    {
        DiagramTextItem *textitem=new DiagramTextItem(texts[i],m_DocPass);
        addItem(textitem);
    }
    QVector<CT_Path*> &paths=m_page->m_Content[0]->m_PathObject;
    for(int i=0;i<paths.size();i++)
    {
        DiagramPathitem *pathitem=new DiagramPathitem(paths[i],m_DocPass);
        addItem(pathitem);
    }
    QVector<CT_Image*> &images=m_page->m_Content[0]->m_ImageObject;
    for(int i=0;i<images.size();i++)
    {
        DiagramImageItem *imageitem=new DiagramImageItem(images[i],m_DocPass);
        addItem(imageitem);
    }
}
