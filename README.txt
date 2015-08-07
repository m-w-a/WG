1) cd build_autotools
2) ./autogen.sh
3) mkdir -p builds/debug;
4) cd builds/debug;
5) ../../configure CXXFLAGS="-O0 -ggdb" --with-boost-headers=<absolute-path-to-boost-headers> --enable-gtest
6) make
7) cd "WG/Local/Tests/build_autotools" for test executables.

Documentation can be found in Local/Docs.
