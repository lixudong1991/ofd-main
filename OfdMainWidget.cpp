#include "OfdMainWidget.h"
#include <QHBoxLayout>
#include "OFDParser.h"
#include <QFileDialog>
OfdMainWidget::OfdMainWidget(QWidget *parent) :
    QWidget(parent)
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open ofd"), "", tr("Image Files (*.ofd)"));
    if(fileName.isEmpty())
        return;
    loadOFDfile(fileName);
    m_content=CreateDocPassage();
    if(m_content)
    {
          QHBoxLayout *mainlay=new QHBoxLayout(this);
          mainlay->addWidget(m_content);
          mainlay->setMargin(20);
    }

}

OfdMainWidget::~OfdMainWidget()
{

}

void OfdMainWidget::loadOFDfile(const QString &file)
{
    OFDParser::getInstance()->parser(file);
    m_ofd=OFDParser::getInstance()->getOFDdoc();
}

DocPassage *OfdMainWidget::CreateDocPassage()
{
    if(!m_ofd)
        return nullptr;
    if(m_ofd->m_DocBody.size()<1)
         return nullptr;

    return new DocPassage(m_ofd->m_DocBody[0]->m_DocRoot);
}
