#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QGraphicsTextItem>
#include <QPen>
#include <QFont>
#include "docpassage.h"
#include "ofdtypes/PageTypes.h"
QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

//! [0]
class DiagramTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    DiagramTextItem(CT_Text *text,DocPassage *,QGraphicsItem *parent = 0);

    int type() const override { return Type; }
signals:
    void lostFocus(DiagramTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:

    QRect m_rect;
    QFont m_font;
    QColor m_color;
    QPen m_pen;

    CT_Text *m_text;
    DocPassage *m_docpass;

};
//! [0]

#endif // DIAGRAMTEXTITEM_H
