/*
 * SKALL is a minimal, experimental UNIX shell
 *
 * Put in the public domain by the author
 *
 * Written by Christian Stigen Larsen, 2012-05-31
 * http://csl.sublevel3.org
 *
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#include "skall.h"
#include "trim.h"
#include "args.h"
#include "prompt.h"
#include "readline.h"
#include "builtins.h"
#include "variables.h"

static void catch_signal(int s)
{
  psignal(s, "\nskall");
}

static void initialize(int argc, char** argv)
{
  /*
   * Install some signal handlers
   */
  signal(SIGINT, catch_signal);
  signal(SIGTSTP, catch_signal);

  #ifdef HAVE_LIBREADLINE
  init_readline();
  #endif

  initvars();

  /*
   * Set up some default variables
   */
  nsetvar("#", argc);
  nsetvar("$", getpid());
  nsetvar("?", 0);
  csetvar("_", argv[0]);
}

// NOTE: We only use strings currently.
void expand_vars(char** args)
{
  for ( char **p = args; *p; ++p ) {
    if ( **p != '$' )
      continue;

    char *name = (*p)+1;
    struct buffer *b = getvar(name);

    if ( b == NULL ) {
      // Try environment if it doesn't exist in the hash table
      char *env = getenv(name);
      *p = env!=NULL? env : "";
    } else {
      *p = b->ptr;
    }
  }
}

/*
 * Look for "FOO=bar" from the left and set variables and clear arg. Stop when
 * we don't find any.
 */
size_t setvars(char** args)
{
  size_t offset = 0;
  for ( char **p=args; *p; ++p ) {
    char *eq = strchr(*p, '=');
    // TODO: Look for "export VAR=VAL" and setenv(name, value)
    if ( eq != NULL ) {
      int len = eq - *p;
      char *value = eq+1;
      char* name = strndup(*p, len);
      csetvar(name, value);
      free(name);
      ++offset;
    } else
      break;
  }

  return offset;
}

int main(int argc, char** argv)
{
  initialize(argc, argv);

  char *input = strdup(argv[0]);

  for (;;) {
    free(input);
    input = readprompt(stdin, NULL);

    if ( feof(stdin) || !input ) {
      fprintf(stderr, "\n");
      break;
    }

#ifdef HAVE_LIBREADLINE
    add_history(input);
#endif

    int argc = 0;
    char **args = parse_args(input, &argc);

    if ( !argc || !*args[0] )
      continue;

    if ( isbuiltin(args[0]) ) {
      exec_builtin(args[0], args);
      continue;
    }

    expand_vars(args);
    size_t offset = setvars(args);

    int pid;
    if ( (pid = fork()) > 0 ) {
      int exit_code=0;
      wait(&exit_code);
      csetvar("_", args[(argc-offset)-1]);
      nsetvar("?", exit_code);
    } else if ( args[offset] != NULL ) {
      // child process
      execvp(args[offset], args[offset]!=NULL? args+offset : NULL);
      perror("skall");
      exit(127);
    }
  }

  exit(0);
}
