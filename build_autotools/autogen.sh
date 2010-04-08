#!/bin/sh

case "${OSTYPE}" in
    darwin*)    TOOLIZER=glibtoolize;;
    *)          TOOLIZER=libtoolize ;;
esac

aclocal
autoheader
autoconf
${TOOLIZER}
automake --add-missing
