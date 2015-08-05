#!/bin/sh

case "${OSTYPE}" in
    darwin*)    TOOLIZER=glibtoolize;;
    *)          TOOLIZER=libtoolize ;;
esac

test_cmd_exists()
{
    cmd_name="$1"
    if ! command -v "$cmd_name" >/dev/null 2>&1
    then
        echo >&2 "Error: missing '$cmd_name'.";
        exit 1;
    fi
    
    return 0
}

test_cmd_exists "aclocal"
test_cmd_exists "autoheader"
test_cmd_exists "autoconf"
test_cmd_exists "${TOOLIZER}"
test_cmd_exists "automake"
test_cmd_exists "pkg-config"
test_cmd_exists "autoreconf"

autoreconf -is