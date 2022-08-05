#include <iostream>
#include <memory>

#include "ast.h"
#include "parser.h"

int main(void) {
  std::string source = "2 ^ 5";
  auto parser = e3::Parser(source);
  auto result = parser.parse_expression();

  if (result == nullptr) {
    for (int i = 0; i < parser.error_queue().size(); i++) {
      std::cout << parser.error_queue().back() << '\n';
      parser.error_queue().pop();
    }

    return 1;
  }

  std::cout << result->execute().get_value() << '\n';
}