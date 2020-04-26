#include "diagrampathitem.h"
#include <QPainterPath>
#include <QPen>
#include "UnitTool.h"
DiagramPathitem::DiagramPathitem(CT_Path *cpath,DocPassage *d,QGraphicsItem *parent) :
    QGraphicsPathItem(parent),m_path(cpath),m_docPass(d)
{
    QStringList lits=m_path->m_AbbreviatedData.split(QRegExp("\\s+"));

    QPainterPath path;

    if(m_path->m_Stroke)
    {
         QColor color(Qt::black);
         if(m_path->m_StrokeColor->m_Value.size()>2)
         {
             int r=m_path->m_StrokeColor->m_Value[0];
             int g=m_path->m_StrokeColor->m_Value[1];
             int b=m_path->m_StrokeColor->m_Value[2];
             int a=m_path->m_StrokeColor->m_Alpha;
             color.setRgb(r,g, b, a);
         }
        QPen pen;
        pen.setWidth(UnitTool::mmToPixel(m_path->m_LineWidth));
        pen.setColor(color);
        setPen(pen);
    }

    if(m_path->m_Fill)
    {
            QColor color(Qt::transparent);
            if(m_path->m_FillColor->m_Value.size()>2)
            {
                int r=m_path->m_FillColor->m_Value[0];
                int g=m_path->m_FillColor->m_Value[1];
                int b=m_path->m_FillColor->m_Value[2];
                int a=m_path->m_FillColor->m_Alpha;
                color.setRgb(r,g, b, a);
            }
            setBrush(QBrush(color));

    }
    if(m_path->m_Rule=="Even-Odd")
       path.setFillRule(Qt::OddEvenFill);
    else
       path.setFillRule(Qt::WindingFill);

    for(int j=0;j<lits.size();j+=3)
    {
        if(lits[j]=="M")
        {
            QPoint start(0,0);
            start.setX(UnitTool::mmToPixel(lits[j+1].toDouble()));
            start.setY(UnitTool::mmToPixel(lits[j+2].toDouble()));
            path.moveTo(start);
        }
        else if(lits[j]=="L")
        {
           QPoint end(0,0);
           end.setX(UnitTool::mmToPixel(lits[j+1].toDouble()));
           end.setY(UnitTool::mmToPixel(lits[j+2].toDouble()));
           path.lineTo(end);
        }else if(lits[j]=="C"){
           QPoint end(0,0);
           end.setX(UnitTool::mmToPixel(lits[1].toDouble()));
           end.setY(UnitTool::mmToPixel(lits[2].toDouble()));
           path.lineTo(end);
        }
    }
    setPath(path);
    QPoint point(UnitTool::mmToPixel(m_path->m_Boundary.x()),UnitTool::mmToPixel(m_path->m_Boundary.y()));
    setPos(point);
}

DiagramPathitem::~DiagramPathitem()
{

}
