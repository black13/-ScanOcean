# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

#include actual project
include(Annotation.pri)
