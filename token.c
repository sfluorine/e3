#include "token.h"

Token TokenNew(TokenType type, StringView repr) {
  Token token;
  token.type = type;
  token.repr = repr;
  return token;
}
