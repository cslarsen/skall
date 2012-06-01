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

static const char prompt_fmt[] = "skall %s$ ";
int last_exit_status;

static void catch_signal(int s)
{
  psignal(s, "\nskall");
}

char* readcmd(FILE* f)
{
  static char line[MAXLINE];
  line[0] = 0;
  fgets(line, sizeof(line), stdin);
  return trim(line);
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
#ifndef USE_READLINE
    printf("%s", getprompt(prompt_fmt));
    char *input = readcmd(stdin);
#else
    char *input = trim(readline(getprompt(prompt_fmt)));
#endif

    if ( feof(stdin) || !input ) {
      fprintf(stderr, "\n");
      break;
    }

#ifdef USE_READLINE
    add_history(input);
#endif

    char **args = parse_args(input);

#ifdef USE_READLINE
    free(input);
#endif

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
      exit(1);
    }
  }

  exit(0);
}
