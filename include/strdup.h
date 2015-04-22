#include "config.h"

#if defined(HAVE_STRDUP) || defined(HAVE_STRNDUP)
# ifdef HAVE_STRING_H
# include <string.h>
# endif
#endif

#ifndef HAVE_STRDUP
char* strdup(const char *);
#endif

#ifndef HAVE_STRNDUP
char* strndup(const char *, size_t);
#endif
