#ifndef DOCUMENTTYPES_H
#define DOCUMENTTYPES_H

#include "DefinitionTypes.h"


class CT_TemplatePage:public OfdObj
{
public:
    CT_TemplatePage();
    ~CT_TemplatePage()override;
    QString toString() const override;
atts:
    ST_ID m_ID;
    QString m_Name;
    QString m_ZOrder;   //可取值Background,Foreground
    ST_Loc  m_BaseLoc;
};
class CT_CommonData:public OfdObj
{
public:
    CT_CommonData();
    ~CT_CommonData()override;
    QString toString() const override;
public:
    ST_ID m_MaxUnitID;
    CT_PageArea* m_PageArea;
    QVector<ST_Loc> m_PublicRes;
    QVector<ST_Loc> m_DocumentRes;
    QVector<CT_TemplatePage*> m_TemplatePage;
    ST_RefID m_DefaultCS;
};
class CT_Page:public OfdObj
{
public:
    CT_Page();
    ~CT_Page()override;
    QString toString() const override;
atts:
    ST_ID m_ID;
    ST_Loc  m_BaseLoc;
};

class Print:public OfdObj
{
public:
    Print();
    ~Print()override;
    QString toString() const override;
atts:
    bool m_Printable;
    int  m_Copies;
};

class ValidPeriod:public OfdObj
{
public:
    ValidPeriod();
    ~ValidPeriod()override;
    QString toString() const override;
atts:
    QString m_StartDate;
    QString m_EndDate;
};
class CT_Permission:public OfdObj
{
public:
    CT_Permission();
    ~CT_Permission()override;
    QString toString() const override;
public:
    bool m_Edit;
    bool m_Annot;
    bool m_Export;
    bool m_Signature;
    bool m_Watermark;
    bool m_PrintScreen;
    Print* m_Print;
    ValidPeriod* m_ValidPeriod;
};




class CT_OutlineElem:public OfdObj
{
public:
    CT_OutlineElem();
    ~CT_OutlineElem()override;
    QString toString() const override;
atts:
    QString m_Title;
    int     m_Count;
    bool    m_Expanded;
public:
    QVector<CT_Action*> m_Actions;
};

class CT_VPreferences:public OfdObj
{
public:
    CT_VPreferences();
    ~CT_VPreferences()override;
    QString toString() const override;
public:
    QString m_PageMode; //None,FullScree,UseOutlines,UseThumbs,UseCustomTags,UseLayers,UseAttatchs,UseBookmarks
    QString m_PageLayout;//OnePage,OneColumn,TwoPageL,TwoColumnL,TwoPageR,TwoColumnR
    QString m_TabDisplay;//DocTitle,FileName
    bool    m_HideToolbar;
    bool    m_HideMenubar;
    bool    m_HideWindowUI;
    QString m_ZoomMode; //Default,FitHeight,FitWidth,FitRect
    double m_Zoom;
};


class CT_Bookmark:public OfdObj
{
public:
    CT_Bookmark();
    ~CT_Bookmark()override;
    QString toString() const override;
atts:
    QString m_Name;
public:
    CT_Dest* m_Dest;
};

class Document:public OfdObj
{
public:
    Document();
    ~Document()override;
    QString toString() const override;
public:
    CT_CommonData* m_CommonData;
    QVector<CT_Page*> m_Pages;
    QVector<CT_OutlineElem*> m_Outlines;
    CT_Permission* m_Permissions;
    QVector<CT_Action*> m_Actions;
    CT_VPreferences* m_VPreferences;
    QVector<CT_Bookmark*> m_Bookmarks;
    ST_Loc  m_Annotations;
    ST_Loc  m_CustomTags;
    ST_Loc  m_Attachments;
    ST_Loc  m_Extensions;
};

#endif // DOCUMENTTYPES_H
