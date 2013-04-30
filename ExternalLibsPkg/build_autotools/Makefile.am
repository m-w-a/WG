#Note: Don't quote "make" variables because they might eventually end up as 
# "make" targets, and if their supposed to represent filesystem locations, then
# the quotes will throw make off.

EXTERNALLIBSNOINSTALL_LOCATION = $(srcdir)/../../ExternalLibsNoInstall/
EXTERNALLIBSNOINSTALLSRC_LOCATION = \
    $(EXTERNALLIBSNOINSTALL_LOCATION)/build_autotools/src/

EXTERNALLIBS_UNPACKAGED_LOG = $(srcdir)/src/.unpackaged_log

EXTRA_DIST =

if ENABLED_GTEST
    GTESTRULE = gtest
endif

all-local : \
    $(EXTERNALLIBSNOINSTALL_LOCATION) \
    $(EXTERNALLIBS_UNPACKAGED_LOG) \
    $(GTESTRULE)

$(EXTERNALLIBSNOINSTALL_LOCATION) :
	chmod u+w "$(EXTERNALLIBSNOINSTALL_LOCATION)"
	chmod u+w "$(EXTERNALLIBSNOINSTALLSRC_LOCATION)"
    
$(EXTERNALLIBS_UNPACKAGED_LOG) :
	chmod u+w "$(EXTERNALLIBS_UNPACKAGED_LOG)"/..
	$(MKDIR_P) "$(EXTERNALLIBS_UNPACKAGED_LOG)"

GTEST_FOLDER = gtest-1.6.0
GTEST_PACKAGE = $(srcdir)/src/$(GTEST_FOLDER).zip
GTEST_LOG = $(EXTERNALLIBS_UNPACKAGED_LOG)/gtest.log
EXTRA_DIST += $(GTEST_PACKAGE)
gtest : $(GTEST_LOG)
$(GTEST_LOG) : $(GTEST_PACKAGE)
	unzip -q "$(GTEST_PACKAGE)"
	mv -f "$(GTEST_FOLDER)" "$(EXTERNALLIBSNOINSTALLSRC_LOCATION)/gtest"
	touch "$(GTEST_LOG)"
