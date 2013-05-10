#******************************************************************************#
# A Makefile.am in the same directory as configure.ac is needed so that 
#   autotools generates the necessary make targets.
#******************************************************************************#

#Must appear only in the top-leve Makefile.am
include $(top_srcdir)/TopLevelDist.am

#Told to do so by autgen.sh
#Must appear only in the top-leve Makefile.am
ACLOCAL_AMFLAGS = -I build-m4

#To ensure "make distcheck"s call to configure employs the user's configure 
# flags.
#Must appear only in the top-leve Makefile.am
DISTCHECK_CONFIGURE_FLAGS=$(SELECTED_CONFIG_FLAGS)

SUBDIRS = \
    WG/ExternalLibsPkg/build_autotools \
    WG/ExternalLibsNoInstall/build_autotools \
    WG/Utils/build_autotools
