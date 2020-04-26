#include "OFDParser.h"
#include "ZipTool.h"
#include <QFileInfo>
#include <QFile>
#include <QApplication>
#include <QDebug>

OFDParser* OFDParser::m_instance=nullptr;

OFDParser* OFDParser::getInstance()
{
    if(!m_instance)
         m_instance=new OFDParser();
    return m_instance;
}

OFDParser::OFDParser()
{

}

OFDParser::~OFDParser()
{

}
void OFDParser::parser(const QString &path)
{
    QFileInfo finfo(path);
    m_path=QApplication::applicationDirPath()+"/"+finfo.fileName().left(finfo.fileName().lastIndexOf('.'));
    if(finfo.isFile())
    {
        Decompress(path);
    }
}
void OFDParser::Decompress(const QString &path)
{

      ZipTool::extractDir(path,m_path);
      qDebug()<<"extractDir : "+m_path;
}
void OFDParser::ComPress(const QString &path)
{

  //  QString temp=m_path+".ofd";
    QFile f(path);
    if(f.exists())
        f.remove();
    ZipTool::compressDir(path,m_path);
    qDebug()<<"ComPress : "+path;
}
OFD *OFDParser::getOFDdoc()
{

    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    QString ofdpath=m_path+"/OFD.xml";
    if(doc->LoadFile((ofdpath).toLocal8Bit().data()) != tinyxml2::XML_SUCCESS)
    {
        return nullptr;
    }
    OFD *ofd=new OFD();
    tinyxml2::XMLElement* root = doc->RootElement();
    ofd->m_Version=root->Attribute("Version");
    ofd->m_DocType=root->Attribute("DocType");
    tinyxml2::XMLElement * body = root->FirstChildElement("ofd:DocBody");
    while(body)
    {
        DocBody *b=new DocBody();
        tinyxml2::XMLElement * info = body->FirstChildElement("ofd:DocInfo");
        if(info)
        {
            CT_DocInfo *dinfo=new CT_DocInfo();
            tinyxml2::XMLElement * e = info->FirstChildElement("ofd:DocID");
            if(e)
                dinfo->m_DocID=e->GetText();
            tinyxml2::XMLElement * e1 = info->FirstChildElement("ofd:Title");
            if(e1)
                dinfo->m_Title=e1->GetText();
            tinyxml2::XMLElement * e2 = info->FirstChildElement("ofd:Author");
            if(e2)
                dinfo->m_Author=e2->GetText();
            tinyxml2::XMLElement * e3 = info->FirstChildElement("ofd:Subject");
            if(e3)
                dinfo->m_Subject=e3->GetText();
            tinyxml2::XMLElement * e4 = info->FirstChildElement("ofd:Abstract");
            if(e4)
                dinfo->m_Abstract=e4->GetText();
            tinyxml2::XMLElement * e5 = info->FirstChildElement("ofd:CreationDate");
            if(e5)
                dinfo->m_CreationDate=e5->GetText();
            tinyxml2::XMLElement * e6 = info->FirstChildElement("ofd:ModDate");
            if(e6)
                dinfo->m_ModDate=e6->GetText();
            tinyxml2::XMLElement * e7 = info->FirstChildElement("ofd:DocUsage");
            if(e7)
                dinfo->m_DocUsage=e7->GetText();
            tinyxml2::XMLElement * e8 = info->FirstChildElement("ofd:Cover");
            if(e8)
                dinfo->m_Cover=e8->GetText();
            tinyxml2::XMLElement * e9 = info->FirstChildElement("ofd:Creator");
            if(e9)
                dinfo->m_Creator=e9->GetText();
            tinyxml2::XMLElement * e10 = info->FirstChildElement("ofd:CreatorVersion");
            if(e10)
                dinfo->m_CreatorVersion=e10->GetText();
             b->m_DocInfo=dinfo;
        }
        tinyxml2::XMLElement * droot=body->FirstChildElement("ofd:DocRoot");
        if(droot)
          b->m_DocRoot=droot->GetText();
        ofd->m_DocBody.append(b);
        body=body->NextSiblingElement("ofd:DocBody");
    }
    delete doc;
    return ofd;
}
static CT_PageArea* getArea(tinyxml2::XMLElement *area)
{
    if(area)
    {
      CT_PageArea* pageArea=new CT_PageArea();
      tinyxml2::XMLElement * PhysicalBox = area->FirstChildElement("ofd:PhysicalBox");
      if(PhysicalBox)
      {
          QString temp=PhysicalBox->GetText();
          QStringList list=temp.split(QRegExp("\\s+"));
          if(list.size()>3)
          {
            pageArea->m_PhysicalBox.setX(list[0].toDouble());
            pageArea->m_PhysicalBox.setY(list[1].toDouble());
            pageArea->m_PhysicalBox.setWidth(list[2].toDouble());
            pageArea->m_PhysicalBox.setHeight(list[3].toDouble());
          }
      }
      tinyxml2::XMLElement * ApplicationBox = area->FirstChildElement("ofd:ApplicationBox");
      if(ApplicationBox)
      {
          QString temp=ApplicationBox->GetText();
          QStringList list=temp.split(QRegExp("\\s+"));
          if(list.size()>3)
          {
            pageArea->m_ApplicationBox.setX(list[0].toDouble());
            pageArea->m_ApplicationBox.setY(list[1].toDouble());
            pageArea->m_ApplicationBox.setWidth(list[2].toDouble());
            pageArea->m_ApplicationBox.setHeight(list[3].toDouble());
          }
      }
      tinyxml2::XMLElement * ContentBox = area->FirstChildElement("ofd:ContentBox");
      if(ContentBox)
      {
          QString temp=ContentBox->GetText();
          QStringList list=temp.split(QRegExp("\\s+"));
          if(list.size()>3)
          {
            pageArea->m_ContentBox.setX(list[0].toDouble());
            pageArea->m_ContentBox.setY(list[1].toDouble());
            pageArea->m_ContentBox.setWidth(list[2].toDouble());
            pageArea->m_ContentBox.setHeight(list[3].toDouble());
          }
      }
      tinyxml2::XMLElement * BleedBox = area->FirstChildElement("ofd:BleedBox");
      if(BleedBox)
      {
          QString temp=BleedBox->GetText();
          QStringList list=temp.split(QRegExp("\\s+"));
          if(list.size()>3)
          {
            pageArea->m_BleedBox.setX(list[0].toDouble());
            pageArea->m_BleedBox.setY(list[1].toDouble());
            pageArea->m_BleedBox.setWidth(list[2].toDouble());
            pageArea->m_BleedBox.setHeight(list[3].toDouble());
          }
      }
      return pageArea;
    }
    return nullptr;
}

