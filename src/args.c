#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "skall.h"
#include "args.h"
#include "trim.h"

static char* args[MAXARGS];

/*
 * TODO: Have parse_args understand " and ' quoting.
 */
char** parse_args(char *s, int* p)
{
  int n = 0;
  args[MAXARGS-1] = NULL;
  args[0] = s;
  char *prev = triml(s);
  int quoting = 0;
  int backslash = 0;

  while ( *s ) {
    if ( !backslash && (*s == '"' || *s == '\'') ) {
      if ( *s == quoting ) {
        quoting = !quoting? *s : 0;
        strcpy(s, s+1);
      } else if ( !quoting ) {
        quoting = *s;
        strcpy(s, s+1);
      } else
        ++s;
      continue;
    }

    if ( quoting && *s == '\\' ) {
      backslash = 1;
      strcpy(s, s+1);
      continue;
    }

    if ( quoting && backslash ) {
      switch ( *s ) {
        case '"': *s = '"'; break;
        case '\'': *s = '\''; break;
        case 'a': *s = '\a'; break;
        case 'b': *s = '\b'; break;
        case 'f': *s = '\f'; break;
        case 'n': *s = '\n'; break;
        case 'r': *s = '\r'; break;
        case 't': *s = '\t'; break;
        case 'v': *s = '\v'; break;
        case '\\': *s = '\\'; break;
        default: {
          // handle \num, \0num, \xnum, \bnum, and do in user overridable
          // module
          fprintf(stderr, "error: unknown escape sequence '%c'\n", *s);
          return NULL;
        }
      }
      backslash = 0;
      ++s;
      continue;
    }

    if ( !quoting && isspace(*s) ) {
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
