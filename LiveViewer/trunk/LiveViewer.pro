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
BOOST_INCLUDE = "/usr/local/boost/include"
BOOST_LIBS = "/usr/local/boost/lib"
EPICS_BASE = "/usr/local/epics/base"
EPICS_HOST_ARCH = "linux-x86_64"
EPICS_TARGET_OS = "linux-x86_64"
GSTAR_INCLUDE = "/usr/local/GStar/include"
GSTAR_LIBS = "/usr/local/GStar/lib"
SSTAR_INCLUDE = "/usr/local/sstar/trunk/include"
SSTAR_LIBS = "/usr/local//sstar/trunk/bin"

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += release
CONFIG += ordered
DEFINES += QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include files for this project
INCLUDEPATH += include

# External library includes
INCLUDEPATH += $${BOOST_INCLUDE}
INCLUDEPATH += $${EPICS_BASE}/include
INCLUDEPATH += $${EPICS_BASE}/include/os/$${EPICS_TARGET_OS}
INCLUDEPATH += $${GSTAR_INCLUDE}
INCLUDEPATH += $${SSTAR_INCLUDE}

# System dependent library paths
macx::!unix {
   LIBS += $${BOOST_LIBS}/libboost_thread.a
   LIBS += -L$${EPICS_BASE}/lib/$${EPICS_HOST_ARCH} -lca
   LIBS += -L$${GSTAR_LIBS} -lGStar
   LIBS += -L$${SSTAR_LIBS} -lsstar
}
unix::!macx {
   LIBS += $${BOOST_LIBS}/libboost_thread.a
   LIBS += -L$${EPICS_BASE}/lib/$${EPICS_HOST_ARCH} -lca
   LIBS += -L$${GSTAR_LIBS} -lGStar
   LIBS += -L$${SSTAR_LIBS} -lsstar
}
win32: {
   LIBS += $${BOOST_LIBS}/libboost_thread-vc100-mt-1_49.lib
   LIBS += $${BOOST_LIBS}/libboost_date_time-vc100-mt-1_49.lib
   LIBS += $${EPICS_BASE}/lib/$${EPICS_HOST_ARCH}/ca.lib
   LIBS += $${GSTAR_LIBS}/GStar.lib
   LIBS += $${SSTAR_LIBS}/libsstar.lib
}

# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = LiveViewer.qrc

# Include actual project
include(LiveViewer.pri)
