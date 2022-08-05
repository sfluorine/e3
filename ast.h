#pragma once

#include <memory>

namespace e3
{

class NumberValue {
public:
  NumberValue(int32_t num)
  : m_num(num) {}

  auto get_value() const -> int32_t { return m_num; }

private:
  int32_t m_num;
};

class Expression {
public:
  virtual ~Expression() {}
  virtual auto execute() -> NumberValue = 0;

protected:
  Expression() {}
};

class ValueExpr : public Expression {
public:
  explicit ValueExpr(NumberValue value)
  : m_value(value) {}

  virtual auto execute() -> NumberValue override;

private:
  NumberValue m_value;
};

enum class BinaryOp {
  Add,
  Sub,
  Mul,
  Div,
  Pow,
};

class BinaryOpExpr : public Expression {
public:
  explicit BinaryOpExpr(BinaryOp op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
  : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}

  virtual auto execute() -> NumberValue override;

private:
  BinaryOp m_op;
  std::unique_ptr<Expression> m_lhs;
  std::unique_ptr<Expression> m_rhs;
};

} // namespace e3
