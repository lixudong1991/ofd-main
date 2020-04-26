#ifndef DIAGRAMIMAGEITEM_H
#define DIAGRAMIMAGEITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "docpassage.h"
#include "ofdtypes/PageTypes.h"

class DiagramImageItem : public QGraphicsPixmapItem
{
public:
    explicit DiagramImageItem(CT_Image *image,DocPassage *,QGraphicsItem *parent = 0);
    ~DiagramImageItem()override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//signals:
 //   void nodeIsMoving(QPointF &pos);
  //  void nodeIsPressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
private:
    CT_Image *m_image;
    DocPassage *m_docpass;
};

#endif // DIAGRAMIMAGEITEM_H
