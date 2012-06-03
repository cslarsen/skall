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

  #ifdef USE_READLINE
  init_readline();
  #endif

  initvars();

  /*
   * Set up some default variables
   */
  nsetvar("?", 0); // $? -> last exit status
  csetvar("_", strdup(argc>1? argv[1] : "")); // $_ -> argv[1] of last cmd
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

    #ifdef USE_READLINE
    add_history(input);
    #endif

    char **args = parse_args(input);

    if ( !*args[0] )
      continue;

    if ( isbuiltin(args[0]) ) {
      exec_builtin(args[0], args);
      continue;
    }

    int pid;
    if ( (pid = fork()) > 0 ) {
      int s;
      wait(&s);

      // update variables
      free(cgetvar("_"));
      csetvar("_", strdup(args[1]? args[1] : ""));
      nsetvar("?", s);
    } else {
      // child process
      execvp(args[0], args);
      perror(argv[0]);
      exit(127);
    }
  }

  exit(0);
}
