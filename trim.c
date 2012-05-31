#include <ctype.h>
#include <string.h>
#include "trim.h"

char* triml(char* s)
{
  while ( isspace(*s) ) ++s;
  return s;
}

char* trimr(char* s)
{
  char *p = s+strlen(s)-1;

  while ( p>s && isspace(*p) )
    *p-- = 0;

  return s;
}

char* trim(char* s)
{
  return triml(trimr(s));
}

