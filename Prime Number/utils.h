#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
//char *my_strdup(const char * const s);
void fail_errno(const char * const msg);

#endif /* #ifndef UTILS_H */
