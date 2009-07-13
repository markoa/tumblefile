
AM_CXXFLAGS = -Wall -Wextra \
              -Wctor-dtor-privacy -Woverloaded-virtual -Wchar-subscripts \
              -Wpointer-arith -Wcast-align -Wsign-compare

bin_PROGRAMS = tumblefile

tumblefile_SOURCES = \
	engine.cc \
	engine.hh \
	main.cc \
	main-window.cc \
	main-window.hh \
	tray-icon.cc \
	tray-icon.hh

global_defines = \
  -DPREFIX=\""$(prefix)"\" \
  -DSYSCONFDIR=\""$(sysconfdir)"\" \
  -DLIBDIR=\""$(libdir)"\" \
  -DDATADIR=\""$(datadir)"\" \
  -DTUMBLEFILE_PKGDATADIR=\""$(pkgdatadir)"\" \
  -DGTKMM_DISABLE_DEPRECATED

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir) $(global_defines) \
               ${TUMBLEFILE_CFLAGS}

tumblefile_LDADD = ${TUMBLEFILE_LIBS}
