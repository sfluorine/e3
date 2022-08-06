#include <iostream>
#include <memory>

#include "ast.h"
#include "parser.h"
#include "environment.h"

int main(void) {
  std::string source;
  auto env = e3::Environment();
  env.global_env["tf"] = 34;
  env.global_env["ti"] = 35;

  while (source != "quit") {
    std::cerr << ">>> ";
    std::getline(std::cin, source);

    auto parser = e3::Parser(source);
    auto result = parser.parse_variable_assignment();

    if (result == nullptr) {
      for (int i = 0; i < parser.error_queue().size(); i++) {
        std::cout << parser.error_queue().back() << '\n';
        parser.error_queue().pop();
      }

      continue;
    }

    result->execute(env);

    for (const auto& var : env.global_env) {
      std::cout << "name: " << var.first << " value: " << var.second << '\n';
    }
  }
}