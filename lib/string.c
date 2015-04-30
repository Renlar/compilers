#include "string.h"

#include <stdlib.h>

str str_new(const str s) {
  str c = malloc(sizeof(char) * (str_len(s) + 1));
  strcpy(c, s);
  return c;
}

void str_destroy(str s) {
  free(s);
}

bool str_empty(const str s) {
  return s[0] == '\0';
}

str str_concat(const str head, const str tail) {
  str c = malloc(sizeof(char) * (str_len(head) + str_len(tail) + 1));
  if (head != NULL) {
    memcpy(c, head, sizeof(char) * str_len(head));
  }
  if (tail != NULL) {
  memcpy(c + sizeof(char) * str_len(head), tail, (sizeof(char) * str_len(tail)));
  }
  *(c + (str_len(head) + str_len(tail))) = '\0';
  return c;
}

str str_concat_clean(const str head, const str tail) {
  str ret = str_concat(head, tail);
  if (head != NULL) {
    str_destroy(head);
  }
  if (tail != NULL) {
    str_destroy(tail);
  }
  return ret;
}


str str_concat_clean_head(const str head, const str tail) {
  str ret = str_concat(head, tail);
  if (head != NULL) {
    str_destroy(head);
  }
  return ret;
}


str str_concat_clean_tail(const str head, const str tail) {
  str ret = str_concat(head, tail);
  if (tail != NULL) {
    str_destroy(tail);
  }
  return ret;
}


size_t str_len(str s) {
  if (s == NULL) {
    return 0;
  }
  return strlen(s);
}