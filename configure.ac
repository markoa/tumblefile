
AC_INIT([tumblefile], [0.1], [marko.anastasov@gmail.com], [tumblefile])
AC_PREREQ(2.59)

AC_CONFIG_SRCDIR([src/main.cc])

AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([1.9 gnu no-define])

ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AC_ISC_POSIX
AC_PROG_CXX
AC_PROG_CC

GNOME_CXX_WARNINGS
GNOME_DEBUG_CHECK
GNOME_MAINTAINER_MODE_DEFINES

# *************************************
# Compiler and platform check
# *************************************

if test "${GXX}" != "yes" ; then
   AC_MSG_ERROR([This program relies on g++ to be compiled])
fi

AC_MSG_CHECKING([for a supported version of g++])

gxx_version=`${CXX} --version | head -n 1`

case "${gxx_version}" in
     *4.*)
	AC_MSG_RESULT([ok (${gxx_version})])
	;;
     *)
        AC_MSG_RESULT([no (${gxx_version})])
	AC_MSG_ERROR([g++ version 4.* is required])
	;;
esac

AC_CANONICAL_HOST

AC_LANG_CPLUSPLUS

# *************************************
# Library checks
# *************************************
#PKG_CHECK_MODULES([GTKMM], [gtkmm-2.4 >= 2.16.0])
#AC_SUBST([GTKMM_CFLAGS])
#AC_SUBST([GTKMM_LIBS])

PKG_CHECK_MODULES([GIOMM], [giomm-2.4 >= 2.16.0])
AC_SUBST([GIOMM_CFLAGS])
AC_SUBST([GIOMM_LIBS])

# *************************************
# LIBS and CFLAGS definitions
# *************************************

TUMBLEFILE_LIBS="$GIOMM_LIBS"

TUMBLEFILE_CFLAGS="$GIOMM_CFLAGS"

AC_SUBST(TUMBLEFILE_LIBS)
AC_SUBST(TUMBLEFILE_CFLAGS)

# *************************************
# Prepare for make
# *************************************

# Allow 'make install'.
AC_PROG_INSTALL

# Generate the files:
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

AC_MSG_NOTICE([Configuration complete.])
