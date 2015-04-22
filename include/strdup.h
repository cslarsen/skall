#include "config.h"

#ifdef HAVE_STRDUP
#include <string.h>
#else
char* strdup(const char *);
#endif
