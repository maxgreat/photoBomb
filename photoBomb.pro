#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T15:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_LIBS += `pkg-config opencv --libs`
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu/

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wunused-result
QMAKE_LFLAGS_RELEASE -= -O1

TARGET = photoBomb
TEMPLATE = app

unix:INCLUDEPATH += "/usr/include"

unix:LIBS += -L /usr/lib/


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
