#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  const char* str;
  size_t length;
} StringView;

StringView StringViewNew(char* str, size_t length);
void StringViewPrint(StringView sv);
bool StringViewCmp(StringView sv, char* str);
