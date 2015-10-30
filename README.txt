To run unit tests:

1) ./autogen.sh
2) mkdir -p builds/debug;
3) cd builds/debug;
4) ../../configure CXXFLAGS="-O0 -ggdb" --with-boost-headers=<absolute-path-to-boost-headers> --enable-gtest
5) make
6) cd "<build-directory>/WG/Local/Tests/build_autotools" for test executables.

Documentation can be found in WG/Local/Docs.
