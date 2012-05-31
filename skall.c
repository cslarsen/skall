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

static int last_exit_status;

static const char* BUILTINS[] = {
  "$?",
  "cd",
  "exit"
  "help",
};

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

int isbuiltin(const char* s)
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
  } else if ( !strcmp("exit", cmd) ) {
    exit(0);
  }
}

int main(int argc, char** argv)
{
  /*
   * Install some signal handlers
   */
  signal(SIGINT, catch_signal);
  signal(SIGTSTP, catch_signal);

  for (;;) {
    printf("%s", getprompt("skall %s$ "));
    char **args = parse_args(readcmd(stdin));

    if ( feof(stdin) )
      break;

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
