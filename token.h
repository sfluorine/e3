#pragma once

#include <string_view>

namespace e3
{

enum class TokenType {
  Var,
  Return,
  Fun,
  Id,
  Number,
  Add,
  Sub,
  Mul,
  Div,
  Lparen,
  Rparen,
  Lbrace,
  Rbrace,
  Comma,
  Semicolon,
  Unknown,
  Eof,
};

struct Token {
  Token()
  : type(TokenType::Unknown), repr("") {}

  Token(TokenType type, std::string_view repr)
  : type(type), repr(repr) {}

  TokenType type;
  std::string_view repr;
};
  
}