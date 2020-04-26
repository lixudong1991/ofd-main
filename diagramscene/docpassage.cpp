#include "docpassage.h"
#include <QFileInfo>
#include <QFontDatabase>
#include "OFDParser.h"
#include "OFDPage.h"

DocPassage::DocPassage(const QString &ofd,QWidget *parent)
    :QScrollArea(parent),m_filepath(ofd),m_document(nullptr)
{
    initUI();
    m_document=OFDParser::getInstance()->getDocument(m_filepath);
    if(!m_document)
        return;
    initOFDDoc();
}

DocPassage::~DocPassage()
{

}


void DocPassage::addPage(QWidget *wid)
{
    this->layout->addWidget(wid,0,Qt::AlignCenter);
    this->layout->update();
    this->adjustWidgetSize();
}

QStringList loadFontFamilyFromFiles(const QString &strFontFilePath)
{
    int loadedFontID =QFontDatabase::addApplicationFont(strFontFilePath);
    if(loadedFontID!=-1)
    {
        return QFontDatabase::applicationFontFamilies(loadedFontID);
    }
    else{
        return QStringList();
    }
}

void DocPassage::initOFDDoc()
{
     QFileInfo finfo(m_filepath);
     QVector<ST_Loc> &pubres=m_document->m_CommonData->m_PublicRes;
     for(int j=0;j<pubres.size();j++)
     {
             Res  *pub=OFDParser::getInstance()->getRes(finfo.path(),pubres[j]);
             m_pubres.append(pub);
     }
     QVector<ST_Loc> &docres=m_document->m_CommonData->m_DocumentRes;
     for(int j=0;j<docres.size();j++)
     {
             Res  *docr=OFDParser::getInstance()->getRes(finfo.path(),docres[j]);
             m_docres.append(docr);
     }
     for(int i=0;i<m_pubres.size();i++)
     {
         for (int j=0;j< m_pubres[i]->m_Fonts.size();j++)
         {
             if (!m_pubres[i]->m_Fonts[j]->m_FontFile.isEmpty())
             {
                 QString fontpath = OFDParser::getInstance()->getOfdPath() + "/"+ finfo.path()+"/" + m_pubres[i]->m_BaseLoc + "/" + m_pubres[i]->m_Fonts[j]->m_FontFile;
                 QStringList fontf= loadFontFamilyFromFiles(fontpath);
             }
             QFont font;
             font.setFamily(m_pubres[i]->m_Fonts[j]->m_FontName);
             font.setBold(m_pubres[i]->m_Fonts[j]->m_Bold);
             font.setItalic(m_pubres[i]->m_Fonts[j]->m_Italic);
             m_fonts.insert(m_pubres[i]->m_Fonts[j]->m_ID,font);
         }
     }

     for(int i=0;i<m_document->m_Pages.size();i++)
     {
        addPage(new OFDPage(finfo.path()+"/"+m_document->m_Pages[i]->m_BaseLoc,this));
     }
}
void DocPassage::initUI()
{
    this->marginWhite = 50;                   // 边缘留下50像素的留白
    this->spacingWhite = 50;
    this->layout = new QVBoxLayout;
    this->layout->setMargin(this->marginWhite);         // 边缘留至少50的空白
    this->layout->setSpacing(this->spacingWhite);       // 纸张之间留下50像素的留白
    this->layout->setAlignment(Qt::AlignHCenter);       // 纸张自动居中排列
    // 新增widget
    this->widget = new QWidget();                       // 中间文档显示区域
    this->widget->setLayout(this->layout);
    this->widget->setVisible(true);
    this->widget->setBackgroundRole(QPalette::Dark);    // widget 背景
    this->widget->setAutoFillBackground(true);
    this->setWidgetResizable(true);                     // 设置ScrollArea 可以影响到内部纸张
    this->setWidget(this->widget);                      // 设置内置widget
    this->setBackgroundRole(QPalette::Dark);            // ScrollArea 的背景
    this->setAlignment(Qt::AlignHCenter);               // ScrollArea 设置位置水平居中

    // 设置滚动条策略
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    adjustScrollBarRange();                             // 调整进度条长度

    // 设置滚动条位置
    adjustScrollBar(this->horizontalScrollBar(), 1);
    adjustScrollBar(this->verticalScrollBar(),1);
    default_width =210 ;                //默认宽度
    default_height =297;              //默认高度
    default_using_working_area = false;
    default_working_width = 210;
    default_working_height =297 ;
    default_working_x = 0;
    default_working_y =0;

}

void DocPassage::adjustScrollBarRange()
{
    QSize areaSize = this->viewport()->size();  // 视窗大小
    QSize widgetSize = this->widget->size();    // 面板大小

    this->horizontalScrollBar()->setPageStep(areaSize.width());
    this->horizontalScrollBar()->setRange(0,widgetSize.width()
                                        - areaSize.width());

    this->verticalScrollBar()->setPageStep(areaSize.height());
    this->verticalScrollBar()->setRange(0,widgetSize.height()
                                        - areaSize.height());

    this->horizontalScrollBar()->update();
    this->verticalScrollBar()->update();
}
void DocPassage::adjustWidgetSize()
{

    this->update();
    this->viewport()->update();
    this->QScrollArea::update();

    adjustScrollBarRange();     // 调整进度条长度

    // 调整滚动条位置
  //  adjustScrollBar(this->horizontalScrollBar(), this->scaleFactor);
   // adjustScrollBar(this->verticalScrollBar(), this->scaleFactor);

}
void DocPassage::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    // 设置滚动条位置
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor -1) * scrollBar->pageStep()/2)) + 1);
    scrollBar->update();
}
