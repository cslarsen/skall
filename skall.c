/*
 * SKALL is a minimal, experimental UNIX shell
 *
 * Put in the public domain by the author
 *
 * Written by Christian Stigen Larsen, 2012-05-31
 * http://csl.sublevel3.org
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "skall> "
#define MAXLINE 1024
#define MAXARGS 256

static char* args[MAXARGS];
static int last_exit_status;

static const char* BUILTINS[] = {
  "help",
  "cd",
  "$?"
};

static char* triml(char* s)
{
  while ( isspace(*s) ) ++s;
  return s;
}

static char* trimr(char* s)
{
  char *p = s+strlen(s)-1;

  while ( p>s && isspace(*p) )
    *p-- = 0;

  return s;
}

static char* trim(char* s)
{
  return triml(trimr(s));
}

static void parse_args(char *s)
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
}

static void print_args()
{
  for ( int n=0; n<MAXARGS && args[n]; ++n )
    fprintf(stderr, "arg[%d] = '%s'\n", n, args[n]);
}

char* readcmd(FILE* f)
{
  static char line[MAXLINE];
  line[0] = 0;
  fgets(line, sizeof(line), stdin);
  return trim(line);
}

int builtin_cmd(const char* s)
{
  for ( int n=0; n<sizeof(BUILTINS)/sizeof(char*); ++n )
    if ( !strcmp(BUILTINS[n], s) )
      return 1;
  return 0;
}

void exec_builtin(const char* cmd, char* const* argv)
{
  if ( !strcmp("cd", cmd) ) {
    chdir(argv[1]);
    fprintf(stderr, "chdir to '%s'\n", argv[1]);
  } else if ( !strcmp("help", cmd) ) {
    fprintf(stderr, "skall is a minimal, experimental unix shell\n\n");
    fprintf(stderr, "builtin commands:\n");

    for ( int n=0; n<sizeof(BUILTINS)/sizeof(char*); ++n )
      fprintf(stderr, "%s ", BUILTINS[n]);

    fprintf(stderr, "\n");
  } else if ( !strcmp("$?", cmd) ) {
    printf("%d\n", last_exit_status);
  }
}

int main(int argc, char** argv)
{
  for (;;) {
    printf("%s", PROMPT);
    parse_args(readcmd(stdin));

    if ( feof(stdin) )
      break;

    if ( !*args[0] )
      continue;

    if ( builtin_cmd(args[0]) ) {
      exec_builtin(args[0], args);
      continue;
    }

    int pid;
    if ( (pid = fork()) > 0 ) {
      wait(&last_exit_status);
    } else {
      // child process
      execvp(args[0], args);
      perror(argv[0]);
      exit(1);
    }
  }

  exit(0);
}
