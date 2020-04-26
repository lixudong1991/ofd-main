#include "diagramtextitem.h"
#include <QFontDatabase>
#include <QFileInfo>
#include "OFDParser.h"
#include "UnitTool.h"
#include <QTransform>
#include <QPainter>
DiagramTextItem::DiagramTextItem(CT_Text *text,DocPassage *doc,QGraphicsItem *parent)
    : QGraphicsTextItem(parent),m_text(text),m_docpass(doc)
{

    setFlag(QGraphicsItem::ItemIsSelectable);

    setPlainText(m_text->m_TextCode[0]->m_Val);
    auto ite=m_docpass->m_fonts.find(m_text->m_Font);
    if(ite!=m_docpass->m_fonts.cend())
        m_font=ite.value();
    else
        m_font.setFamily("New Sun");

    int size=UnitTool::mmToPixel(m_text->m_Size);
    m_font.setPixelSize(size);
    m_font.setWeight(m_text->m_Weight/10);
    setFont(m_font);
    m_color=Qt::black;
    if(m_text->m_FillColor&&m_text->m_FillColor->m_Value.size()>2)
    {
            int r=m_text->m_FillColor->m_Value[0];
            int g=m_text->m_FillColor->m_Value[1];
            int b=m_text->m_FillColor->m_Value[2];
            int a=m_text->m_FillColor->m_Alpha;
            m_color.setRgb(r,g, b, a);
    }
    setDefaultTextColor(m_color);

  //  setMatrix()
    m_rect.setX(UnitTool::mmToPixel(m_text->m_TextCode[0]->m_X));
    m_rect.setY(UnitTool::mmToPixel(m_text->m_TextCode[0]->m_Y));
    m_rect.setWidth(UnitTool::mmToPixel(m_text->m_Boundary.width()));
    m_rect.setHeight(UnitTool::mmToPixel(m_text->m_Boundary.height()));
    if(m_text->m_CTM.size()>5)
    {
        QTransform t1;
        t1.setMatrix(m_text->m_CTM[0],m_text->m_CTM[1],0,
                m_text->m_CTM[2],m_text->m_CTM[3],0,
                m_text->m_CTM[4],m_text->m_CTM[5],1);
        setTransform(t1);
    }

    setTextInteractionFlags(Qt::TextEditorInteraction);
    setZValue(1000.0);
    setPos(UnitTool::mmToPixel(m_text->m_Boundary.x()), UnitTool::mmToPixel(m_text->m_Boundary.y()));

}


QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
