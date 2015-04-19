#ifndef COMP_STRING
#define COMP_STRING

#include <string.h>
#include <stdlib.h>

typedef char* str;

/*
 * takes a pointer to a null terminated string and copies it into malloced
 * memory.
 * @arg s a pointer to the string to malloc space for.
 * @return a pointer to the malloced memory containing s.
 */
str str_new(str s) {
  str c = malloc(sizeof(char) * (strlen(s) + 1));
  strcpy(s, c);
  return c;
}


#endif//COMP_STRING