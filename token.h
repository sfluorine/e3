#pragma once 

#include "stringview.h"

typedef enum {
  TOK_ID = 0, // x || y
  TOK_NUMBER, // 69420
  TOK_VAR, // var
  TOK_RETURN, // return
  TOK_ASSIGN, // =
  TOK_LPAREN, // (
  TOK_RPAREN, // )
  TOK_LBRACE, // {
  TOK_RBRACE, // }
  TOK_SEMICOLON, // ;
  TOK_ADD, // +
  TOK_SUB, // -
  TOK_MUL, // *
  TOK_DIV, // /
  TOK_EOF, 
  TOK_UNKNOWN // Error token
} TokenType;

typedef struct {
  TokenType type;
  StringView repr;
} Token;

Token TokenNew(TokenType type, StringView repr);
