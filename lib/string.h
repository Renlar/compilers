#ifndef COMP_STRING
#define COMP_STRING

#include <string.h>
#include <stdbool.h>

typedef char* str;

/*
 * takes a pointer to a null terminated string and copies it into malloced
 * memory.
 * @arg s a pointer to the string to malloc space for.
 * @return a pointer to the malloced memory containing s.
 */
str str_new(const str s);

void str_destroy(str s);

bool str_empty(const str s);


#endif//COMP_STRING