# Copyright (c) 2012, UChicago Argonne, LLC
# See LICENSE file.
# Qt template
TEMPLATE = lib

# Project name
TARGET = GStar

# Qt components
QT += core \
      gui \
	  widgets

# Destination build directory
DESTDIR = ./lib

# Release or Debug
CONFIG += staticlib release
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter
#debug only
#QMAKE_CXXFLAGS += /D_ITERATOR_DEBUG_LEVEL=2

# Include paths
INCLUDEPATH += include
INCLUDEPATH += include/Annotation

# Platform dependent include paths
macx {
BOOST_INCLUDE ="${BOOST_BASE}/include"
INCLUDEPATH += $${BOOST_INCLUDE}
}
unix:
win32 {
BOOST_INCLUDE="%BOOST_BASE%"

INCLUDEPATH += $${BOOST_INCLUDE}
QMAKE_CXXFLAGS += /Gs999999 

}
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
