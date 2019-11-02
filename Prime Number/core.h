#ifndef CORE
#define CORE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <iostream>
#include <math.h>
#include "DataStruct/list_aux.h"

using namespace std;

#define MAXFORK 16
#define DEFAULTFORK 4
#define MINFORK 0
#define MAXNUM pow(2,sizeof(Elem))-1
#define DEFAULT_F_OUT 1
#define DEFAULT_F_IN 0


#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif



#endif // !CORE

