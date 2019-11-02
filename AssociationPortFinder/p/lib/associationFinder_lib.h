#ifndef LIBRARY_ASC
#define LIBRARY_ASC

#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <stdlib.h>

#define MINPORTNUM 1024
#define MAXPORTNUM 65535
#define IANAMINEPHEM 49152
#define IANAMAXEPHEM 65535
#define DEFAULTBACKLOG 1
#define MAXBACKLOG 20

//#define DEBUG

//address utilities
in_port_t get_in_port(struct sockaddr *sa);
void *get_in_addr(struct sockaddr *sa);
const char *get_str_addr(struct sockaddr *sa, char *s);

//general utilities
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
char *my_strdup(const char * const s);
char *casualStringGenerator(const size_t len);
char *int_to_str(const int i, int *len);

void fail_errno(const char * const msg);
void fail(const char *const msg);

#ifdef DEBUG
#define debug(...) fprintf (stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

#endif // !LIBRARY-ASC
