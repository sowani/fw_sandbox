FWU_LIB=libfwupdate.a

#CC=$(CROSS_COMPILE)gcc
#AR=$(CROSS_COMPILE)ar
BUILDENV=
ifeq ($(DEBUG), 1)
  CFLAGS=-c -g -DDEBUG
else
  CFLAGS=-c
endif

INCLUDES= \
	-I. \
	-I../include \
	-I/home/test/tmp/json_sandbox/json-c/include/json-c

LIBPATH= \
	-L../lib \
	-L/home/test/tmp/json_sandbox/json-c/lib

LIBS=-lfwupdate -ljson-c

FWU_SRC= \
	fwupcore.c \
    fwuputil.c

FWU_OBJ=$(subst .c,.o,$(FWU_SRC))

all=$(FWU_LIB)

$(FWU_LIB): $(FWU_OBJ)
	$(AR) ru $@ $(FWU_OBJ)
	ranlib $@
	mkdir -p ../lib
	mv $(FWU_LIB) ../lib

%.o: %.c
	$(CC) -fPIC $(BUILDENV) $(INCLUDES) $(CFLAGS) $< -o $@

test:
	$(CC) test.c $(INCLUDES) $(LIBPATH) $(LIBS) -o testfw

clean:
	@\rm -f $(FWU_OBJ)

doclean:
	@\rm -rf ../doc/*

cleaner:
	@\rm -rf $(FWU_OBJ) ../lib/$(FWU_LIB) testfw
	make doclean
