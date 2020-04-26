#ifndef OFDMAINWIDGET_H
#define OFDMAINWIDGET_H

#include <QWidget>

#include "docpassage.h"
#include "ofdtypes/OFDTypes.h"
class OfdMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OfdMainWidget(QWidget *parent = nullptr);
    ~OfdMainWidget();
    void loadOFDfile(const QString &file);
private:
    DocPassage * CreateDocPassage();
    DocPassage *m_content;
    OFD *m_ofd;
};

#endif // OFDMAINWIDGET_H
