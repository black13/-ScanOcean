# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
# Qt template
TEMPLATE = app

# Project name
TARGET = ColorTransferFunction

# Qt components
QT += core \
      gui

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += release
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include
INCLUDEPATH += ../../include

# Library paths
QMAKE_LIBDIR += ../../lib
LIBS += -lGStar

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Include actual project
include(ColorTransferFunction.pri)
