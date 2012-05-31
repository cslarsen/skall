TARGETS = trim.o skall
CFLAGS = --std=c99 -Wall -Iinclude

all: $(TARGETS)

skall: trim.o

clean:
	rm -f $(TARGETS)
