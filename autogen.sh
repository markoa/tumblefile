#! /bin/sh

PROJECT=lomofile

topsrcdir=`dirname $0`
if test x$topsrcdir = x ; then
	topsrcdir=.
fi

(test -f $topsrcdir/configure.ac \
  && test -f $topsrcdir/README \
  && test -d $topsrcdir/src) || {
    echo -n "**Error**: Directory "\`$topsrcdir\'" does not look like the"
    echo " top-level $PROJECT directory"
    exit 1
}

which gnome-autogen.sh || {
    echo "Please install gnome-common package."
    exit 1
}

REQUIRED_AUTOMAKE_VERSION=1.9 REQUIRED_INTLTOOL_VERSION=0.35 . gnome-autogen.sh
