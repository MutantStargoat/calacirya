src = $(wildcard src/*.cc)
obj = $(src:.cc=.o)
dep = $(obj:.o=.d)
bin = calagl

libdir = ..
inc = -I$(libdir)/src -I$(libdir)/libs

CFLAGS = -pedantic -Wall -g $(inc)
CXXFLAGS = -std=c++11 $(CFLAGS)
LDFLAGS = $(lib) $(libgl) -Wl,-rpath=$(libdir)

ifeq ($(shell uname -s), Darwin)
	libgl = -framework OpenGL -framework GLUT
	lib = $(libdir)/libcalacirya.dylib
else
	libgl = -lGL -lglut
	lib = $(libdir)/libcalacirya.so.0.1
endif

$(bin): $(obj) Makefile
	$(CXX) -o $@ $(obj) $(LDFLAGS)

-include $(dep)

%.d: %.cc
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(bin) $(dep)