static CT_Color *getColor(tinyxml2::XMLElement *doc)
{
    if(!doc)
        return nullptr;
    CT_Color *color=new CT_Color();
    QStringList v=QString(doc->Attribute("Value")).split(QRegExp("\\s+"));
    if(v.size()>2)
    {
        color->m_Value.append(v[0].toInt());
        color->m_Value.append(v[1].toInt());
        color->m_Value.append(v[2].toInt());
    }
    color->m_Index=QString(doc->Attribute("Index")).toInt();
    color->m_ColorSpace=QString(doc->Attribute("ColorSpace")).toInt();
    if(doc->Attribute("Alpha"))
       color->m_Alpha=QString(doc->Attribute("Alpha")).toInt();
    else
       color->m_Alpha=255;
    return color;
}
Document *OFDParser::getDocument(const ST_Loc &path)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    QString ofdpath=m_path+"/"+path;
    if(doc->LoadFile((ofdpath).toLocal8Bit().data()) != tinyxml2::XML_SUCCESS)
    {
        return nullptr;
    }
    Document *docment=new Document();
    tinyxml2::XMLElement* root = doc->RootElement();
    tinyxml2::XMLElement * cdata = root->FirstChildElement("ofd:CommonData");
    if(cdata)
    {
        CT_CommonData* commonData=new CT_CommonData();
        tinyxml2::XMLElement * MaxUnitID = cdata->FirstChildElement("ofd:MaxUnitID");
        if(MaxUnitID)
            commonData->m_MaxUnitID=QString(MaxUnitID->GetText()).toInt();
        tinyxml2::XMLElement * PageArea = cdata->FirstChildElement("ofd:PageArea");
        commonData->m_PageArea=getArea(PageArea);
        tinyxml2::XMLElement * PublicRes = cdata->FirstChildElement("ofd:PublicRes");
        while(PublicRes)
        {
           commonData->m_PublicRes.push_back(PublicRes->GetText());
           PublicRes=PublicRes->NextSiblingElement("ofd:PublicRes");
        }
        tinyxml2::XMLElement * DocumentRes = cdata->FirstChildElement("ofd:DocumentRes");
        while(DocumentRes)
        {
           commonData->m_DocumentRes.push_back(DocumentRes->GetText());
           DocumentRes=DocumentRes->NextSiblingElement("ofd:DocumentRes");
        }
        docment->m_CommonData=commonData;
    }
     tinyxml2::XMLElement * pages = root->FirstChildElement("ofd:Pages");
     if(pages)
     {
         tinyxml2::XMLElement * Page = pages->FirstChildElement("ofd:Page");
         while(Page)
         {
              CT_Page *page=new CT_Page();
              page->m_ID = QString(Page->Attribute("ID")).toInt();
              page->m_BaseLoc = QString(Page->Attribute("BaseLoc"));
              docment->m_Pages.append(page);
              Page=Page->NextSiblingElement("ofd:Page");
         }
     }
     delete doc;
     return docment;
}
/*   tinyxml2::XMLElement* person = root->FirstChildElement("person");
   while (person)
   {
        //获取person的name属性
        const XMLAttribute * nameAttr = person->FirstAttribute();
        String perName = nameAttr->Value();
        if(perName == "花花")
        {
            cout<<nameAttr->Name()<<":"<<nameAttr->Value()<<endl;
            //遍历person的其他子节点
            tinyxml2::XMLElement * perAttr = person->FirstChildElement();
            while(perAttr)
            {
                cout<<perAttr->Name()<<":"<<perAttr->GetText()<<endl;
                perAttr = perAttr->NextSiblingElement();
            }
        }
        person =  person->NextSiblingElement();
   }*/

