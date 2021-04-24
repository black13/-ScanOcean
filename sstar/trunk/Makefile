

all: shared static
   
clean: shared-clean static-clean

shared: Makefile.shared
	make -f Makefile.shared

shared-clean: Makefile.shared
	make -f Makefile.shared clean

static: Makefile.static
	make -f Makefile.static

static-clean: Makefile.static
	make -f Makefile.static clean
