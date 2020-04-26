#ifndef OFDOBJ_H
#define OFDOBJ_H

#include <QString>

class OfdObj
{
public:
    OfdObj();
    virtual ~OfdObj();
    virtual QString toString()const=0;
};

#endif // OFDOBJ_H