static void getGraphicUnit(CT_GraphicUnit *obj,tinyxml2::XMLElement *Tobject)
{
    if(Tobject->Attribute("Boundary"))
    {
        QStringList v=QString(Tobject->Attribute("Boundary")).split(QRegExp("\\s+"));
        if(v.size()>3)
        {
            obj->m_Boundary.setX(v[0].toDouble());
            obj->m_Boundary.setY(v[1].toDouble());
            obj->m_Boundary.setWidth(v[2].toDouble());
            obj->m_Boundary.setHeight(v[3].toDouble());
        }
    }
    if(Tobject->Attribute("Visible"))
        obj->m_Visible=QStoB(QString(Tobject->Attribute("Visible")));
    else
        obj->m_Visible =true;

    if(Tobject->Attribute("CTM"))
    {
        QStringList v=QString(Tobject->Attribute("CTM")).split(QRegExp("\\s+"));
        for(int i=0;i<v.size();i++)
            obj->m_CTM.append(v[i].toFloat());
    }
    obj->m_DrawParam=QString(Tobject->Attribute("DrawParam")).toInt();
    if(Tobject->Attribute("LineWidth"))
         obj->m_LineWidth=QString(Tobject->Attribute("LineWidth")).toFloat();
    else
         obj->m_LineWidth=0.353f;
    if(Tobject->Attribute("Cap"))
         obj->m_Cap=Tobject->Attribute("Cap");
    else
         obj->m_Cap="Butt";

    if(Tobject->Attribute("Join"))
         obj->m_Join=Tobject->Attribute("Join");
    else
         obj->m_Join="Miter";

    if(Tobject->Attribute("MiterLimit"))
         obj->m_MiterLimit=QString(Tobject->Attribute("MiterLimit")).toFloat();
    else
         obj->m_MiterLimit=4.234f;

    if(Tobject->Attribute("DashOffset"))
         obj->m_DashOffset=QString(Tobject->Attribute("DashOffset")).toFloat();
    else
         obj->m_DashOffset=0.0f;

    if(Tobject->Attribute("DashPattern"))
    {
         QStringList v=QString(Tobject->Attribute("DashPattern")).split(QRegExp("\\s+"));
         for(int i=0;i<v.size();i++)
             obj->m_DashPattern.append(v[i].toFloat());
    }

    if(Tobject->Attribute("Alpha"))
         obj->m_Alpha=QString(Tobject->Attribute("Alpha")).toInt();
    else
         obj->m_Alpha=255;
}

