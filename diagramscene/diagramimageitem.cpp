#include "diagramimageitem.h"


DiagramImageItem::DiagramImageItem(CT_Image *image,DocPassage *doc,QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),m_image(image),m_docpass(doc)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
   // m_filename=file;
  //  setPixmap(QPixmap(file));
}

DiagramImageItem::~DiagramImageItem()
{

}

QRectF DiagramImageItem::boundingRect() const
{
        QRect rect = this->pixmap().rect();
        //return QRectF(rect);
       return QRectF(0,0,rect.width(),rect.width()+15);
}

QPainterPath DiagramImageItem::shape() const
{
    QRectF rect = boundingRect();
    QPainterPath path;
    path.addRoundedRect(rect, 5,5);
    return path;
}

void DiagramImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
       QPixmap pixmap = this->pixmap();
       QRect rect = pixmap.rect();
       painter->drawPixmap(rect,pixmap);

}

void DiagramImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void DiagramImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update(boundingRect());
    QGraphicsItem::mouseReleaseEvent(event);
}
