#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "skall.h"
#include "args.h"
#include "trim.h"

static char* args[MAXARGS];

/*
 * TODO: Have parse_args understand quoting
 */
char** parse_args(char *s, int* p)
{
  int n = 0;
  args[MAXARGS-1] = NULL;
  args[0] = s;
  char *prev = triml(s);

  while ( *s ) {
    if ( isspace(*s) ) {
      if ( n == MAXARGS-2 ) {
        fprintf(stderr, "warning: too many args\n");
        break;
      }

      if ( strlen(prev) )
        args[n++] = prev;

      *s = 0;
      prev = s = triml(s+1);
    } else
      ++s;
  }

  if ( strlen(prev) )
    args[n++] = prev;

  args[n++] = NULL;

  if ( p && n) *p = n-1;

  return args;
}
