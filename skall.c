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

int last_exit_status;

static void catch_signal(int s)
{
  psignal(s, "\nskall");
}

int main(int argc, char** argv)
{
  /*
   * Install some signal handlers
   */
  signal(SIGINT, catch_signal);
  signal(SIGTSTP, catch_signal);

#ifdef USE_READLINE
  init_readline();
#endif

  for (;;) {
    char *input = readprompt(stdin, NULL);

    if ( feof(stdin) || !input ) {
      fprintf(stderr, "\n");
      break;
    }

#ifdef USE_READLINE
    add_history(input);
#endif

    char **args = parse_args(input);
    free(input);

    if ( !*args[0] )
      continue;

    if ( isbuiltin(args[0]) ) {
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
      exit(127);
    }
  }

  exit(0);
}
