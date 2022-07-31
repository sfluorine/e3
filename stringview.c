#include "stringview.h"

#include <stdio.h>

StringView StringViewNew(char* str, size_t length) {
  StringView sv;
  sv.str = str;
  sv.length = length;
  return sv;
}

void StringViewPrint(StringView sv) {
  if (sv.str == NULL)
    return;

  for (size_t i = 0; i < sv.length; i++) {
    printf("%c", *sv.str);
    sv.str++;
  }
  printf("\n");
}

bool StringViewCmp(StringView sv, char* str) {
  if (sv.str == NULL || str == NULL)
    return false;

  for (size_t i = 0; i < sv.length; i++) {
    if (*sv.str != *str)
      return false;
  }

  return true;
}
