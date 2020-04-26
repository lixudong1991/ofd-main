#include "SignaturesTypes.h"

Signatures::Signatures():m_MaxSignId(-1)
{

}

Signatures::~Signatures()
{

}

QString Signatures::toString() const
{
    if(m_MaxSignId==-1&&m_Signatures.size()==0)
    {
        return "";
    }
    QString start="<ofd:Signatures>", end= "</ofd:Signatures>";
    if(m_MaxSignId!=-1)
    {
        start.append(QString::number(m_MaxSignId));
    }
    start.append(end);
    return start;
}
