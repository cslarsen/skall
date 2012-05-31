#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "skall.h"
#include "args.h"
#include "trim.h"

static char* args[MAXARGS];

char** parse_args(char *s)
{
  int n=0;
  args[MAXARGS-1] = NULL;
  args[0] = s;
  char *prev = s;

  while ( *s ) {
    if ( isspace(*s) ) {
      if ( n == MAXARGS-2 ) {
        fprintf(stderr, "warning: too many args\n");
        break;
      }

      args[n++] = prev;
      *s = 0;
      prev = s = triml(s+1);
    } else
      ++s;
  }

  args[n++] = prev;
  args[n++] = NULL;
  return args;
}