static CT_Text *getTextObject(tinyxml2::XMLElement *Tobject)
{
    CT_Text *textObject=new CT_Text();
    textObject->m_ID=QString(Tobject->Attribute("ID")).toInt();
    textObject->m_Font=QString(Tobject->Attribute("Font")).toInt();
    textObject->m_Size=QString(Tobject->Attribute("Size")).toFloat();
    textObject->m_Stroke=QStoB(QString(Tobject->Attribute("Stroke")));
    if(Tobject->Attribute("Fill"))
        textObject->m_Fill=QStoB(QString(Tobject->Attribute("Fill")));
    else
        textObject->m_Fill=true;

    textObject->m_HScale=QStoB(QString(Tobject->Attribute("HScale")));
    textObject->m_Italic=QStoB(QString(Tobject->Attribute("Italic")));
    textObject->m_ReadDirection=QString(Tobject->Attribute("ReadDirection")).toInt();
    textObject->m_CharDirection=QString(Tobject->Attribute("CharDirection")).toInt();
    if(Tobject->Attribute("Weight"))
        textObject->m_Weight=QString(Tobject->Attribute("Weight")).toInt();
    else
        textObject->m_Weight=400;


    tinyxml2::XMLElement *fillc = Tobject->FirstChildElement("ofd:FillColor");
    textObject->m_FillColor=getColor(fillc);
    tinyxml2::XMLElement *StrokeColor = Tobject->FirstChildElement("ofd:StrokeColor");
    textObject->m_StrokeColor=getColor(StrokeColor);
    tinyxml2::XMLElement *CGTransform = Tobject->FirstChildElement("ofd:CGTransform");
    while(CGTransform)
    {
       CT_CGTransform *Transform=new CT_CGTransform();
       Transform->m_CodePosition=QString(CGTransform->Attribute("CodePosition")).toInt();
       Transform->m_CodeCount=QString(CGTransform->Attribute("CodeCount")).toInt();
       Transform->m_GlyphCount=QString(CGTransform->Attribute("GlyphCount")).toInt();

       tinyxml2::XMLElement * Glyphs=CGTransform->FirstChildElement("ofd:Glyphs");
       if(Glyphs)
       {
           QStringList v=QString(Glyphs->GetText()).split(QRegExp("\\s+"));
           for(int i=0;i<v.size();i++)
               Transform->m_Glyphs.append(v[i].toFloat());
       }
       textObject->m_CGTransform.append(Transform);
       CGTransform=CGTransform->NextSiblingElement("ofd:CGTransform");
    }

    tinyxml2::XMLElement *Textcode = Tobject->FirstChildElement("ofd:TextCode");
    while(Textcode)
    {
        TextCode *textCode=new TextCode();
        textCode->m_X=QString(Textcode->Attribute("X")).toFloat();
        textCode->m_Y=QString(Textcode->Attribute("Y")).toFloat();
        textCode->m_Val=Textcode->GetText();

        if(Textcode->Attribute("DeltaX")){
            QStringList v=QString(Textcode->Attribute("DeltaX")).split(QRegExp("\\s+"));
            for(int i=0;i<v.size();i++)
                textCode->m_DeltaX.append(v[i].toFloat());
        }
        if(Textcode->Attribute("DeltaY")){
           QStringList v1=QString(Textcode->Attribute("DeltaY")).split(QRegExp("\\s+"));
           for(int i=0;i<v1.size();i++)
               textCode->m_DeltaY.append(v1[i].toFloat());
        }
        textObject->m_TextCode.append(textCode);
       Textcode=Textcode->NextSiblingElement("ofd:TextCode");
    }
    getGraphicUnit(textObject,Tobject);
    return textObject;
}
static CT_Path* getPathObject(tinyxml2::XMLElement *Pobject)
{
    CT_Path *pathObject=new CT_Path();
    pathObject->m_ID=QString(Pobject->Attribute("ID")).toInt();
    if(Pobject->Attribute("Stroke"))
        pathObject->m_Stroke=QStoB(QString(Pobject->Attribute("Stroke")));
    else
        pathObject->m_Stroke=true;
    if(Pobject->Attribute("Fill"))
        pathObject->m_Fill=QStoB(QString(Pobject->Attribute("Fill")));
    else
        pathObject->m_Fill=false;
    if(Pobject->Attribute("Rule"))
       pathObject->m_Rule=Pobject->Attribute("Rule");
    else
       pathObject->m_Rule="NonZero";

    tinyxml2::XMLElement *fillc = Pobject->FirstChildElement("ofd:FillColor");
    pathObject->m_FillColor=getColor(fillc);
    tinyxml2::XMLElement *StrokeColor = Pobject->FirstChildElement("ofd:StrokeColor");
    pathObject->m_StrokeColor=getColor(StrokeColor);
    tinyxml2::XMLElement *AbbreviatedData = Pobject->FirstChildElement("ofd:AbbreviatedData");
    if(AbbreviatedData)
        pathObject->m_AbbreviatedData=AbbreviatedData->GetText();
    getGraphicUnit(pathObject,Pobject);
    return pathObject;
}

