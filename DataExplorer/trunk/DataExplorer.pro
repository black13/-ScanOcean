# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.

# Qt template
TEMPLATE = app

# Project name
TARGET = DataExplorer

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

# Platform dependent include paths
macx {
	INCLUDEPATH += /usr/local/hdf5/include
	INCLUDEPATH += /usr/local/boost
}
unix {
	INCLUDEPATH += /usr/local/hdf5/include
}

# Platform dependent library paths and libraries
macx {
	QMAKE_LIBDIR += /usr/local/hdf5/lib
}
unix {
	QMAKE_LIBDIR += /usr/local/hdf5/lib
	LIBS += -lhdf5
	LIBS += -lz
}

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = DataExplorer.qrc

# Include actual project
include(DataExplorer.pri)
