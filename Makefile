TARGETS = args.o trim.o skall
CFLAGS = --std=c99 -Wall -Iinclude

all: $(TARGETS)

skall: args.o trim.o

clean:
	rm -f $(TARGETS)
