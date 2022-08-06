#pragma once

#include <map>
#include <string>

namespace e3
{

struct Environment {
public:
  Environment() {}

public:
  std::map<std::string, int32_t> global_env;
};

} // namespace e3
