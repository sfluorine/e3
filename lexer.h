#pragma once

#include "token.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  bool eof;
  char* source;
  size_t source_len;
} Lexer;

Lexer LexerNew(char* source);
void LexerAdvance(Lexer* lexer);
Token LexerGetToken(Lexer* lexer);
