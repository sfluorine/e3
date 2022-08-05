#pragma once

#include <string_view>
#include <string>
#include <queue>
#include <memory>

#include "lexer.h"
#include "ast.h"

namespace e3
{

class Parser {
public:
  explicit Parser(std::string_view source)
  : m_lexer(source), m_current_token(m_lexer.get_token()), m_has_error(false) {}

  auto parse_factor() -> std::unique_ptr<Expression>;
  auto parse_term() -> std::unique_ptr<Expression>;
  auto parse_expression() -> std::unique_ptr<Expression>;

  auto has_error() const -> bool { return m_has_error; }
  std::queue<std::string>& error_queue() { return m_error_queue; }

private:
  void advance();
  auto expect(TokenType type) const -> bool;
  auto eat(TokenType type) -> bool;

private:
  Lexer m_lexer;
  Token m_current_token;
  bool m_has_error;
  std::queue<std::string> m_error_queue;
};

} // namespace e3
