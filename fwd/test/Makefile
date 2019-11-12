#CC=$(CROSS_COMPILE)gcc
BUILDENV=
ifeq ($(DEBUG), 1)
  CFLAGS=-c -g -DDEBUG
else
  CFLAGS=-c
endif

INCLUDES= \
	-I../include \
	-I/home/test/tmp/json_sandbox/json-c/include/json-c

LIBPATH= \
	-L../lib \
	-L/home/test/tmp/json_sandbox/json-c/lib

LIBS=-lfwupdate -ljson-c

TEST_SRC= \
	test.c

TEST_OBJ=$(subst .c,.o,$(TEST_SRC))

all=test

%.o: %.c
	$(CC) -fPIC $(BUILDENV) $(INCLUDES) $(CFLAGS) $< -o $@

test:
	$(CC) test.c $(INCLUDES) $(LIBPATH) $(LIBS) -o testfw

clean:
	@\rm -f $(TEST_OBJ) testfw
