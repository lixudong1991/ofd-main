#ifndef SIGNATURESTYPES_H
#define SIGNATURESTYPES_H
#include "DefinitionTypes.h"
#include "OfdObj.h"

class Signature:public OfdObj
{
public:
    Signature();
    ~Signature()override;
    QString toString() const override;
public:
    int m_ID;
    QString m_Type;
    ST_Loc  m_BaseLoc;
};

class Signatures:public OfdObj
{
public:
    Signatures();
    ~Signatures()override;
    QString toString() const override;
public:
    int m_MaxSignId;
    QVector<Signature>  m_Signatures;
};


#endif // SIGNATURESTYPES_H
