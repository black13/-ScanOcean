# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
QT += core \
    gui
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = Annotation
TEMPLATE = app

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += debug
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter
INCLUDEPATH += include
INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/Annotation

# Library paths
QMAKE_LIBDIR += ../../lib
LIBS += -lGStar

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# include actual project
include(Annotation.pri)
HEADERS = include/AnnotationDisplayWidget.h \
    ../../include/AbstractImageWidget.h \
    ../../include/Annotation/AbstractGraphicsItem.h \
    ../../include/Annotation/EmptyGraphicsItem.h \
    ../../include/Annotation/IntensityLineGraphicsItem.h \
    ../../include/Annotation/IntensityPieGraphicsItem.h \
    ../../include/Annotation/LineGraphicsItem.h \
    ../../include/Annotation/MarkerGraphicsItem.h \
    ../../include/Annotation/PieGraphicsItem.h \
    ../../include/Annotation/RulerGraphicsItem.h \
    ../../include/AnnotationProperty.h \
    ../../include/AnnotationToolBarWidget.h \
    ../../include/AnnotationTreeModel.h \
    ../../include/RulerUnitsDialog.h
RESOURCES = AnnotationRes.qrc
SOURCES = src/AnnotationDisplayWidget.cpp \
    src/main.cpp \
    ../../src/AbstractImageWidget.cpp \
    ../../src/Annotation/AbstractGraphicsItem.cpp \
    ../../src/Annotation/EmptyGraphicsItem.cpp \
    ../../src/Annotation/IntensityLineGraphicsItem.cpp \
    ../../src/Annotation/IntensityPieGraphicsItem.cpp \
    ../../src/Annotation/LineGraphicsItem.cpp \
    ../../src/Annotation/MarkerGraphicsItem.cpp \
    ../../src/Annotation/PieGraphicsItem.cpp \
    ../../src/Annotation/RulerGraphicsItem.cpp \
    ../../src/AnnotationProperty.cpp \
    ../../src/AnnotationToolBarWidget.cpp \
    ../../src/AnnotationTreeModel.cpp \
    ../../src/RulerUnitsDialog.cpp
