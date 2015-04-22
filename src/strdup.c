#include "strdup.h"

#ifndef HAVE_STRDUP
char* strdup(const char* s)
{
  char* r = malloc((1+strlen(s))*sizeof(char));
  strcpy(r, s);
  return r;
}
#endif

#ifndef HAVE_STRNDUP
char* strndup(const char* s, size_t l)
{
  char* r = malloc((1+l)*sizeof(char));
  strncpy(r, s, l);
  return r;
}
#endif