static CT_Image* getImageObject(tinyxml2::XMLElement *Iobject)
{
    CT_Image *imageObject=new CT_Image();
    imageObject->m_ID=QString(Iobject->Attribute("ID")).toInt();
    imageObject->m_ResourceID=QString(Iobject->Attribute("ResourceID")).toInt();
    imageObject->m_Substitution=QString(Iobject->Attribute("Substitution")).toInt();
    imageObject->m_ImageMask=QString(Iobject->Attribute("ImageMask")).toInt();
    tinyxml2::XMLElement *Bordere = Iobject->FirstChildElement("ofd:Border");
    if(Bordere)
    {
        Border *border=new Border();
        if(Bordere->Attribute("LineWidth"))
          border->m_LineWidth=QString(Bordere->Attribute("LineWidth")).toFloat();
        else
          border->m_LineWidth= 0.353f;
        border->m_HorizonalCornerRadius=QString(Bordere->Attribute("HorizonalCornerRadius")).toFloat();
        border->m_VerticalCornerRadius=QString(Bordere->Attribute("VerticalCornerRadius")).toFloat();
        border->m_DashOffset=QString(Bordere->Attribute("DashOffset")).toFloat();
        if(Bordere->Attribute("DashPattern"))
        {
           QStringList v1=QString(Bordere->Attribute("DashPattern")).split(QRegExp("\\s+"));
           for(int i=0;i<v1.size();i++)
               border->m_DashPattern.append(v1[i].toFloat());
        }
        tinyxml2::XMLElement *BorderColor = Bordere->FirstChildElement("ofd:BorderColor");
        border->m_BorderColor=getColor(BorderColor);
        imageObject->m_Border=border;
    }
    getGraphicUnit(imageObject,Iobject);
    return imageObject;
}
static CT_Composite* getmCompositeObject(tinyxml2::XMLElement *Cobject)
{
    CT_Composite *composite=new CT_Composite();
    composite->m_ID=QString(Cobject->Attribute("ID")).toInt();
    composite->m_ResourceID=QString(Cobject->Attribute("ResourceID")).toInt();
    getGraphicUnit(composite,Cobject);
    return composite;
}
Page *OFDParser::getPage(const ST_Loc &path)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    QString ofdpath=m_path+"/"+path;
    if(doc->LoadFile((ofdpath).toLocal8Bit().data()) != tinyxml2::XML_SUCCESS)
    {
        return nullptr;
    }
    Page *page=new Page();
    tinyxml2::XMLElement* root = doc->RootElement();
    page->m_Area=getArea(root->FirstChildElement("ofd:Area"));
    tinyxml2::XMLElement * Content= root->FirstChildElement("ofd:Content");
    if(Content)
    {
         tinyxml2::XMLElement *Layere = Content->FirstChildElement("ofd:Layer");
         while(Layere)
         {
             Layer *layer=new Layer();
             layer->m_ID=QString(Layere->Attribute("ID")).toInt();
             layer->m_Type=Layere->Attribute("Type");
             layer->m_DrawParam=QString(Layere->Attribute("DrawParam")).toInt();
             tinyxml2::XMLElement *Tobject = Layere->FirstChildElement("ofd:TextObject");
             while(Tobject)
             {
                CT_Text*  textObject= getTextObject(Tobject);
                layer->m_TextObject.append(textObject);
                Tobject=Tobject->NextSiblingElement("ofd:TextObject");
             } 
             tinyxml2::XMLElement *Pobject = Layere->FirstChildElement("ofd:PathObject");
             while(Pobject)
             {
                CT_Path*  pathObject= getPathObject(Pobject);
                layer->m_PathObject.append(pathObject);
                Pobject=Pobject->NextSiblingElement("ofd:PathObject");
             }
             tinyxml2::XMLElement *ImageObject = Layere->FirstChildElement("ofd:ImageObject");
             while(ImageObject)
             {
                CT_Image*  imageObject= getImageObject(ImageObject);
                layer->m_ImageObject.append(imageObject);
                ImageObject=ImageObject->NextSiblingElement("ofd:ImageObject");
             }
             tinyxml2::XMLElement *CompositeObject = Layere->FirstChildElement("ofd:CompositeObject");
             while(CompositeObject)
             {
                CT_Composite* composite= getmCompositeObject(CompositeObject);
                layer->m_CompositeObject.append(composite);
                CompositeObject=CompositeObject->NextSiblingElement("ofd:CompositeObject");
             }
             page->m_Content.append(layer);

             Layere=Layere->NextSiblingElement("ofd:Layer");
         }
    }
    delete doc;
    return page;
}


