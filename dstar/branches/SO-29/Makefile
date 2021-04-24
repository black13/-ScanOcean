CC = g++

CXXFLAGS = -Wall -g -fPIC

INCLUDES = -I/local/fkhan/hdf5/include -I./include

LFLAGS = -L/local/fkhan/hdf5/lib

LIBS = -lhdf5

SRCS = src/HDF5DataScalar.cpp src/AbstractAttribute.cpp src/AbstractGroup.cpp src/HDF5Object.cpp src/HDF5Data.cpp src/Selection.cpp src/HDF5File.cpp src/AbstractData.cpp src/HDF5DataSimple.cpp src/AbstractView.cpp src/HDF5Group.cpp src/AbstractObject.cpp src/HDF5Attribute.cpp

OBJS = $(SRCS:.cpp=.o)

DSTAR_LIB = dstar-1.so

.PHONY: depend clean

all: $(DSTAR_LIB)

$(DSTAR_LIB): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -shared -o $(DSTAR_LIB) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

distclean:
	$(RM) src/*.o *~ $(DSTAR_LIB)


depend: $(SRCS)
	makedepend $(INCLUDES) $^


