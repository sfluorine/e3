#include "lexer.h"

#include <cctype>

namespace e3
{

auto Lexer::get_token() -> Token {
  if (eof()) return Token(TokenType::Eof, "");

  skip_whitespace();

  if (isdigit(m_source[m_index])) {
    auto start = std::string_view(m_source.data() + m_index);
    auto len = 0;

    do {
      len++;
      advance();
    } while (isdigit(m_source[m_index]) && !eof());

    auto result = std::string_view(start.data(), len);
    return Token(TokenType::Number, result);
  }

  if (isalpha(m_source[m_index])) {
    auto start = std::string_view(m_source.data() + m_index);
    auto len = 0;

    do {
      len++;
      advance();
    } while (isalnum(m_source[m_index]) && !eof());

    auto result = std::string_view(start.data(), len);

    if (result == "var")
      return Token(TokenType::Var, result);

    if (result == "return")
      return Token(TokenType::Return, result);

    if (result == "fun")
      return Token(TokenType::Fun, result);
    return Token(TokenType::Id, result);
  }

  if (m_source[m_index] == '+') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Add, start);
  }

  if (m_source[m_index] == '-') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Sub, start);
  }

  if (m_source[m_index] == '*') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Mul, start);
  }

  if (m_source[m_index] == '/') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Div, start);
  }

  if (m_source[m_index] == '^') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Pow, start);
  }

  if (m_source[m_index] == '(') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Lparen, start);
  }

  if (m_source[m_index] == ')') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Rparen, start);
  }

  if (m_source[m_index] == '{') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Lbrace, start);
  }

  if (m_source[m_index] == '}') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Rbrace, start);
  }

  if (m_source[m_index] == '=') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Assign, start);
  }

  if (m_source[m_index] == ',') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Comma, start);
  }

  if (m_source[m_index] == ';') {
    auto start = std::string_view(m_source.data() + m_index, 1);
    advance();

    return Token(TokenType::Semicolon, start);
  }

  auto start = std::string_view(m_source.data() + m_index, 1);
  advance();

  return Token(TokenType::Unknown, start);
}

auto Lexer::eof() const -> bool {
  return m_eof;
}

void Lexer::advance() {
  if (eof()) return;

  if (m_index >= m_source.length() - 1) {
    m_eof = true;
    return;
  }

  m_index++;
}

void Lexer::skip_whitespace() {
  while ((m_source[m_index] == ' ' || m_source[m_index] == '\n') && !eof())
    advance();
}

} // namespace e3