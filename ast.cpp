#include "ast.h"

#include <cmath>

namespace e3
{

auto ValueExpr::execute(Environment& env) -> NumberValue {
  return m_value;
}

auto VariableExpr::execute(Environment& env) -> NumberValue {
  return NumberValue(env.global_env[m_name]);
}

auto BinaryOpExpr::execute(Environment& env) -> NumberValue {
  switch (m_op)
  {
  case BinaryOp::Add:
    return NumberValue(m_lhs->execute(env).get_value() + m_rhs->execute(env).get_value());
  case BinaryOp::Sub:
    return NumberValue(m_lhs->execute(env).get_value() - m_rhs->execute(env).get_value());
  case BinaryOp::Mul:
    return NumberValue(m_lhs->execute(env).get_value() * m_rhs->execute(env).get_value());
  case BinaryOp::Div:
    return NumberValue(m_lhs->execute(env).get_value() / m_rhs->execute(env).get_value());
  case BinaryOp::Pow:
    return NumberValue(pow(m_lhs->execute(env).get_value(), m_rhs->execute(env).get_value()));
  }
}

void VariableAssignmentStmt::execute(Environment& env) {
  env.global_env[m_name] = m_expr->execute(env).get_value();
}

} // namespace e3
