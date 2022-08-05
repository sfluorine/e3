#include "ast.h"

namespace e3
{

auto ValueExpr::execute() -> NumberValue {
  return m_value;
}

auto BinaryOpExpr::execute() -> NumberValue{
  switch (m_op)
  {
  case BinaryOp::Add:
    return NumberValue(m_lhs->execute().get_value() + m_rhs->execute().get_value());
  case BinaryOp::Sub:
    return NumberValue(m_lhs->execute().get_value() - m_rhs->execute().get_value());
  case BinaryOp::Mul:
    return NumberValue(m_lhs->execute().get_value() * m_rhs->execute().get_value());
  case BinaryOp::Div:
    return NumberValue(m_lhs->execute().get_value() / m_rhs->execute().get_value());
  }
}

} // namespace e3
