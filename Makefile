TARGETS = hash.o hashtable.o variables.o builtins.o readline.o prompt.o args.o trim.o skall
CFLAGS = --std=c99 -Wall -Iinclude -DUSE_READLINE -g
LDFLAGS = -lreadline

all: $(TARGETS)

skall: hash.o hashtable.o variables.o builtins.o readline.o args.o trim.o prompt.o

clean:
	rm -f $(TARGETS)
