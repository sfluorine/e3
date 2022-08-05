CC = clang++
CPPFLAGS = -Wall -std=c++17 -Os
SRC = main.cpp lexer.cpp ast.cpp parser.cpp

all:
	$(CC) $(CPPFLAGS) $(SRC) -o e3

clean:
	rm -f e3