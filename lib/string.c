#include "string.h"

#include <stdlib.h>

str str_new(str s) {
  str c = malloc(sizeof(char) * (strlen(s) + 1));
  strcpy(s, c);
  return c;
}

void str_destroy(str s) {
  free(s);
}

bool str_empty(str s) {
  return s[0] == '\0';
}
