#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T15:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE += -O3

TARGET = photoBomb
TEMPLATE = app

#include opencv
#win32:INCLUDEPATH += "D:\install\opencv\build\install\include"
#win64:
unix:INCLUDEPATH += "/usr/include"


#win32:LIBS += -L D:/install/opencv/build/install/x64/mingw/lib/
#win32:LIBS += libopencv_core248d
#win32:LIBS += libopencv_imgproc248d
#win32:LIBS += libopencv_highgui248d

#win64:LIBS += -L D:/install/opencv/build/install/x64/mingw/lib/
#win64:LIBS += libopencv_core248d
#win64:LIBS += libopencv_imgproc248d
#win64:LIBS += libopencv_highgui248d


unix:LIBS += -L /usr/lib/
unix:LIBS += lopencv_core248d
unix:LIBS += lopencv_imgproc248d
unix:LIBS += lopencv_highgui248d





SOURCES += main.cpp\
        mainwindow.cpp \
    lib/zonecentrale.cpp \
    lib/fenetrehistogramme.cpp \
    lib/imageRGB.cpp \
    lib/lumetcont.cpp \
    lib/fenetretaille.cpp \
    lib/operationsBasiques.cpp \
    lib/preferences.cpp \
    lib/fenetreinfo.cpp

HEADERS  += mainwindow.h \
    lib/zonecentrale.h \
    lib/fenetrehistogramme.h \
    lib/imageRGB.h \
    lib/lumetcont.h \
    lib/fenetretaille.h \
    lib/operationsBasiques.h \
    lib/preferences.h \
    lib/fenetreinfo.h
FORMS += mainwindow.ui