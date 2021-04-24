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
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include

# System dependent include and library paths
macx:
unix::!macx {

	# Includes
	INCLUDEPATH += /local/faisal/EPICS/base/include
	INCLUDEPATH += /local/faisal/EPICS/base/include/os/Linux

	# Libraries
	LIBS += -L /local/faisal/EPICS/base/lib/linux-x86_64 -lca
	LIBS += -L/usr/lib64 -lboost_thread-mt

}
win32:


# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = LiveViewer.qrc

# Include actual project
include(LiveViewer.pri)
