#ifndef PAGETYPES_H
#define PAGETYPES_H

#include "DefinitionTypes.h"

class CT_Path;
class CT_Text;
class CT_Pattern;
class CT_AxialShd;
class CT_RadialShd;
class CT_GouraudShd;
class CT_LaGouraudShd;
class PageBlock;
class CT_PageBlock;
class CT_CGTransform;
class CellContent;
class CT_Color;

class CT_Pattern:public OfdObj
{
public:
    CT_Pattern();
    ~CT_Pattern()override;
    QString toString() const override;
atts:
    float   required    m_Width;
    float   required    m_Height;
    float   m_XStep;
    float   m_YStep;
    QString     m_ReflectMethod;//Normal,Row,Column,RowAndColumn
    QString     m_RelativeTo;//Page,Object;
    ST_Array<float>     m_CTM;
public:
    CellContent*   m_CellContent;
};

class Segment:public OfdObj
{
public:
    Segment();
    ~Segment()override;
    QString toString() const override;
atts:
    float m_Position;
public:
    CT_Color*   m_Color;
};

class CT_AxialShd:public OfdObj
{
public:
    CT_AxialShd();
    ~CT_AxialShd()override;
    QString toString() const override;
atts:
    ST_Pos  required StartPoint;
    ST_Pos  required EndPoint;
    int m_Extend;
    float   m_MapUnit;
    QString m_MapType;//Direct,Repeat,Reflect
public:
    QVector<Segment*>   m_Segment;
};

class CT_RadialShd:public OfdObj
{
public:
    CT_RadialShd();
    ~CT_RadialShd()override;
    QString toString() const override;
atts:
    ST_Pos  required StartPoint;
    ST_Pos  required EndPoint;
    float   required m_EndRadius;
    float    m_StartRadius;
    int m_Extend;
    float m_Angle;
    float   m_Eccentricity;
    float   m_MapUnit;
    QString m_MapType;//Direct,Repeat,Reflect
public:
    QVector<Segment*>   m_Segment;
};

class Point:public OfdObj
{
public:
    Point();
    ~Point()override;
    QString toString() const override;
atts:
    float required m_X;
    float required m_Y;
    int required  m_EdgeFlag;//0,1,2
public:
    CT_Color* m_Color;
};

class CT_GouraudShd:public OfdObj
{
public:
    CT_GouraudShd();
    ~CT_GouraudShd()override;
    QString toString() const override;
atts:
    int m_Extend;
public:
    QVector<Point*> m_Point;
    CT_Color*   m_BackColor;
};

class CT_LaGouraudShd:public OfdObj
{
public:
    CT_LaGouraudShd();
    ~CT_LaGouraudShd()override;
    QString toString() const override;
atts:
    int required m_VerticesPerRow;
    int m_Extend;
public:
    QVector<Point*> m_Point;
    CT_Color*   m_BackColor;
};


class CT_Color:public OfdObj
{
public:
    CT_Color();
    ~CT_Color()override;
    QString toString() const override;
atts:
    ST_Array<int> m_Value;
    int  m_Index;
    ST_RefID    m_ColorSpace;
    int     m_Alpha;
public:
    CT_Pattern *m_Pattern;
    CT_AxialShd *m_AxialShd;
    CT_RadialShd *m_RadialShd;
    CT_GouraudShd *m_GouraudShd;
    CT_LaGouraudShd *m_LaGouraudShd;
};
class Area:public OfdObj
{
public:
    Area();
    ~Area()override;
    QString toString() const override;
atts:
    ST_RefID    m_DrawParam;
    ST_Array<float> m_CTM;
public:
    CT_Path *m_Path;
    CT_Text *m_Text;
};

class CT_Clip:public OfdObj
{
public:
    CT_Clip();
    ~CT_Clip()override;
    QString toString() const override;
public:
    QVector<Area*> m_Area;
};

class CT_GraphicUnit:public OfdObj
{
public:
    CT_GraphicUnit();
    ~CT_GraphicUnit()override;
    QString toString() const override=0;
atts:
    ST_Box  required m_Boundary;
    QString m_Name;
    bool    m_Visible;
    ST_Array<float>  m_CTM;
    ST_RefID    m_DrawParam;
    float       m_LineWidth;
    QString     m_Cap;//Butt,Round,Square
    QString     m_Join;//Miter,Round,Bevel
    float       m_MiterLimit;
    float       m_DashOffset;
    ST_Array<float> m_DashPattern;
    int         m_Alpha;
public:
    QVector<CT_Action*>  m_Actions;
    QVector<CT_Clip*>    m_Clips;
};


