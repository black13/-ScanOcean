# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
# Qt template
TEMPLATE = lib

# Project name
TARGET = GStar

# Qt components
QT += core \
      gui

# Destination build directory
DESTDIR = ./lib

# Release or Debug
CONFIG += staticlib release
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include
INCLUDEPATH += include/Annotation

# Platform dependent include paths
macx:
unix:

# Platform dependent library paths and libraries
macx:
unix:

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = GStar.qrc

# Include actual project
include(GStar.pri)
