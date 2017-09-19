#-------------------------------------------------
#
# Project created by QtCreator 2016-09-02T14:45:35
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathTracer
TEMPLATE = app
OBJECTS_DIR = obj
MOC_DIR = moc


SOURCES  += $$PWD/viewer/src/main.cpp\
            $$PWD/viewer/src/MainWindow.cpp \
            $$PWD/viewer/src/PathTraceWidget.cpp \
            $$PWD/PT/src/PathTracer.cpp \
            $$PWD/PT/src/Light.cpp \
            $$PWD/PT/src/Sphere.cpp \
    PT/src/Scene.cpp \
    PT/src/Image.cpp \
    PT/src/Primitive.cpp

HEADERS  += $$PWD/viewer/include/MainWindow.h \
            $$PWD/viewer/include/PathTraceWidget.h \
            $$PWD/PT/include/PathTracer.h \
            $$PWD/PT/include/Utility.h \
            $$PWD/PT/include/Primitive.h \
            $$PWD/PT/include/Light.h \
            $$PWD/PT/include/Sphere.h \
    PT/include/Scene.h \
    PT/include/Image.h \
    PT/include/Primitive.h

FORMS    += $$PWD/ui/MainWindow.ui

INCLUDEPATH +=  $$PWD/viewer/include/ \
                $$PWD/PT/include
