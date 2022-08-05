#include "parser.h"

#include <map>
#include <charconv>

namespace e3
{

static std::map<TokenType, const char*> g_token_repr = {
  {TokenType::Var, "Var"},
  {TokenType::Return, "Return"},
  {TokenType::Fun, "Fun"},
  {TokenType::Id, "Identifier"},
  {TokenType::Number, "Number literal"},
  {TokenType::Add, "+"},
  {TokenType::Sub, "-"},
  {TokenType::Mul, "*"},
  {TokenType::Div, "/"},
  {TokenType::Lparen, "("},
  {TokenType::Rparen, ")"},
  {TokenType::Lbrace, "{"},
  {TokenType::Rbrace, "}"},
  {TokenType::Comma, ","},
  {TokenType::Semicolon, ";"},
  {TokenType::Unknown, "Unknown"},
  {TokenType::Eof, "EOF"},
};

auto Parser::parse_factor() -> std::unique_ptr<Expression> {
  auto token = m_current_token;
  if (!eat(TokenType::Number))
    return nullptr;

  int32_t num = 0;

  // convert the string view representation of a number
  std::from_chars(token.repr.data(), token.repr.data() + token.repr.size(), num);

  return std::make_unique<ValueExpr>(num);
}

auto Parser::parse_term() -> std::unique_ptr<Expression> {
  auto term = parse_factor();
  if (term == nullptr)
    return nullptr;

  while (expect(TokenType::Mul) || expect(TokenType::Div)) {
    auto op = m_current_token.type;
    advance();

    auto right = parse_factor();
    if (right == nullptr)
      return nullptr;

    switch (op) {
    case TokenType::Mul:
      term = std::make_unique<BinaryOpExpr>(BinaryOp::Mul, std::move(term), std::move(right));
      break;
    case TokenType::Div:
      term = std::make_unique<BinaryOpExpr>(BinaryOp::Div, std::move(term), std::move(right));
      break;
    default:
      break;
    }
  }

  return term; 
}

auto Parser::parse_expression() -> std::unique_ptr<Expression> {
  auto term = parse_term();
  if (term == nullptr)
    return nullptr;

  while (expect(TokenType::Add) || expect(TokenType::Sub)) {
    auto op = m_current_token.type;
    advance();

    auto right = parse_term();
    if (right == nullptr)
      return nullptr;

    switch (op) {
    case TokenType::Add:
      term = std::make_unique<BinaryOpExpr>(BinaryOp::Add, std::move(term), std::move(right));
      break;
    case TokenType::Sub:
      term = std::make_unique<BinaryOpExpr>(BinaryOp::Sub, std::move(term), std::move(right));
      break;
    default:
      break;
    }
  }

  return term; 
}

void Parser::advance() {
  if (m_current_token.type != TokenType::Eof)
    m_current_token = m_lexer.get_token();
}

auto Parser::expect(TokenType type) const -> bool {
  if (m_current_token.type != type)
    return false;
  return true;
}

auto Parser::eat(TokenType type) -> bool {
  if (!expect(type)) {
    m_has_error = true;

    std::string error;
    error += "ERROR: expected: ";
    error += g_token_repr[type];
    error += " but got: ";
    error += g_token_repr[m_current_token.type];

    m_error_queue.push(std::move(error));

    advance();
    return false;
  }

  advance();
  return true;
}

} // namespace e3