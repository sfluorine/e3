#include "lexer.h"

#include <string.h>
#include <ctype.h>

Lexer LexerNew(char* source) {
  Lexer lexer;

  if (source == NULL || *source == 0) {
    lexer.eof = true;
    lexer.source_len = 0;
  } else {
    lexer.eof = false;
    lexer.source_len = strlen(source);
  }

  lexer.source = source;
  return lexer;
}

void LexerAdvance(Lexer* lexer) {
  if (lexer->eof)
    return;

  lexer->source++;

  if (*lexer->source == 0)
    lexer->eof = true;
}

Token LexerGetToken(Lexer* lexer) {
  if (lexer->eof)
    return TokenNew(TOK_EOF, StringViewNew(NULL, 0));

  if (isalpha(*lexer->source)) {
    char* start = lexer->source;
    size_t count = 0;

    do {
      count++;
      LexerAdvance(lexer);
    } while (isalnum(*lexer->source));

    StringView keyword = StringViewNew(start, count);

    if (StringViewCmp(keyword, "fun"))
      return TokenNew(TOK_FUN, keyword);

    if (StringViewCmp(keyword, "var"))
      return TokenNew(TOK_VAR, keyword);

    if (StringViewCmp(keyword, "return"))
      return TokenNew(TOK_RETURN, keyword);
    return TokenNew(TOK_ID, keyword);
  }

  if (isdigit(*lexer->source)) {
    char* start = lexer->source;
    size_t count = 0;

    do {
      count++;
      LexerAdvance(lexer);
    } while (isdigit(*lexer->source));

    if (*lexer->source == '.') {
      count++;
      LexerAdvance(lexer);

      while (isdigit(*lexer->source)) {
        count++;
        LexerAdvance(lexer);
      }
    }

    return TokenNew(TOK_NUMBER, StringViewNew(start, count));
  }

  switch (*lexer->source) {
  case '=':
    LexerAdvance(lexer);
    return TokenNew(TOK_ASSIGN, StringViewNew(NULL, 0));
  case '(':
    LexerAdvance(lexer);
    return TokenNew(TOK_LPAREN, StringViewNew(NULL, 0));
  case ')':
    LexerAdvance(lexer);
    return TokenNew(TOK_RPAREN, StringViewNew(NULL, 0));
  case '{':
    LexerAdvance(lexer);
    return TokenNew(TOK_LBRACE, StringViewNew(NULL, 0));
  case '}':
    LexerAdvance(lexer);
    return TokenNew(TOK_RBRACE, StringViewNew(NULL, 0));
  case ';':
    LexerAdvance(lexer);
    return TokenNew(TOK_SEMICOLON, StringViewNew(NULL, 0));
  case '+':
    LexerAdvance(lexer);
    return TokenNew(TOK_ADD, StringViewNew(NULL, 0));
  case '-':
    LexerAdvance(lexer);
    return TokenNew(TOK_SUB, StringViewNew(NULL, 0));
  case '*':
    LexerAdvance(lexer);
    return TokenNew(TOK_MUL, StringViewNew(NULL, 0));
  case '/':
    LexerAdvance(lexer);
    return TokenNew(TOK_DIV, StringViewNew(NULL, 0));
  default:
    LexerAdvance(lexer);
    return TokenNew(TOK_UNKNOWN, StringViewNew(lexer->source - 1, 1));
  }
}
