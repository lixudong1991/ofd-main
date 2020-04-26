#ifndef DEFINITIONTYPES_H
#define DEFINITIONTYPES_H

#include <QRectF>
#include <QPointF>
#include <QVector>
#include <QString>
#include "OfdObj.h"

#define atts      public
#define required


#define BtoS(a)            ((a)?"true":"false")
#define QStoB(a)            (((a)=="true")?true:false)

#define ST_Loc          QString
#define ST_Array        QVector
#define ST_ID           int
#define ST_RefID        int
#define ST_Pos          QPointF
#define ST_Box          QRectF


class CT_Dest:public OfdObj
{
public:
    CT_Dest();
    ~CT_Dest()override;
    QString toString() const override;
atts:
    QString m_Type;//XYZ,Fit,FitH,FitV,FitR
    ST_RefID   m_PageID;
    double     m_Left;
    double     m_Top;
    double     m_Right;
    double     m_Bottom;
    double     m_Zoom;
};

class CT_PageArea:public OfdObj
{
public:
    CT_PageArea();
    ~CT_PageArea()override;
    QString toString() const override;
public:
    ST_Box m_PhysicalBox;
    ST_Box m_ApplicationBox;
    ST_Box m_ContentBox;
    ST_Box m_BleedBox;
};


class CT_Region:public OfdObj
{
public:
    CT_Region();
    ~CT_Region()override;
    QString toString() const override;
atts:
    ST_Pos m_Start;
};

class URI:public OfdObj
{
public:
    URI();
    ~URI()override;
    QString toString() const override;
atts:
    QString m_URI;
    QString m_Base;
    QString m_Target;
};
class GotoA:public OfdObj
{
public:
    GotoA();
    ~GotoA()override;
    QString toString() const override;
atts:
    int m_AttachID;
    bool m_NewWindow;
};
class Sound:public OfdObj
{
public:
    Sound();
    ~Sound()override;
    QString toString() const override;
atts:
    ST_RefID m_ResourceID;
    int m_Volume;
    bool m_Repeat;
    bool m_Synchronous;
};
class Movie:public OfdObj
{
public:
    Movie();
    ~Movie()override;
    QString toString() const override;
atts:
    ST_RefID m_ResourceID;
    QString m_Operator;//Play,Stop,Pause,Resume
};
class CT_Action:public OfdObj
{
public:
    CT_Action();
    ~CT_Action()override;
    QString toString() const override;
atts:
    QString m_Event;//DO,PO,CLICK
public:
    CT_Region* m_Region;
    URI* m_URI;
    GotoA* m_GotoA;
    Sound* m_Sound;
    Movie* m_Movie;
};

#endif // DEFINITIONTYPES_H
