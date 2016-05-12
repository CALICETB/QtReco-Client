#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T17:12:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OnlineMonitorClient
TEMPLATE = app

SOURCES += src/main.cpp\
    src/GuiClient.cpp \
    src/QRootCanvas.cpp \
    src/TCPClient.cpp \
    src/Logger.cpp \
    src/QCanvasWidget.cpp

HEADERS  += \
    include/GuiClient.h \
    include/QRootCanvas.h \
    include/TCPClient.h \
    include/Logger.h \
    include/QCanvasWidget.h

FORMS    += \
    ui/GuiClient.ui

INCLUDEPATH += $(ROOTSYS)/include \
include

LIBS += -L$(ROOTSYS)/lib -Wl,--no-as-needed -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree \
-lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lm -ldl -rdynamic \

CONFIG += x86_64
