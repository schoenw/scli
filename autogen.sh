#!/bin/sh
#
# Run this to generate all the initial makefiles.
#
# $Id$

DIE=true
PROJECT="stools"


VER=`autoconf --version | grep '^autoconf' | sed 's/.*)//'`
case "$VER" in
0* | 1\.* | 2\.[0-9] | 2\.[0-9][a-z]* | \
2\.1[0-2] | 2\.1[0-2][a-z]* )
  cat >&2 <<_EOF_

	You must have autoconf 2.13 or later installed to compile $PROJECT.
	Download the appropriate package for your distribution/OS,
	or get the source tarball at ftp://ftp.gnu.org/pub/gnu/autoconf/
_EOF_
  DIE="exit 1"
  ;;
esac


VER=`automake --version | grep '^automake' | sed 's/.*)//'`
case "$VER" in
0* | 1\.[0-3] | 1\.[0-3][a-z]* )

  cat >&2 <<_EOF_

	You must have automake 1.4 or later installed to compile $PROJECT.
	Download the appropriate package for your distribution/OS,
	or get the source tarball at ftp://ftp.gnu.org/pub/gnu/automake/
_EOF_
  DIE="exit 1"
  ;;
esac


VER=`libtool --version | grep ' libtool)' | \
sed 's/.*) \([0-9][0-9.]*\) .*/\1/' `
case "$VER" in
0* | 1\.[0-2] | 1\.[0-2][a-z]* | \
1\.3\.[0-2] | 1\.3\.[0-2][a-z]* )

  cat >&2 <<_EOF_

	You must have libtool 1.3.3 or later installed to compile $PROJECT.
	Download the appropriate package for your distribution/OS,
	or get the source tarball at ftp://ftp.gnu.org/pub/gnu/libtool/
_EOF_
  DIE="exit 1"
  ;;
esac

$DIE

libtoolize --copy --force || exit 1

if test -z "$*"; then
	echo "Running ./configure with no arguments. If you wish to pass any,"
	echo "please specify them on the $0 command line."
fi

#aclocal_flags="`./aclocal-flags`"
aclocal_flags=""
aclocalinclude="$ACLOCAL_FLAGS $aclocal_flags"; \
echo aclocal $aclocalinclude
aclocal $aclocalinclude || exit 1
echo autoheader
autoheader || exit 1
echo automake --add-missing --gnu $am_opt
automake --add-missing --gnu $am_opt || exit 1
echo autoconf
autoconf || exit 1

./configure "$@" || exit 1

echo
echo "Now type 'make' to compile $PROJECT."
