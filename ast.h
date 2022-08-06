#pragma once

#include <memory>

#include "environment.h"

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
  virtual auto execute(Environment&) -> NumberValue = 0;

protected:
  Expression() {}
};

class ValueExpr : public Expression {
public:
  explicit ValueExpr(NumberValue value)
  : m_value(value) {}

  virtual auto execute(Environment&) -> NumberValue override;

private:
  NumberValue m_value;
};

class VariableExpr : public Expression {
public:
  VariableExpr(std::string name)
  : m_name(std::move(name)) {}

  virtual auto execute(Environment&) -> NumberValue override;

private:
  std::string m_name;
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

  virtual auto execute(Environment&) -> NumberValue override;

private:
  BinaryOp m_op;
  std::unique_ptr<Expression> m_lhs;
  std::unique_ptr<Expression> m_rhs;
};

class Statement {
public:
  virtual ~Statement() {}
  virtual void execute(Environment&) = 0;

protected:
  Statement() {}
};

class VariableAssignmentStmt : public Statement {
public:
  VariableAssignmentStmt(std::string name, std::unique_ptr<Expression> expr)
  : m_name(std::move(name)), m_expr(std::move(expr)) {}

  virtual void execute(Environment&) override;

private:
  std::string m_name;
  std::unique_ptr<Expression> m_expr;
};

} // namespace e3
