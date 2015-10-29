In this directory run:

autoconf
automake -a
autoreconf

mkdir -p builds/debug
cd builds/debug
../../configure CXXFLAGS="-O0 -ggdb" --with-boost-headers=<Boost-Header-File-Location> --enable-gtest

make
