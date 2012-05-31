TARGETS = prompt.o args.o trim.o skall
CFLAGS = --std=c99 -Wall -Iinclude

all: $(TARGETS)

skall: args.o trim.o prompt.o

clean:
	rm -f $(TARGETS)
