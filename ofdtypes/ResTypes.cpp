#include "ResTypes.h"

Palette::Palette()
{

}

Palette::~Palette()
{

}

QString Palette::toString() const
{
    return "";
}

CT_ColorSpace::CT_ColorSpace():
   m_BitsPerComonent(8),m_Palette(nullptr)
{

}

CT_ColorSpace::~CT_ColorSpace()
{

}

QString CT_ColorSpace::toString() const
{

  return "";
}

CT_DrawParm::CT_DrawParm():
    m_LineWidth(0.353f),m_Join("Miter"),m_Cap("Butt"),m_DashOffset(0),m_MiterLimit(4.234f),
    m_FillColor(nullptr),m_StrokeColor(nullptr)
{


}

CT_DrawParm::~CT_DrawParm()
{

}

QString CT_DrawParm::toString() const
{
  return "";
}

CT_Font::CT_Font():
    m_Charset("unicode"),m_Italic(false)
  ,m_Bold(false),m_Serif(false),m_FixedWidth(false)
{


}

CT_Font::~CT_Font()
{

}

QString CT_Font::toString() const
{
  return "";
}

CT_VectorG::CT_VectorG():m_Content(nullptr)
{

}

CT_VectorG::~CT_VectorG()
{

}

QString CT_VectorG::toString() const
{
  return "";
}

Res::Res()
{

}

Res::~Res()
{

}

QString Res::toString() const
{
  return "";
}

CT_MultiMedia::CT_MultiMedia()
{

}

CT_MultiMedia::~CT_MultiMedia()
{

}

QString CT_MultiMedia::toString() const
{
    return "";
}
