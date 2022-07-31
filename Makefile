CC = clang
CFLAGS = -Wall -g
SRC = main.c token.c stringview.c lexer.c

all:
	$(CC) $(CFLAGS) $(SRC) -o e3
