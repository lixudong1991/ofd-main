#ifndef RESTYPES_H
#define RESTYPES_H

#include "PageTypes.h"

class Palette:public OfdObj
{
public:
    Palette();
    ~Palette()override;
    QString toString() const override;
public:
    QVector<ST_Array<float>*> m_CV;
};


class CT_ColorSpace:public OfdObj
{
public:
    CT_ColorSpace();
    ~CT_ColorSpace()override;
    QString toString() const override;
atts:
    ST_ID   required    m_ID;
    QString required    m_Type;//GRAY,RGB,CMYK
    int     m_BitsPerComonent;
    ST_Loc  m_Profile;
public:
    Palette *m_Palette;
};


class CT_DrawParm:public OfdObj
{
public:
    CT_DrawParm();
    ~CT_DrawParm()override;
    QString toString() const override;
atts:
    ST_ID   required    m_ID;
    ST_RefID m_Relative;
    float    m_LineWidth;
    QString  m_Join;
    QString  m_Cap;
    float    m_DashOffset;
    ST_Array<float> m_DashPattern;
    float   m_MiterLimit;
public:
    CT_Color* m_FillColor;
    CT_Color* m_StrokeColor;
};

class CT_Font:public OfdObj
{
public:
    CT_Font();
    ~CT_Font()override;
    QString toString() const override;
atts:
    ST_ID   required    m_ID;
    QString required m_FontName;
    QString  m_FamilyName;
    QString  m_Charset;
    bool     m_Italic;
    bool    m_Bold;
    bool    m_Serif;
    bool    m_FixedWidth;
public:
    ST_Loc  m_FontFile;

};
class CT_VectorG:public OfdObj
{
public:
    CT_VectorG();
    ~CT_VectorG()override;
    QString toString() const override;
atts:
    ST_ID   required    m_ID;
    float  required m_Width;
    float  required m_Height;
public:
    ST_RefID    m_Thumbnail;
    ST_RefID    m_Substitution;
    CT_PageBlock*   m_Content;
};
class CT_MultiMedia:public OfdObj
{
public:
    CT_MultiMedia();
    ~CT_MultiMedia()override;
    QString toString() const override;
atts:
    ST_ID   required    m_ID;
    QString    required   m_Type; //Image,Audio,Video
    QString               m_Format;
public:
    ST_Loc        m_MediaFile;
};

class Res:public OfdObj
{
public:
    Res();
    ~Res()override;
    QString toString() const override;
atts:
    ST_Loc  required m_BaseLoc;
public:
    QVector<CT_ColorSpace*> m_ColorSpaces;
    QVector<CT_DrawParm*> m_DrawParms;
    QVector<CT_Font*> m_Fonts;
    QVector<CT_VectorG*> m_CompositeGraphicUnits;
    QVector<CT_MultiMedia*> m_MultiMedias;
};


#endif // RESTYPES_H
