#ifndef OFDXMLTYPES_H
#define OFDXMLTYPES_H
#include "OfdObj.h"
#include "DefinitionTypes.h"


class Version:public OfdObj
{
public:
    Version();
    ~Version()override;
    QString toString() const override;
atts:
    int required  m_ID;
    int required  m_Index;
    bool m_Current;
    ST_Loc required m_BaseLoc;
};

class CustomData:public OfdObj
{
public:
    CustomData();
    ~CustomData()override;
    QString toString() const override;
atts:
    QString required m_Name;
public:
    QString m_Value;
};

class CT_DocInfo:public OfdObj
{
public:
    CT_DocInfo();
    ~CT_DocInfo()override;
    QString toString() const override;
public:
    QString m_DocID;
    QString m_Title;
    QString m_Author;
    QString m_Subject;
    QString m_Abstract;
    QString m_CreationDate;
    QString m_ModDate;
    QString m_DocUsage;
    ST_Loc  m_Cover;
    QVector<QString>  m_Keywords;
    QString m_Creator;
    QString m_CreatorVersion;
    QVector<CustomData*> m_CustomDatas;
};
class DocBody:public OfdObj
{
public:
    DocBody();
    ~DocBody()override;
    QString toString() const override;
public:
    CT_DocInfo* m_DocInfo;
    ST_Loc  m_DocRoot;
    QVector<Version*> m_Versions;
    ST_Loc  m_Signatures;
};
class OFD:public OfdObj
{
public:
    OFD();
    ~OFD()override;
    QString toString() const override;
atts:
    QString m_Version;
    QString m_DocType;
public:
    QVector<DocBody*> m_DocBody;
};

#endif // OFDXMLTYPES_H
