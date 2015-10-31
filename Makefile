CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra
OBJS = src/kheadgen.o
BIN = bin/kheadgen
RM = rm -rv

all: $(BIN)

$(BIN): $(OBJS)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	$(RM) $(OBJS) $(BIN)

.PHONY: clean
