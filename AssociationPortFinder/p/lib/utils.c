#include <stdio.h>
#include <stdlib.h>
#include "associationFinder_lib.h"


void *my_malloc(size_t size)
{
	void *result = malloc(size);
	if (!result)
		fail_errno("Cannot allocate memory with malloc");
	return result;
}

void *my_realloc(void *ptr, size_t size)
{
	void *result = realloc(ptr, size);
	if (!result)
		fail_errno("Cannot re-allocate memory");
	return result;
}

char *my_strdup(const char * const s) {
	char *result = strdup(s);
	if (!result)
		fail_errno("Cannot allocate memory for strdup\n");
	return result;
}

char *casualStringGenerator(const size_t len)
{
	char* s = my_malloc(len);
	srand(time(NULL));   // should only be called once
	for (int i = 0; i < len; ++i)
		*(s + i) = 41 + (rand() % 85);  //41 -> 125
	s[len] = '\0';
	return s;
}

char *int_to_str(const int i, int *len)
{
	int length = snprintf(NULL, 0, "%d", i);
	char* str = my_malloc(length + 1);
	snprintf(str, length + 1, "%d", i);
	*len = length;
	return str;
}