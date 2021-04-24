# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
# Qt template
TEMPLATE = app

# Project name
TARGET = LiveViewer

# Qt components
QT += core \
    gui

# External library directories
GSTAR_DIR = "../trunk/gstar"

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include
INCLUDEPATH += $${GSTAR_DIR}/include

# System dependent include and library paths
macx:
unix::!macx {
	LIBS += -L/usr/lib/boost -lboost_thread-mt
	LIBS += -L$${GSTAR_DIR}/lib -lGStar
}
win32:


# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = LiveViewer.qrc

# Include actual project
include(LiveViewer.pri)
