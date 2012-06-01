TARGETS = builtins.o readline.o prompt.o args.o trim.o skall
CFLAGS = --std=c99 -Wall -Iinclude -DUSE_READLINE
LDFLAGS = -lreadline

all: $(TARGETS)

skall: builtins.o readline.o args.o trim.o prompt.o

clean:
	rm -f $(TARGETS)
