#include <ctype.h>
#include <string.h>
#include "trim.h"

char* triml(char* s)
{
  if ( s ) while ( isspace(*s) ) ++s;
  return s;
}

char* trimr(char* s)
{
  if ( s ) {
    char *p = s+strlen(s)-1;

    while ( p>s && isspace(*p) )
      *p-- = 0;
  }

  return s;
}

char* trim(char* s)
{
  return triml(trimr(s));
}