Res* OFDParser::getRes(const QString &ppath,const ST_Loc &path)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    QString ofdpath=m_path+"/"+ppath+"/"+path;
    if(doc->LoadFile((ofdpath).toLocal8Bit().data()) != tinyxml2::XML_SUCCESS)
        return nullptr;
    Res *res=new Res();
    tinyxml2::XMLElement* root = doc->RootElement();
    res->m_BaseLoc=root->Attribute("BaseLoc");
    tinyxml2::XMLElement * ColorSpaces= root->FirstChildElement("ofd:ColorSpaces");
    if(ColorSpaces)
    {
      tinyxml2::XMLElement * ColorSpace= ColorSpaces->FirstChildElement("ofd:ColorSpace");
      while(ColorSpace)
      {
         CT_ColorSpace *colorSpace=new CT_ColorSpace();
         colorSpace->m_ID=QString(ColorSpace->Attribute("ID")).toInt();
         if(ColorSpace->Attribute("Type"))
             colorSpace->m_Type=ColorSpace->Attribute("Type");
         else
             colorSpace->m_Type="RGB";
         if(ColorSpace->Attribute("BitsPerComonent"))
             colorSpace->m_BitsPerComonent=QString(ColorSpace->Attribute("BitsPerComonent")).toInt();
         else
             colorSpace->m_BitsPerComonent=8;
         colorSpace->m_Profile=ColorSpace->Attribute("Profile");

         tinyxml2::XMLElement * Palettee= ColorSpace->FirstChildElement("ofd:Palette");
         if(Palettee)
         {
            Palette *palette=new Palette();
            tinyxml2::XMLElement * CV= Palettee->FirstChildElement("ofd:CV");
            while(CV)
            {
              QStringList v1=QString(CV->GetText()).split(QRegExp("\\s+"));
              if(v1.size()>0)
              {
                  ST_Array<float> *temp=new ST_Array<float>() ;
                  for(int i=0;i<v1.size();i++)
                        temp->append(v1[i].toFloat());
                  palette->m_CV.append(temp);
              }
              CV=CV->NextSiblingElement("ofd:CV");
            }
            colorSpace->m_Palette=palette;
         }
         res->m_ColorSpaces.append(colorSpace);
         ColorSpace=ColorSpace->NextSiblingElement("ofd:ColorSpace");
      }
    }
    tinyxml2::XMLElement * DrawParms= root->FirstChildElement("ofd:DrawParms");
    if(DrawParms)
    {
        tinyxml2::XMLElement * DrawParm= ColorSpaces->FirstChildElement("ofd:DrawParm");
        while(DrawParm)
        {
            CT_DrawParm *drawParm=new CT_DrawParm();
            drawParm->m_ID=QString(DrawParm->Attribute("ID")).toInt();
            drawParm->m_Relative=QString(DrawParm->Attribute("Relative")).toInt();
            if(DrawParm->Attribute("LineWidth"))
                drawParm->m_LineWidth=QString(DrawParm->Attribute("LineWidth")).toFloat();
            else
                drawParm->m_LineWidth=0.353f;

            if(DrawParm->Attribute("Join"))
                drawParm->m_Join=DrawParm->Attribute("Join");
            else
                drawParm->m_Join="Miter";
            if(DrawParm->Attribute("Cap"))
                drawParm->m_Cap=DrawParm->Attribute("Cap");
            else
                drawParm->m_Cap="Butt";
            drawParm->m_DashOffset=QString(DrawParm->Attribute("DashOffset")).toFloat();
            if(DrawParm->Attribute("DashPattern"))
            {
                QStringList v1=QString(DrawParm->Attribute("DashPattern")).split(QRegExp("\\s+"));
                for(int i=0;i<v1.size();i++)
                    drawParm->m_DashPattern.append(v1[i].toFloat());
            }
            if(DrawParm->Attribute("MiterLimit"))
               drawParm->m_MiterLimit=QString(DrawParm->Attribute("MiterLimit")).toFloat();
            else
               drawParm->m_MiterLimit= 4.234f;
            tinyxml2::XMLElement *fillc = DrawParm->FirstChildElement("ofd:FillColor");
            drawParm->m_FillColor=getColor(fillc);
            tinyxml2::XMLElement *StrokeColor = DrawParm->FirstChildElement("ofd:StrokeColor");
            drawParm->m_StrokeColor=getColor(StrokeColor);
            res->m_DrawParms.append(drawParm);
            DrawParm=DrawParm->NextSiblingElement("ofd:DrawParm");
        }
    }
    tinyxml2::XMLElement * Fonts= root->FirstChildElement("ofd:Fonts");
    if(Fonts)
    {
        tinyxml2::XMLElement * Font= Fonts->FirstChildElement("ofd:Font");
        while(Font)
        {
            CT_Font *font=new CT_Font();
            font->m_ID=QString(Font->Attribute("ID")).toInt();
            font->m_FontName=Font->Attribute("FontName");
            font->m_FamilyName=Font->Attribute("FamilyName");
            if(Font->Attribute("Charset"))
               font->m_Charset=Font->Attribute("Charset");
            else
               font->m_Charset="unicode";

            font->m_Italic=QStoB(QString(Font->Attribute("Italic")));
            font->m_Bold=QStoB(QString(Font->Attribute("Bold")));
            font->m_Serif=QStoB(QString(Font->Attribute("Serif")));
            font->m_FixedWidth=QStoB(QString(Font->Attribute("FixedWidth")));

            tinyxml2::XMLElement *FontFile = Font->FirstChildElement("ofd:FontFile");
            if(FontFile)
               font->m_FontFile=FontFile->GetText();
            res->m_Fonts.append(font);
            Font=Font->NextSiblingElement("ofd:Font");
        }
    }
    tinyxml2::XMLElement * CompositeGraphicUnits= root->FirstChildElement("ofd:CompositeGraphicUnits");
    if(CompositeGraphicUnits)
    {
        tinyxml2::XMLElement * CompositeGraphicUnit= CompositeGraphicUnits->FirstChildElement("ofd:CompositeGraphicUnit");
        while(CompositeGraphicUnit)
        {
            CT_VectorG *compositeGraphicUnit=new CT_VectorG();
            compositeGraphicUnit->m_ID=QString(CompositeGraphicUnit->Attribute("ID")).toInt();
            compositeGraphicUnit->m_Width=QString(CompositeGraphicUnit->Attribute("Width")).toFloat();
            compositeGraphicUnit->m_Height=QString(CompositeGraphicUnit->Attribute("Height")).toFloat();

            tinyxml2::XMLElement *Thumbnail = CompositeGraphicUnit->FirstChildElement("ofd:Thumbnail");
            if(Thumbnail)
                compositeGraphicUnit->m_Thumbnail=QString(Thumbnail->GetText()).toInt();
            tinyxml2::XMLElement *Substitution = CompositeGraphicUnit->FirstChildElement("ofd:Substitution");
            if(Substitution)
                compositeGraphicUnit->m_Substitution=QString(Substitution->GetText()).toInt();
            res->m_CompositeGraphicUnits.append(compositeGraphicUnit);
            CompositeGraphicUnit=CompositeGraphicUnit->NextSiblingElement("ofd:CompositeGraphicUnit");
        }
    }
    tinyxml2::XMLElement * MultiMedias= root->FirstChildElement("ofd:MultiMedias");
    if(MultiMedias)
    {
        tinyxml2::XMLElement * MultiMedia= MultiMedias->FirstChildElement("ofd:MultiMedia");
        while(MultiMedia)
        {
            CT_MultiMedia *multiMedia=new CT_MultiMedia();
            multiMedia->m_ID=QString(MultiMedia->Attribute("ID")).toInt();
            multiMedia->m_Type=MultiMedia->Attribute("Type");
            multiMedia->m_Format=MultiMedia->Attribute("Format");
            tinyxml2::XMLElement *MediaFile = MultiMedia->FirstChildElement("ofd:MediaFile");
            if(MediaFile)
                multiMedia->m_MediaFile=MediaFile->GetText();
            res->m_MultiMedias.append(multiMedia);
            MultiMedia=MultiMedia->NextSiblingElement("ofd:MultiMedia");
        }
    }
    delete doc;
    return res;
}

