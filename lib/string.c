#include "string.h"

#include <stdlib.h>

str str_new(const str s) {
  str c = malloc(sizeof(char) * (strlen(s) + 2));
  strcpy(c, s);
  return c;
}

void str_destroy(str s) {
  free(s);
}

bool str_empty(const str s) {
  return s[0] == '\0';
}
