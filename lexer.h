#pragma once

#include <string_view>

#include "token.h"

namespace e3
{

class Lexer {
public:
  Lexer()
  : m_source(""), m_index(0), m_eof(true) {}

  Lexer(std::string_view source)
  : m_source(source), m_index(0) 
  {
    m_eof = false;

    if (m_source.data() == nullptr || m_source == "")
      m_eof = true;
  }

  auto get_token() -> Token;

private:
  auto eof() const -> bool;
  void advance();
  void skip_whitespace();

private:
  std::string_view m_source;
  size_t m_index;
  bool m_eof;
};

} // namespace e3