int OFDParser::writeImage(const QString &path,const CT_Image &image)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    int ret=0;
    if(doc->LoadFile((path).toLocal8Bit().data()) != tinyxml2::XML_SUCCESS)
        return -1;
    tinyxml2::XMLElement* root = doc->RootElement();
    tinyxml2::XMLElement * Content= root->FirstChildElement("ofd:Content");
    if(Content)
    {
         tinyxml2::XMLElement *Layere = Content->FirstChildElement("ofd:Layer");
         if(Layere)
         {
             tinyxml2::XMLElement* ImageObject = Layere->FirstChildElement("ofd:ImageObject");
             while (ImageObject)
             {
                 if (QString(ImageObject->Attribute("ID")).toInt()== image.m_ID)
                     break;
                 ImageObject = ImageObject->NextSiblingElement("ofd:ImageObject");
             }
             if (!ImageObject)
             {
                 ImageObject = doc->NewElement("ofd:ImageObject");
                 Layere->InsertEndChild(ImageObject);
             }
                   
             ImageObject->SetAttribute("ID",QString::number(image.m_ID).toStdString().c_str());
             ImageObject->SetAttribute("ResourceID",QString::number(image.m_ResourceID).toStdString().c_str());
             QString boundary="%1 %2 %3 %4";
             boundary=boundary.arg(image.m_Boundary.x()).arg(image.m_Boundary.y()).arg(image.m_Boundary.width()).arg(image.m_Boundary.height());
             ImageObject->SetAttribute("Boundary",boundary.toStdString().c_str());
             if(image.m_CTM.size()>5)
             {
                  QString ctm="%1 %2 %3 %4 %5 %6";
                  ctm=ctm.arg(image.m_CTM[0]).arg(image.m_CTM[1]).arg(image.m_CTM[2]).arg(image.m_CTM[3]).arg(image.m_CTM[4]).arg(image.m_CTM[5]);
                  ImageObject->SetAttribute("CTM",ctm.toStdString().c_str());
             }    
         }
    }

    ret=doc->SaveFile((path).toLocal8Bit().data());
    delete  doc;
    return ret;
}

