QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    OFDParser.cpp \
    OfdMainWidget.cpp \
    UnitTool.cpp \
    ZipTool.cpp \
    diagramscene/OFDPage.cpp \
    diagramscene/OFDScene.cpp \
    diagramscene/diagramimageitem.cpp \
    diagramscene/diagrampathitem.cpp \
    diagramscene/diagramtextitem.cpp \
    diagramscene/docpassage.cpp \
    main.cpp \
    ofdtypes/AnnotationTypes.cpp \
    ofdtypes/AnnotationsTypes.cpp \
    ofdtypes/AttachmentsTypes.cpp \
    ofdtypes/CustomTagsTypes.cpp \
    ofdtypes/DefinitionTypes.cpp \
    ofdtypes/ExtensionsTypes.cpp \
    ofdtypes/PageTypes.cpp \
    ofdtypes/ResTypes.cpp \
    ofdtypes/SignatureTypes.cpp \
    ofdtypes/SignaturesTypes.cpp \
    ofdtypes/VersionTypes.cpp \
    ofdtypes/DocumentTypes.cpp \
    OfdObj.cpp \
    ofdtypes/OFDTypes.cpp \
    tinyxml2.cpp
HEADERS += \
    OFDParser.h \
    OfdMainWidget.h \
    UnitTool.h \
    ZipTool.h \
    diagramscene/OFDPage.h \
    diagramscene/OFDScene.h \
    diagramscene/diagramimageitem.h \
    diagramscene/diagrampathitem.h \
    diagramscene/diagramtextitem.h \
    diagramscene/docpassage.h \
    ofdtypes/AnnotationTypes.h \
    ofdtypes/AnnotationsTypes.h \
    ofdtypes/AttachmentsTypes.h \
    ofdtypes/CustomTagsTypes.h \
    ofdtypes/DefinitionTypes.h \
    ofdtypes/ExtensionsTypes.h \
    ofdtypes/PageTypes.h \
    ofdtypes/ResTypes.h \
    ofdtypes/SignatureTypes.h \
    ofdtypes/SignaturesTypes.h \
    ofdtypes/VersionTypes.h \
    ofdtypes/DocumentTypes.h \
    OfdObj.h \
    ofdtypes/OFDTypes.h \
    tinyxml2.h

INCLUDEPATH += $$PWD/includes/ \
               $$PWD/diagramscene



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG += debug_and_release
CONFIG(debug, debug|release){
MOC_DIR += \
           debug/moc
OBJECTS_DIR += \
           debug/obj
RCC_DIR += \
            debug/rcc
LIBS += -L$$PWD/share/debug -lquazipd
} else {
MOC_DIR += \
           release/moc
OBJECTS_DIR += \
           release/obj
RCC_DIR += \
           release/rcc
LIBS += -L$$PWD/share/release -lquazip
}

RESOURCES += \
    ofd.qrc

FORMS +=
