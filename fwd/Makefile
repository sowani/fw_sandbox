PLATFORM := x86

ifeq ($(SITARA), 1)
  PLATFORM=sitara
  CC=$(CROSS_COMPILE)gcc
  AR=$(CROSS_COMPILE)ar
else
  PLATFORM=x86
  CC=gcc
  AR=ar
endif

INSTALLDIR := inst

SUBDIRS := \
	src \
	test

all:
	for dir in $(SUBDIRS) ; do \
        $(MAKE) PLATFORM=$(PLATFORM) -C $$dir ; \
    done

docs:
	doxygen

install:
	mkdir -p $(INSTALLDIR)/$(PLATFORM)/lib
	mkdir -p $(INSTALLDIR)/$(PLATFORM)/include
	mkdir -p $(INSTALLDIR)/scripts
	cp lib/$(PLATFORM)/*.a $(INSTALLDIR)/$(PLATFORM)/lib
	cp include/*.h $(INSTALLDIR)/$(PLATFORM)/include
	cp -rp scripts/* $(INSTALLDIR)/scripts

clean:
	for dir in $(SUBDIRS) ; do \
        $(MAKE) -C $$dir clean ; \
    done

doclean:
	@\rm -rf doc/html

cleaner:
	make clean
	@\rm -rf $(INSTALLDIR)
	make doclean
