#include "strdup.h"

#ifndef HAVE_STRDUP
char* strdup(const char* s)
{
  char* r = malloc(1+strlen(s)*sizeof(char));
  strcpy(r, s);
  return r;
}
#endif
