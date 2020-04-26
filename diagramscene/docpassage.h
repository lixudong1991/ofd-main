#ifndef DOCPASSAGE_H
#define DOCPASSAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFont>
#include <QMap>
#include "ofdtypes/DocumentTypes.h"
#include "ofdtypes/ResTypes.h"

class OFDPage;
class OFDScene;
class OFDPage;
class DiagramImageItem;
class DiagramPathitem;
class DiagramTextItem;

class DocPassage : public QScrollArea
{
    Q_OBJECT
    friend class OFDPage;
    friend class OFDScene;
    friend class DiagramImageItem;
    friend class DiagramPathitem;
    friend class DiagramTextItem;
public:
    explicit DocPassage(const QString &ofddoc,QWidget *parent = nullptr);
    ~DocPassage();
private:
    void initUI();
    void adjustScrollBar(
            QScrollBar *scrollBar,
            double factor);        // 调整滑动条
    void adjustScrollBarRange();    //调整滑动条范围
    void adjustWidgetSize();
    void addPage(QWidget *wid);

    void initOFDDoc();

    int marginWhite;                // 边缘留白
    int spacingWhite;               // 纸张之间的留白

    // 默认的大小
    double default_width;                       //默认宽度
    double default_height;                      //默认高度
    bool default_using_working_area;
    double default_working_width;
    double default_working_height;
    double default_working_x;
    double default_working_y;

    QVBoxLayout * layout;           // 纵向排列
    QWidget * widget;               // 用widget做缓冲
    QString m_filepath;
    Document *m_document;
    QVector<Res*> m_pubres;
    QVector<Res*> m_docres;
    QMap<int,QFont> m_fonts;
};

#endif // DOCPASSAGE_H
