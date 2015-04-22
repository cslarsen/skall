OBJECTS := args.o \
					 buffer.o \
					 builtins.o \
					 hash.o \
					 hashtable.o \
					 prompt.o \
					 readline.o \
					 skall.o \
					 trim.o \
					 variables.o

TARGETS := $(OBJECTS) skall

CFLAGS = --std=c99 -Wall -Iinclude -DUSE_READLINE -g
LDFLAGS = -lreadline

all: $(TARGETS)

skall: $(OBJECTS)

clean:
	rm -rf $(TARGETS) *.dSYM
