# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
# Qt template
TEMPLATE = app

# Project name
TARGET = LiveViewer

# Qt components
QT += core \
    gui

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += Debug
DEFINES += QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include

# System dependent include and library paths
macx:
unix:
win32:

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = LiveViewer.qrc

# Include actual project
include(LiveViewer.pri)
