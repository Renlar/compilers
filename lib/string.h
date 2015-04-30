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

str str_concat(const str head, const str tail);

str str_concat_clean(const str head, const str tail);

str str_concat_clean_head(const str head, const str tail);

str str_concat_clean_tail(const str head, const str tail);

size_t str_len(str s);

#endif//COMP_STRING