lib_LTLIBRARIES = libsimpleconf.la

libsimpleconf_la_CXXFLAGS = -I$(top_srcdir)/include -std=c++11 -W -Wall -pedantic -O3
libsimpleconf_la_LDFLAGS = -Wl,--as-needed -Wl,-soname -Wl,libsimpleconf.so.0 -version-info 0:0:0
libsimpleconf_la_SOURCES = \
	simpleconf.cpp \
	$(NULL)