int OFDParser::writeMultiMedia(const QString &ppath, const CT_MultiMedia &res)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    int status=doc->LoadFile((ppath).toLocal8Bit().data());
    if(status == tinyxml2::XML_SUCCESS)
    {
          tinyxml2::XMLElement* root = doc->RootElement();
          tinyxml2::XMLElement * MultiMedias= root->FirstChildElement("ofd:MultiMedias");
          if(!MultiMedias)
          {
             MultiMedias= doc->NewElement("ofd:MultiMedias");
             root->InsertEndChild(MultiMedias);
          }

          tinyxml2::XMLElement* multiMedia = MultiMedias->FirstChildElement("ofd:MultiMedia");
		  while (multiMedia)
		  {
			  if (QString(multiMedia->Attribute("ID")).toInt() == res.m_ID)
				  break;
              multiMedia = multiMedia->NextSiblingElement("ofd:MultiMedia");
		  }
          if (!multiMedia) 
          {
              multiMedia = doc->NewElement("ofd:MultiMedia");
              tinyxml2::XMLElement* mediaFile = doc->NewElement("ofd:MediaFile");
              multiMedia->InsertEndChild(mediaFile);
              MultiMedias->InsertEndChild(multiMedia);
          }
               
          multiMedia->SetAttribute("ID",QString::number(res.m_ID).toStdString().c_str());
          multiMedia->SetAttribute("Type",res.m_Type.toStdString().c_str());
          if(!res.m_Format.isEmpty())
          {
            multiMedia->SetAttribute("Format",res.m_Format.toStdString().c_str());
          }
          if(!res.m_MediaFile.isEmpty())
          {
              tinyxml2::XMLElement* mediaFile = multiMedia->FirstChildElement("ofd:MediaFile");
               mediaFile->SetText(res.m_MediaFile.toLocal8Bit().data());
              
          }    
          int ret=doc->SaveFile((ppath).toLocal8Bit().data());
          delete doc;
          return ret;
    }
    delete doc;
    return -1;
}

int OFDParser::writeRes(const QString &ppath, const Res &res)
{

    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    doc->Parse(declaration);
    tinyxml2::XMLElement* root = doc->NewElement("ofd:Res");
    root->SetAttribute("BaseLoc",res.m_BaseLoc.toLocal8Bit().data());

    doc->InsertEndChild(root);
    int ret=doc->SaveFile(ppath.toLocal8Bit().data());
    delete doc;
    return ret;
}

int OFDParser::writeCommonData(const QString &ppath, const CT_CommonData &data)
{
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    int status=doc->LoadFile((ppath).toLocal8Bit().data());
    if(status!=tinyxml2::XML_SUCCESS)
        return -1;
    tinyxml2::XMLElement* root = doc->RootElement();
    tinyxml2::XMLElement * cdata = root->FirstChildElement("ofd:CommonData");
    if(cdata)
    {
       tinyxml2::XMLElement * mid = cdata->FirstChildElement("ofd:MaxUnitID");
       if(!mid)
       {
           tinyxml2::XMLElement * maxid = doc->NewElement("ofd:MaxUnitID");
           maxid->SetText(QString::number(data.m_MaxUnitID).toStdString().c_str());
           cdata->InsertEndChild(maxid);
       }else{
     //  tinyxml2::XMLText* text = doc->NewText(QString::number(data.m_MaxUnitID).toStdString().c_str());
           mid->SetText(QString::number(data.m_MaxUnitID).toStdString().c_str());
       }
       if(data.m_PublicRes.size()>0)
       {
            tinyxml2::XMLElement * PublicRes = cdata->FirstChildElement("ofd:PublicRes");
            if(!PublicRes)
            {
                tinyxml2::XMLElement * pres = doc->NewElement("ofd:PublicRes");
                pres->SetText(data.m_PublicRes[0].toLocal8Bit().data());
                cdata->InsertEndChild(pres);
            }else{
                PublicRes->SetText(data.m_PublicRes[0].toLocal8Bit().data());
            }
       }
       if(data.m_DocumentRes.size()>0)
       {
            tinyxml2::XMLElement * PublicRes = cdata->FirstChildElement("ofd:DocumentRes");
            if(!PublicRes)
            {
                tinyxml2::XMLElement * pres = doc->NewElement("ofd:DocumentRes");
                pres->SetText(data.m_DocumentRes[0].toLocal8Bit().data());
                cdata->InsertEndChild(pres);
            }else{
                PublicRes->SetText(data.m_DocumentRes[0].toLocal8Bit().data());
            }
       }
    }
    int ret=doc->SaveFile(ppath.toLocal8Bit().data());
    delete doc;
    return ret;
}
