#include <stdio.h>

#include "lexer.h"

int main(void) {
  char input[256];
  char *st = NULL;

  while (1) {
    fprintf(stderr, ">> ");
    st = fgets(input, 256, stdin);

    if (st == NULL)
      return 0;

    Lexer lexer = LexerNew(input);
  }
}