class CT_Path:public CT_GraphicUnit
{

public:
    CT_Path();
    ~CT_Path()override;
    QString toString() const override;
atts:
    ST_ID  required  m_ID;
    bool     m_Stroke;
    bool     m_Fill;
    QString  m_Rule;//NonZero,Even-Odd
public:
    CT_Color*  m_StrokeColor;
    CT_Color*  m_FillColor;
    QString   m_AbbreviatedData;
};

class TextCode:public OfdObj
{

public:
    TextCode();
    ~TextCode()override;
    QString toString() const override;
atts:
    float     m_X;
    float     m_Y;
    ST_Array<float>     m_DeltaX;
    ST_Array<float>     m_DeltaY;
public:
    QString m_Val;
};

class CT_Text:public CT_GraphicUnit
{
public:
    CT_Text();
    ~CT_Text()override;
    QString toString() const override;
atts:
    ST_ID  required  m_ID;
    ST_RefID    required m_Font;
    float   required    m_Size;
    bool        m_Stroke;
    bool        m_Fill;
    bool        m_HScale;
    int         m_ReadDirection;
    int         m_CharDirection;
    int         m_Weight;//0,100,200,300,400,500,600,700,800,900,1000
    bool        m_Italic;
public:
    CT_Color*    m_FillColor;
    CT_Color*    m_StrokeColor;
    QVector<CT_CGTransform*> m_CGTransform;
    QVector<TextCode*>    m_TextCode;
};
class CT_CGTransform:public OfdObj
{
public:
    CT_CGTransform();
    ~CT_CGTransform()override;
    QString toString() const override;
atts:
    int required m_CodePosition;
    int m_CodeCount;
    int m_GlyphCount;
public:
    ST_Array<float>   m_Glyphs;
};



class Border:public OfdObj
{
public:
    Border();
    ~Border()override;
    QString toString() const override;
atts:
    float  m_LineWidth;
    float  m_HorizonalCornerRadius;
    float  m_VerticalCornerRadius;
    float  m_DashOffset;
    ST_Array<float> m_DashPattern;
public:
    CT_Color*  m_BorderColor;
};


class CT_Image:public CT_GraphicUnit
{
public:
    CT_Image();
    ~CT_Image()override;
    QString toString() const override;
atts:
    ST_ID  required  m_ID;
    ST_RefID required m_ResourceID;
    ST_RefID m_Substitution;
    ST_RefID m_ImageMask;
public:
    Border* m_Border;
};
class CT_Composite:public CT_GraphicUnit
{
public:
    CT_Composite();
    ~CT_Composite()override;
    QString toString() const override;
atts:
    ST_ID  required  m_ID;
    ST_RefID required m_ResourceID;
};


class Template:public OfdObj
{
public:
    Template();
    ~Template()override;
    QString toString() const override;
atts:
    ST_RefID  required  m_TemplateID;
    QString   m_ZOrder;//Background,Foreground
};


class CT_PageBlock:public OfdObj
{
public:
    CT_PageBlock();
    ~CT_PageBlock()override;
    QString toString() const override;
public:
    QVector<CT_Text*> m_TextObject;
    QVector<CT_Path*> m_PathObject;
    QVector<CT_Image*> m_ImageObject;
    QVector<CT_Composite*> m_CompositeObject;
    QVector<PageBlock*> m_PageBlock;
};

class CellContent:public CT_PageBlock
{
public:
    CellContent();
    ~CellContent()override;
    QString toString() const override;
atts:
    ST_RefID    m_Thumbnail;
};

class PageBlock:public CT_PageBlock
{
public:
    PageBlock();
    ~PageBlock()override;
    QString toString() const override;
atts:
    ST_ID  required  m_ID;
};

/*
class CT_Layer:public CT_PageBlock
{
public:
    CT_Layer();
    ~CT_Layer()override;
    QString toString() const override;
attributes:

};*/

class Layer:public CT_PageBlock
{
public:
    Layer();
    ~Layer()override;
    QString toString() const override;
atts:
    QString     m_Type;//Body,Background,Foreground,Custom
    ST_RefID    m_DrawParam;
    ST_ID required  m_ID;
};


class Page:public OfdObj
{
public:
    Page();
    ~Page()override;
    QString toString() const override;
public:
    QVector<Template*> m_Template;
    QVector<ST_Loc>   m_PageRes;
    CT_PageArea* m_Area;
    QVector<Layer*> m_Content;
    QVector<CT_Action*> m_Actions;
};



#endif // PAGETYPES_H
