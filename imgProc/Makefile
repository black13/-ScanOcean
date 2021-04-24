

all: example shared static
   
clean: example-clean shared-clean static-clean

example: Makefile.example
	make -f Makefile.example -j8

example-clean: Makefile.example
	make -f Makefile.example clean

shared: Makefile.shared
	make -f Makefile.shared -j8

shared-clean: Makefile.shared
	make -f Makefile.shared clean

static: Makefile.static
	make -f Makefile.static -j8

static-clean: Makefile.static
	make -f Makefile.static clean
