#ifndef OFDPAGE_H
#define OFDPAGE_H

#include <QGraphicsView>
#include "OFDScene.h"
#include "ofdtypes/PageTypes.h"
#include "docpassage.h"
class OFDPage : public QGraphicsView
{
    Q_OBJECT

public:
    explicit OFDPage(const QString &page,DocPassage *docpass,QWidget *parent = nullptr);
    ~OFDPage();
private:
    void initPage();
    QString m_filepath;
    OFDScene *m_scene;
    Page *m_page;
    DocPassage *m_Passage;
};

#endif // OFDPAGE_H
