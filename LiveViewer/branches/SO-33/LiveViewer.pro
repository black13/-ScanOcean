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
GSTAR_DIR = "../gstar"
EPICS_BASE = "/usr/local/epics/base"
EPICS_HOST_ARCH = "linux-x86_64"
#EPICS_BASE = "/APSshare/epics/base-3.14.12.1"
#EPICS_HOST_ARCH = "linux-x86_64-el6-debug"
BOOST_INCLUDE = /usr/include
BOOST_LIBS = /usr/lib64

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += include

# System dependent include and library paths
macx::!unix {

   # Includes
   INCLUDEPATH += $${BOOST_INCLUDE}
   INCLUDEPATH += $${EPICS_BASE}/include
   INCLUDEPATH += $${EPICS_BASE}/include/os/Linux
   INCLUDEPATH += $${GSTAR_DIR}/include

   # Libraries
   LIBS += $${BOOST_LIBS}/libboost_thread.a
   LIBS += -L$${EPICS_BASE}/lib/$${EPICS_HOST_ARCH} -lca
   LIBS += -L$${GSTAR_DIR}/lib -lGStar
   
}
unix::!macx {

   # Includes
   INCLUDEPATH += $${EPICS_BASE}/include
   INCLUDEPATH += $${EPICS_BASE}/include/os/Linux
   INCLUDEPATH += $${GSTAR_DIR}/include

   # Libraries
   LIBS += -L$${EPICS_BASE}/lib/$${EPICS_HOST_ARCH} -lca
   LIBS += -L$${BOOST_LIBS} -lboost_thread-mt
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
