#ifndef OFDSCENE_H
#define OFDSCENE_H

#include <QGraphicsScene>
#include "ofdtypes/PageTypes.h"
#include "docpassage.h"
class OFDScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit OFDScene(Page *page,DocPassage *docpass,QObject *parent = 0);
    ~OFDScene();
private:
    void initLayer();
    Page *m_page;
    DocPassage *m_DocPass;
};

#endif // OFDSCENE_H
