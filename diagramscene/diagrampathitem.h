#ifndef DIAGRAMPATHITEM_H
#define DIAGRAMPATHITEM_H

#include<QGraphicsPathItem>
#include "docpassage.h"
#include "ofdtypes/PageTypes.h"


class DiagramPathitem : public QGraphicsPathItem
{


public:
    explicit DiagramPathitem(CT_Path *path,DocPassage *,QGraphicsItem *parent = 0);
    ~DiagramPathitem();

private:
    CT_Path *m_path;
    DocPassage *m_docPass;
};

#endif // DIAGRAMPATHITEM_H
