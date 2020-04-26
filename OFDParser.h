#ifndef OFDPARSER_H
#define OFDPARSER_H
#include <QString>
#include <QPixmap>
#include <tinyxml2.h>
#include "ofdtypes/OFDTypes.h"
#include "ofdtypes/DocumentTypes.h"
#include "ofdtypes/ResTypes.h"
#include "ofdtypes/PageTypes.h"

class OFDParser
{
public:
    OFDParser();
    ~OFDParser();
    static OFDParser *getInstance();
    void parser(const QString &path);
    void Decompress(const QString &path);
    void ComPress(const QString &path);
    OFD *getOFDdoc();
    Document *getDocument(const ST_Loc &path);
    Page *getPage(const ST_Loc &path);
    Res* getRes(const QString &ppath,const ST_Loc &path);
    inline QString getOfdPath()const {
        return m_path;
    }
    int writeImage(const QString &ppath,const CT_Image &image);
    int writeMultiMedia(const QString &ppath,const CT_MultiMedia &res);
    int writeRes(const QString &ppath,const Res &res);
    int writeCommonData(const QString &ppath,const CT_CommonData &data);
private:
    QString m_path;
    static OFDParser *m_instance;
};

#endif // OFDPARSER_H
